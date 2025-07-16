#include "bl_astOptimizer.h"


#define COLOR_RESET     "\x1b[0m"
#define COLOR_LABEL     "\x1b[1;36m"
#define COLOR_OP        "\x1b[1;33m"
#define COLOR_RESULT    "\x1b[1;32m"
#define COLOR_ARG       "\x1b[1;34m"
#define COLOR_COMMENT   "\x1b[2;37m"

// #define BL_IR_TEST

typedef enum { 
    TAC_NOP,        //
    TAC_ASSIGNDECL, //
    TAC_ASSIGN,     //
    TAC_BINOP,      //--
    TAC_UNOP,       //
    TAC_LABEL,      //
    TAC_GOTO,       //
    TAC_IFGOTO,     //
    TAC_PARAM,      //
    TAC_ARG,        //
    TAC_CALL,       //
    TAC_FUNC_BEGIN, //
    TAC_FUNC_END,   //
    TAC_MAIN_BEGIN, //
    TAC_MAIN_END,   //
    TAC_RETURN,     // 
    TAC_EXTERN,     //
    TAC_LOAD_PTR,   //
    TAC_ADDR_OF,    //
} TAC_Op;

typedef enum {
    TYPE_UNKNOWN,
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_STRING,
    TYPE_CHAR,
    TYPE_BOOL,
    TYPE_VOID,
    TYPE_IDENTIFIER,
    TYPE_PTR,
    TYPE_REF,
    TYPE_FUNCTION,
    TYPE_PARAM,
    TYPE_ARG,
    TYPE_EXTERN,
    TYPE_UNDECLARED,
} ValueType;



typedef union{
    int ival;
    float fval;
    char cval;
    bool bval;
    char* sval;
} ValuePrimitive;

typedef struct LoopContext {
    char* break_label;
    char* continue_label;
    struct LoopContext* prev;
} LoopContext;

typedef struct {
    char* name;
    char* string_val;
    int int_val;
    float float_val;
    char char_val;
    bool bool_val;
    ValueType type;
    bool is_global;
    int offset;
} SymbolEntry;

typedef struct SymbolTable SymbolTable;

typedef struct SymbolTable{
    char* scope_name;    
    int scope_id;

    SymbolEntry** entries;  
    SymbolTable* parent;
    SymbolTable** children;
    int children_count;

    int symbol_count;
    int symbol_capacity;
    int total_offset;
} SymbolTable;

typedef struct {
    SymbolTable** tables;     
    int table_count;
    int table_capacity;
    bl_arena* arena;
} SymbolTableList;

typedef struct {
    char* scope_stack[100];     
    int top;
} ScopeStack;


typedef struct {
    ValuePrimitive val;
    ValueType acquired_type;
    ValueType type;
    SymbolTable* scope;
    int scope_id;
} DataContext;

typedef struct {
    char* operator_str;
    enum KEYWORD_TYPES operator_type;
} OperatorContext;

typedef struct TACInstr {
    TAC_Op op;
    DataContext* result;
    DataContext* arg1;
    DataContext* arg2;
    OperatorContext* relop;    
    char* label;    
    int   arg_count; 

    struct TACInstr* next;
} TACInstr;

typedef struct {
    TACInstr* head;
    TACInstr* tail;
    int temp_id;
    int label_id;
} TACList;

typedef struct {
    TACList* list;
    SymbolTableList* slist;
} bl_ir;

static char temp_counter = 0;
static char label_counter = 0;
static int scope_id_counter = 0;


TACInstr* tac_create_instr(bl_arena* arena, TAC_Op op, DataContext* result, DataContext* arg1, DataContext* arg2, OperatorContext* relop, char* label);
void tac_append(TACList* list, TACInstr* instr);
void tac_print(TACList* list,bl_arena* arena);
void tac_debug_print(TACList* list,bl_arena* arena);
void tac_colored_print(TACList* list,bl_arena* arena);
void tac_export_dot(TACList* list, const char* filename,bl_arena* arena);

bl_ir* generate_tac(AST_Node* ast, bl_arena* arena);
DataContext* gen_tac(AST_Node* node, TACList* prog, SymbolTableList* slist,SymbolTable* current_table,bl_arena* arena, LoopContext* loop_ctx);
void update_types_in_list(TACList* list,bl_arena* arena);
void update_tac_values(TACInstr* instr,DataContext* ctx,SymbolTable* table,ValueType temp_type,bl_arena* arena);
bool is_binop_string(TACInstr* instr);
bool is_binop_bool(TACInstr* instr);
bool is_binop_char(TACInstr* instr);
bool is_binop_int(TACInstr* instr);
bool is_binop_float(TACInstr* instr);
bool is_compare_type(TACInstr* instr);

DataContext* new_temp(bl_arena* arena);
char* get_binop_from_keyword(enum KEYWORD_TYPES type);
char* new_label(bl_arena* arena);
char* print_type_val(DataContext* context,bl_arena* arena);
char* get_str_type(ValueType type);

char* arena_strdup(bl_arena* arena, const char* s);
void symbol_table_list_init(SymbolTableList* list, bl_arena* arena);
void allocate_offsets_for_func(SymbolTable* table,int *offset);
void allocate_offsets_for_all_funcs(SymbolTableList* list);

void print_symbol_table(SymbolTable* table);
void print_all_symbol_tables(SymbolTableList* list);
void visualize_symbol_tables_ascii(const SymbolTable *root);
void visualize_symbol_tables_dot(const SymbolTable *root);
void print_table_dot(const SymbolTable *root);
static void emit_dot_nodes(const SymbolTable *tbl);
static void print_table_ascii(const SymbolTable *tbl, int depth);
bl_ir* bhaulang_ir(char* filename, bl_arena* arena);


#ifdef BL_IR_TEST

int main(int argc, char** argv){
    if(argc != 2){
        fprintf(stderr, "Usage : ./prog <input_file>\n");
        exit(1);
    }
    bl_arena* arena = (bl_arena*)malloc(sizeof(bl_arena));
    arena_init(arena);

    bhaulang_ir(argv[argc-1],arena);
    return 0;
}

#endif

bl_ir* bhaulang_ir(char* filename, bl_arena* arena){
    AST_Node* node = bhaulang_optimizer(filename,arena);
    bl_ir* ir_struct = generate_tac(node,arena);
    update_types_in_list(ir_struct->list,arena);
    allocate_offsets_for_all_funcs(ir_struct->slist);
    return ir_struct;
}

char* get_binop_from_keyword(enum KEYWORD_TYPES type){
    switch(type){
        case BL_EQUAL:
            return "=";
        case BL_ISEQUALCOND:
            return "==";
        case BL_MODBINOP:
            return "%";
        case BL_ADDBINOP:
            return "+";
        case BL_SUBBINOP:
            return "-";
        case BL_MULTBINOP:
            return "*";
        case BL_DIVBINOP:
            return "/";
        case BL_ADDEQ:
            return "+=";
        case BL_SUBEQ:
            return "-=";
        case BL_MULTEQ:
            return "*=";
        case BL_DIVEQ:
            return "/=";
        case BL_MODEQ:
            return "%=";
        case BL_INC:
            return "++";
        case BL_DEC:
            return "--";
        case BL_LSHIFT:
            return "<<";
        case BL_RSHIFT:
            return ">>";
        case BL_AND:
            return "&";
        case BL_OR:
            return "|";
        case BL_XOR:
            return "^";
        case BL_ANDEQ:
            return "&=";
        case BL_OREQ:
            return "|=";
        case BL_XOREQ:
            return "^=";
        case BL_NOT:
            return "!";
        case BL_LESSTHAN:
            return "<";
        case BL_GRTTHAN:
            return ">";
        case BL_NOTEQ:
            return "!=";
        case BL_LESSEQ: 
            return "<=";
        case BL_GRTEQ:
            return ">=";
        case BL_LOGAND:
            return "&&";
        case BL_LOGOR:
            return "||";
        default: return keyword_enum_to_str(type);
    }
    return NULL;
}

char* get_unaryop_from_keyword(int type){
    switch(type){
        case BL_NOT:
            return "!";
            break;
        case BL_SUBBINOP:
            return "-";
            break;
        case BL_INC:
            return "++";
            break;
        case BL_DEC:
            return "--";
            break;
        case BL_KW_BHAU_PTR:
            return "*";
            break;
        case BL_KW_BHAU_REF:
            return "&";
            break;
        default: return keyword_enum_to_str(type);
    }
    return NULL;
}

char* get_str_type(ValueType type){
    switch(type){
        case TYPE_INT: return "int";
        case TYPE_BOOL: return "bool";
        case TYPE_CHAR: return "char";
        case TYPE_STRING: return "str";
        case TYPE_FLOAT: return "float";
        case TYPE_IDENTIFIER: return "idt";
        case TYPE_VOID: return "void";
        case TYPE_UNKNOWN: return "unknown";
        case TYPE_PTR: return "ptr";
        case TYPE_REF: return "ref";
        case TYPE_FUNCTION: return "func";
        case TYPE_EXTERN: return "extern";
        case TYPE_UNDECLARED: return "undeclared";
        case TYPE_PARAM: return "param";
        case TYPE_ARG : return "arg";
    }
    return NULL;
}

TACInstr* tac_create_instr(bl_arena* arena, TAC_Op op, DataContext* result, DataContext* arg1, DataContext* arg2, OperatorContext* relop, char* label) {
    TACInstr* instr = (TACInstr*)arena_alloc(arena, sizeof(TACInstr));
    instr->op = op;
    instr->result = result;
    instr->arg1 = arg1;
    instr->arg2 = arg2;
    instr->relop = relop;
    instr->label = label;
    instr->next = NULL;
    instr->arg_count = 0;
    return instr;
}

void tac_append(TACList* list, TACInstr* instr) {
    if (!list->head) {
        list->head = list->tail = instr;
    } else {
        list->tail->next = instr;
        list->tail = instr;
    }
}

DataContext* new_temp(bl_arena* arena) {
    char buf[64];
    snprintf(buf, sizeof(buf), "t%d", temp_counter++);
    char* tmp = (char*)arena_alloc(arena, strlen(buf) + 1);
    strcpy(tmp, buf);
    DataContext* ctx = (DataContext*)arena_alloc(arena,sizeof(DataContext));
    ctx->val.sval = tmp;
    ctx->type = TYPE_IDENTIFIER;
    ctx->acquired_type = TYPE_IDENTIFIER;
    return ctx;
}

char* new_label(bl_arena* arena) {
    char buf[64];
    snprintf(buf, sizeof(buf), "L%d", label_counter++);
    char* lbl = (char*)arena_alloc(arena, strlen(buf) + 1);
    strcpy(lbl, buf);
    return lbl;
}

bl_ir* generate_tac(AST_Node* ast, bl_arena* arena) {

    SymbolTable* g_table = arena_alloc(arena,sizeof(SymbolTable));
    g_table->scope_name = "global";
    g_table->scope_id = scope_id_counter;
    g_table->parent = NULL;
    g_table->symbol_count = 0;
    g_table->children_count = 0;
    g_table->symbol_capacity = 1024;
    g_table->entries = (SymbolEntry**)arena_alloc(arena,sizeof(SymbolEntry*)*g_table->symbol_capacity);
    g_table->children = (SymbolTable**)arena_alloc(arena,sizeof(SymbolTable*)*128);

    SymbolTableList* table_list = (SymbolTableList*)arena_alloc(arena,sizeof(SymbolTableList));
    symbol_table_list_init(table_list,arena);
    table_list->tables[table_list->table_count++] = g_table;

    TACList* list = (TACList*)arena_alloc(arena, sizeof(TACList));
    list->head = list->tail = NULL;
    list->temp_id = 0;
    list->label_id = 0;

    gen_tac(ast, list,table_list,g_table, arena,NULL);

    bl_ir* ir_ = (bl_ir*)arena_alloc(arena,sizeof(bl_ir));
    ir_->list = list;
    ir_->slist = table_list;
    return ir_;
}

DataContext* gen_tac(AST_Node* node, TACList* prog,SymbolTableList* slist,SymbolTable* current_table, bl_arena* arena,LoopContext* loop_ctx) {
    if (!node) return NULL;
    switch (node->type) {
        case AST_PROGRAM: {
            ASTProgram* prog_node = (ASTProgram*)node->data;
            for (size_t i = 0; i < prog_node->count; ++i) {
                gen_tac(prog_node->statements[i], prog,slist,current_table, arena,loop_ctx);
            }
            return NULL;
        }

        case AST_SWITCH: {
            AST_Switch* sw = (AST_Switch*)node->data;


            char* end_label = new_label(arena);

            LoopContext* new_ctx = (LoopContext*)arena_alloc(arena,sizeof(LoopContext));
            new_ctx->break_label = end_label,
            new_ctx->continue_label = NULL;
            new_ctx->prev = loop_ctx;

            SymbolTable* sw_table = (SymbolTable*)arena_alloc(arena,sizeof(SymbolTable));
            sw_table->parent = current_table;
            sw_table->children = (SymbolTable**)arena_alloc(arena,sizeof(SymbolTable*)*128);
            sw_table->symbol_capacity = 1024;
            sw_table->entries = (SymbolEntry**)arena_alloc(arena,sizeof(SymbolEntry*)*1024);
            sw_table->scope_id = ++scope_id_counter;
            sw_table->scope_name = "null";
            sw_table->symbol_count = 0;
            sw_table->children_count = 0;
            current_table->children[current_table->children_count++] = sw_table;
            slist->tables[slist->table_count++] = sw_table;

            DataContext* switch_val_data = gen_tac(sw->expr, prog,slist,sw_table, arena,new_ctx);


            char** case_labels = (char**)arena_alloc(arena, sizeof(char*) * sw->case_count);
            for (int i = 0; i < (int)sw->case_count; ++i) {
                case_labels[i] = new_label(arena);
            }

            for (int i = 0; i < (int)sw->case_count; ++i) {
                AST_SwitchCase* case_node = (AST_SwitchCase*)sw->cases[i]->data;
                ASTNodeType type = case_node->value->type;
                if(type == AST_INTLITERAL){
                    AST_IntLiteral* ilit = (AST_IntLiteral*)((AST_Node*)case_node->value)->data;
                    DataContext* sw_ctx = (DataContext*)arena_alloc(arena,sizeof(DataContext));
                    sw_ctx->val.ival = ilit->value;
                    sw_ctx->type = TYPE_INT;
                    sw_ctx->scope = sw_table;
                    sw_ctx->scope_id = sw_table->scope_id;
                    sw_ctx->acquired_type = TYPE_INT;

                    OperatorContext* op_ctx = (OperatorContext*)arena_alloc(arena,sizeof(OperatorContext));
                    op_ctx->operator_str = "==";
                    op_ctx->operator_type = BL_ISEQUALCOND;

                    DataContext* result = new_temp(arena);
                    result->type = TYPE_REF;
                    result->acquired_type = TYPE_REF;
                    result->scope = current_table;
                    result->scope_id = current_table->scope_id;

                    SymbolEntry* entry = (SymbolEntry*)arena_alloc(arena,sizeof(SymbolEntry));
                    entry->name = result->val.sval;
                    entry->is_global = current_table->scope_id == 0 ? true : false;
                    entry->type = TYPE_IDENTIFIER;

                    current_table->entries[current_table->symbol_count++] = entry;


                    tac_append(prog,tac_create_instr(arena,TAC_ASSIGNDECL,result,switch_val_data,NULL,NULL,NULL));
                    tac_append(prog, tac_create_instr(arena, TAC_IFGOTO, NULL, result,sw_ctx, op_ctx, case_labels[i]));
                }else if(type == AST_CHARLITERAL){
                    AST_CharLiteral* clit = (AST_CharLiteral*)((AST_Node*)case_node->value)->data;
                    DataContext* sw_ctx = (DataContext*)arena_alloc(arena,sizeof(DataContext));
                    sw_ctx->val.cval = clit->value;
                    sw_ctx->type = TYPE_CHAR;
                    sw_ctx->scope = sw_table;
                    sw_ctx->scope_id = sw_table->scope_id;
                    sw_ctx->acquired_type = TYPE_CHAR;

                    OperatorContext* op_ctx = (OperatorContext*)arena_alloc(arena,sizeof(OperatorContext));
                    op_ctx->operator_str = "==";
                    op_ctx->operator_type = BL_ISEQUALCOND;

                    DataContext* result = new_temp(arena);
                    result->type = TYPE_REF;
                    result->acquired_type = TYPE_REF;
                    result->scope = current_table;
                    result->scope_id = current_table->scope_id;

                    SymbolEntry* entry = (SymbolEntry*)arena_alloc(arena,sizeof(SymbolEntry));
                    entry->name = result->val.sval;
                    entry->is_global = current_table->scope_id == 0 ? true : false;
                    entry->type = TYPE_IDENTIFIER;

                    current_table->entries[current_table->symbol_count++] = entry;


                    tac_append(prog,tac_create_instr(arena,TAC_ASSIGNDECL,result,switch_val_data,NULL,NULL,NULL));
                    tac_append(prog, tac_create_instr(arena, TAC_IFGOTO, NULL, result,sw_ctx, op_ctx, case_labels[i]));
                }else{
                    fprintf(stderr,"Switch cannot be used with floats or strings");
                    exit(1);
                }
            }

            char* def_label = new_label(arena);
            tac_append(prog, tac_create_instr(arena, TAC_GOTO, NULL, NULL,NULL,NULL,def_label));

            for (int i = 0; i < (int)sw->case_count; ++i) {
                tac_append(prog, tac_create_instr(arena, TAC_LABEL, NULL, NULL,NULL,NULL, case_labels[i]));
                gen_tac(sw->cases[i], prog, slist,sw_table,arena,new_ctx);
            }
            tac_append(prog, tac_create_instr(arena, TAC_LABEL, NULL, NULL,NULL,NULL, def_label));

            if (sw->default_case) {
                gen_tac(sw->default_case, prog,slist,sw_table, arena,new_ctx);
            }

            tac_append(prog, tac_create_instr(arena, TAC_LABEL, NULL, NULL,NULL,NULL, end_label));
            return NULL;
        }

        case AST_CASE: {
            AST_SwitchCase* cs = (AST_SwitchCase*)node->data;
            for (int i = 0; i < (int)cs->body_count; ++i) {
                gen_tac(cs->body[i], prog,slist,current_table, arena,loop_ctx);
            }
            return NULL;
        }

        case AST_DEFAULT: {
            AST_SwitchCase* def = (AST_SwitchCase*)node->data;
            for (int i = 0; i < (int)def->body_count; ++i) {
                gen_tac(def->body[i], prog,slist,current_table, arena,loop_ctx);
            }
            return NULL;
        }

        case AST_EXTERN: {
            AST_Identifier* ext = (AST_Identifier*)((AST_Node*)((AST_Extern*)node->data)->ident)->data;
            DataContext* ext_ctx = (DataContext*)arena_alloc(arena,sizeof(DataContext));
            ext_ctx->val.sval = ext->name;
            ext_ctx->type = TYPE_IDENTIFIER;
            ext_ctx->acquired_type = TYPE_IDENTIFIER;
            ext_ctx->scope = current_table;
            ext_ctx->scope_id = current_table->scope_id;

            SymbolEntry* entry = (SymbolEntry*)arena_alloc(arena,sizeof(SymbolEntry));
            entry->is_global = current_table->scope_id == 0? true : false;
            entry->name = ext_ctx->val.sval;
            entry->type = TYPE_EXTERN;

            current_table->entries[current_table->symbol_count++] = entry;

            tac_append(prog, tac_create_instr(arena, TAC_EXTERN, ext_ctx,NULL, NULL, NULL, NULL));
            return NULL;
        }

        case AST_INTLITERAL: {
            AST_IntLiteral* lit = (AST_IntLiteral*)node->data;
            DataContext* int_val = (DataContext*)arena_alloc(arena,sizeof(DataContext));
            int_val->val.ival = lit->value;
            int_val->type = TYPE_INT;
            int_val->scope = current_table;
            int_val->scope_id = current_table->scope_id;
            int_val->acquired_type = TYPE_INT;

            return int_val;
        }
        
        case AST_BOOLLITERAL: {
            AST_BoolLiteral* blit = (AST_BoolLiteral*)node->data;
            DataContext* bool_val = (DataContext*)arena_alloc(arena,sizeof(DataContext));
            bool_val->val.bval=blit->value;
            bool_val->type = TYPE_BOOL;
            bool_val->acquired_type = TYPE_BOOL;
            bool_val->scope = current_table;
            bool_val->scope_id = current_table->scope_id;
            return bool_val;
        }

        case AST_STRINGLITERAL : {
            AST_StringLiteral* slit = (AST_StringLiteral*)node->data;
            DataContext* str_val = (DataContext*)arena_alloc(arena,sizeof(DataContext));
            str_val->val.sval = slit->value;
            str_val->type = TYPE_STRING;
            str_val->scope = current_table;
            str_val->scope_id = current_table->scope_id;
            str_val->acquired_type = TYPE_STRING;
            return str_val;
        }

        case AST_CHARLITERAL : {
            AST_CharLiteral* clit = (AST_CharLiteral*)node->data;
            DataContext* char_val = (DataContext*)arena_alloc(arena,sizeof(DataContext));
            char_val->val.cval = clit->value;
            char_val->type = TYPE_CHAR;
            char_val->acquired_type = TYPE_CHAR;
            char_val->scope = current_table;
            char_val->scope_id = current_table->scope_id;
            return char_val;
        }

        case AST_FLOATLITERAL : {
            AST_FloatLiteral* flit = (AST_FloatLiteral*)node->data;
            DataContext* float_val = (DataContext*)arena_alloc(arena,sizeof(DataContext));
            float_val->val.fval = flit->value;
            float_val->type = TYPE_FLOAT;
            float_val->acquired_type = TYPE_FLOAT;
            float_val->scope = current_table;
            float_val->scope_id = current_table->scope_id;
            return float_val;
        }

        case AST_IDENTIFIER: {
            AST_Identifier* ident = (AST_Identifier*)node->data;
            DataContext* ctx = (DataContext*)arena_alloc(arena,sizeof(DataContext));
            ctx->val.sval = ident->name;
            ctx->type = TYPE_IDENTIFIER;
            ctx->scope_id = current_table->scope_id;
            ctx->scope = current_table;
            ctx->acquired_type = TYPE_IDENTIFIER;
            return ctx;
        }

        case AST_BINOP: {
            AST_Binop* bin = (AST_Binop*)node->data;
            DataContext* left = gen_tac(bin->lhs, prog, slist,current_table,arena,loop_ctx);
            DataContext* right = gen_tac(bin->rhs, prog,slist,current_table, arena,loop_ctx);
            DataContext* result = new_temp(arena);
            result->scope = current_table;
            result->scope_id = current_table->scope_id;

            SymbolEntry* entry = (SymbolEntry*)arena_alloc(arena,sizeof(SymbolEntry));
            entry->name = result->val.sval;
            entry->is_global = current_table->scope_id == 0 ? true : false;
            entry->type = TYPE_IDENTIFIER;

            current_table->entries[current_table->symbol_count++] = entry;


            DataContext* lhs = new_temp(arena);
            lhs->scope = current_table;
            lhs->scope_id = current_table->scope_id;

            SymbolEntry* entry_lhs = (SymbolEntry*)arena_alloc(arena,sizeof(SymbolEntry));
            entry_lhs->name = lhs->val.sval;
            entry_lhs->is_global = current_table->scope_id == 0 ? true : false;
            entry_lhs->type = TYPE_IDENTIFIER;

            current_table->entries[current_table->symbol_count++] = entry_lhs;


            DataContext* rhs = new_temp(arena);
            rhs->scope = current_table;
            rhs->scope_id = current_table->scope_id;

            SymbolEntry* entry_rhs = (SymbolEntry*)arena_alloc(arena,sizeof(SymbolEntry));
            entry_rhs->name = rhs->val.sval;
            entry_rhs->is_global = current_table->scope_id == 0 ? true : false;
            entry_rhs->type = TYPE_IDENTIFIER;

            current_table->entries[current_table->symbol_count++] = entry_rhs;

            OperatorContext* op_ctx = (OperatorContext*)arena_alloc(arena,sizeof(OperatorContext));
            op_ctx->operator_str = get_binop_from_keyword(bin->op);
            op_ctx->operator_type = bin->op;


            DataContext* temp_ctx = (DataContext*)arena_alloc(arena,sizeof(DataContext));
            temp_ctx->type = TYPE_INT;
            temp_ctx->acquired_type = TYPE_INT;
            temp_ctx->scope = current_table;
            temp_ctx->scope_id = current_table->scope_id;
            temp_ctx->val.ival = 0;

            DataContext* temp_ctx_lhs = (DataContext*)arena_alloc(arena,sizeof(DataContext));
            temp_ctx_lhs->type = TYPE_INT;
            temp_ctx_lhs->acquired_type = TYPE_INT;
            temp_ctx_lhs->scope = current_table;
            temp_ctx_lhs->scope_id = current_table->scope_id;
            temp_ctx_lhs->val.ival = 0;

            DataContext* temp_ctx_rhs = (DataContext*)arena_alloc(arena,sizeof(DataContext));
            temp_ctx_rhs->type = TYPE_INT;
            temp_ctx_rhs->acquired_type = TYPE_INT;
            temp_ctx_rhs->scope = current_table;
            temp_ctx_rhs->scope_id = current_table->scope_id;
            temp_ctx_rhs->val.ival = 0;

            OperatorContext* op_ctx_lhs = (OperatorContext*)arena_alloc(arena,sizeof(OperatorContext));
            op_ctx_lhs->operator_str = "=";
            op_ctx_lhs->operator_type = BL_EQUAL;

            OperatorContext* op_ctx_rhs = (OperatorContext*)arena_alloc(arena,sizeof(OperatorContext));
            op_ctx_rhs->operator_str = "=";
            op_ctx_rhs->operator_type = BL_EQUAL;

            tac_append(prog,tac_create_instr(arena,TAC_ASSIGNDECL,result,temp_ctx,NULL,NULL,NULL));
            tac_append(prog,tac_create_instr(arena,TAC_ASSIGNDECL,lhs,temp_ctx_lhs,NULL,NULL,NULL));
            tac_append(prog,tac_create_instr(arena,TAC_ASSIGN,lhs,left,NULL,op_ctx_lhs,NULL));
            tac_append(prog,tac_create_instr(arena,TAC_ASSIGNDECL,rhs,temp_ctx_rhs,NULL,NULL,NULL));
            tac_append(prog,tac_create_instr(arena,TAC_ASSIGN,rhs,right,NULL,op_ctx_rhs,NULL));
            tac_append(prog, tac_create_instr(arena, TAC_BINOP, result, lhs, rhs, op_ctx, NULL));
            return result;
        }
        
        case AST_GROUP: {
            AST_Group* grp = (AST_Group*)node->data;
            return gen_tac(grp->expr, prog,slist, current_table,arena, loop_ctx);
        }

        case AST_UNOP: {
            AST_Unop* un = (AST_Unop*)node->data;
            DataContext* arg = gen_tac(un->node, prog,slist,current_table, arena,loop_ctx);

            if (un->op == (enum KEYWORD_TYPES)BL_KW_BHAU_REF) {
                DataContext* result = new_temp(arena);
                result->type = TYPE_REF;
                result->acquired_type = TYPE_REF;
                result->scope = current_table;
                result->scope_id = current_table->scope_id;

                SymbolEntry* entry = (SymbolEntry*)arena_alloc(arena,sizeof(SymbolEntry));
                entry->name = result->val.sval;
                entry->is_global = current_table->scope_id == 0 ? true : false;
                entry->type = TYPE_IDENTIFIER;

                current_table->entries[current_table->symbol_count++] = entry;

                OperatorContext* op_ctx = (OperatorContext*)arena_alloc(arena,sizeof(OperatorContext));
                op_ctx->operator_str = get_unaryop_from_keyword(un->op);
                op_ctx->operator_type = un->op;

                DataContext* temp_ctx = (DataContext*)arena_alloc(arena,sizeof(DataContext));
                temp_ctx->type = TYPE_INT;
                temp_ctx->acquired_type = TYPE_INT;
                temp_ctx->scope = current_table;
                temp_ctx->scope_id = current_table->scope_id;
                temp_ctx->val.ival = 0;
                tac_append(prog,tac_create_instr(arena,TAC_ASSIGNDECL,result,temp_ctx,NULL,NULL,NULL));
                tac_append(prog, tac_create_instr(arena, TAC_ADDR_OF, result, arg, NULL, op_ctx, NULL));
                return result;
            }else if(un->op == (enum KEYWORD_TYPES)BL_KW_BHAU_PTR){
                DataContext* result = new_temp(arena);
                result->type = TYPE_PTR;
                result->acquired_type = TYPE_PTR;
                result->scope = current_table;
                result->scope_id = current_table->scope_id;


                SymbolEntry* entry = (SymbolEntry*)arena_alloc(arena,sizeof(SymbolEntry));
                entry->name = result->val.sval;
                entry->is_global = current_table->scope_id == 0 ? true : false;
                entry->type = TYPE_IDENTIFIER;

                current_table->entries[current_table->symbol_count++] = entry;

                OperatorContext* op_ctx = (OperatorContext*)arena_alloc(arena,sizeof(OperatorContext));
                op_ctx->operator_str = get_unaryop_from_keyword(un->op);
                op_ctx->operator_type = un->op;

                DataContext* temp_ctx = (DataContext*)arena_alloc(arena,sizeof(DataContext));
                temp_ctx->type = TYPE_INT;
                temp_ctx->scope = current_table;
                temp_ctx->scope_id = current_table->scope_id;
                temp_ctx->acquired_type = TYPE_INT;
                temp_ctx->val.ival = 0;
                tac_append(prog,tac_create_instr(arena,TAC_ASSIGNDECL,result,temp_ctx,NULL,NULL,NULL));
                tac_append(prog,tac_create_instr(arena,TAC_LOAD_PTR,result,arg,NULL,op_ctx,NULL));
                return result;
            }else if(un->op == (enum KEYWORD_TYPES)BL_INC || un->op == (enum KEYWORD_TYPES)BL_DEC){
                DataContext* result = new_temp(arena);
                result->scope = current_table;
                result->scope_id = current_table->scope_id;

                SymbolEntry* entry = (SymbolEntry*)arena_alloc(arena,sizeof(SymbolEntry));
                entry->name = result->val.sval;
                entry->is_global = current_table->scope_id == 0 ? true : false;
                entry->type = TYPE_IDENTIFIER;

                current_table->entries[current_table->symbol_count++] = entry;

                OperatorContext* op_ctx = (OperatorContext*)arena_alloc(arena,sizeof(OperatorContext));
                op_ctx->operator_str = get_unaryop_from_keyword(un->op);
                op_ctx->operator_type = un->op;

                OperatorContext* aop_ctx = (OperatorContext*)arena_alloc(arena,sizeof(OperatorContext));
                aop_ctx->operator_str = "=";
                aop_ctx->operator_type = BL_EQUAL;

                DataContext* temp_ctx = (DataContext*)arena_alloc(arena,sizeof(DataContext));
                temp_ctx->type = TYPE_INT;
                temp_ctx->scope = current_table;
                temp_ctx->scope_id = current_table->scope_id;
                temp_ctx->acquired_type = TYPE_INT;
                temp_ctx->val.ival = 0;
                tac_append(prog,tac_create_instr(arena,TAC_ASSIGNDECL,result,temp_ctx,NULL,NULL,NULL));
                tac_append(prog, tac_create_instr(arena, TAC_UNOP, result, arg, NULL, op_ctx, NULL));
                tac_append(prog,tac_create_instr(arena,TAC_ASSIGN,arg,result,NULL, aop_ctx,NULL));
                return arg;
            }
            DataContext* result = new_temp(arena);
            result->scope = current_table;
            result->scope_id = current_table->scope_id;

            SymbolEntry* entry = (SymbolEntry*)arena_alloc(arena,sizeof(SymbolEntry));
            entry->name = result->val.sval;
            entry->is_global = current_table->scope_id == 0 ? true : false;
            entry->type = TYPE_IDENTIFIER;

            current_table->entries[current_table->symbol_count++] = entry;

            OperatorContext* op_ctx = (OperatorContext*)arena_alloc(arena,sizeof(OperatorContext));
            op_ctx->operator_str = get_unaryop_from_keyword(un->op);
            op_ctx->operator_type = un->op;

            DataContext* temp_ctx = (DataContext*)arena_alloc(arena,sizeof(DataContext));
            temp_ctx->type = TYPE_INT;
            temp_ctx->acquired_type = TYPE_INT;
            temp_ctx->scope = current_table;
            temp_ctx->scope_id = current_table->scope_id;
            temp_ctx->val.ival = 0;
            tac_append(prog,tac_create_instr(arena,TAC_ASSIGNDECL,result,temp_ctx,NULL,NULL,NULL));
            tac_append(prog, tac_create_instr(arena, TAC_UNOP, result, arg, NULL, op_ctx, NULL));
            return result;
        }

        case AST_ASSIGN: {
            AST_Assign* asg = (AST_Assign*)node->data;
            DataContext* rhs = gen_tac(asg->rhs, prog,slist,current_table, arena,loop_ctx);
            DataContext* ctx = (DataContext*)arena_alloc(arena,sizeof(DataContext));
            if(asg->lhs->type == AST_UNOP && (((AST_Unop*)asg->lhs->data)->op == (enum KEYWORD_TYPES)BL_KW_BHAU_REF || ((AST_Unop*)asg->lhs->data)->op == (enum KEYWORD_TYPES)BL_KW_BHAU_PTR)){
                fprintf(stderr, "Reference not allowed on left side of the assignment\n");
                exit(69);
            }
            AST_Identifier* ident = (AST_Identifier*)asg->lhs->data;
            ctx->val.sval = ident->name;
            ctx->type = TYPE_IDENTIFIER;
            ctx->scope = current_table;
            ctx->scope_id = current_table->scope_id;
            ctx->acquired_type = TYPE_IDENTIFIER;

            OperatorContext* op_ctx = (OperatorContext*)arena_alloc(arena,sizeof(OperatorContext));
            op_ctx->operator_str = get_binop_from_keyword(asg->op);
            op_ctx->operator_type = asg->op;

            if(strcmp(op_ctx->operator_str,"=") == 0){
                tac_append(prog, tac_create_instr(arena, TAC_ASSIGN, ctx, rhs, NULL,op_ctx, NULL));
            }else if(strcmp(op_ctx->operator_str,"+=") == 0){
                DataContext* left = ctx;
                DataContext* right = rhs;
                DataContext* result = new_temp(arena);
                result->scope = current_table;
                result->scope_id = current_table->scope_id;

                SymbolEntry* entry = (SymbolEntry*)arena_alloc(arena,sizeof(SymbolEntry));
                entry->name = result->val.sval;
                entry->is_global = current_table->scope_id == 0 ? true : false;
                entry->type = TYPE_IDENTIFIER;

                current_table->entries[current_table->symbol_count++] = entry;

                DataContext* lhs = new_temp(arena);
                lhs->scope = current_table;
                lhs->scope_id = current_table->scope_id;

                SymbolEntry* entry_lhs = (SymbolEntry*)arena_alloc(arena,sizeof(SymbolEntry));
                entry_lhs->name = lhs->val.sval;
                entry_lhs->is_global = current_table->scope_id == 0 ? true : false;
                entry_lhs->type = TYPE_IDENTIFIER;

                current_table->entries[current_table->symbol_count++] = entry_lhs;


                DataContext* rhs = new_temp(arena);
                rhs->scope = current_table;
                rhs->scope_id = current_table->scope_id;

                SymbolEntry* entry_rhs = (SymbolEntry*)arena_alloc(arena,sizeof(SymbolEntry));
                entry_rhs->name = rhs->val.sval;
                entry_rhs->is_global = current_table->scope_id == 0 ? true : false;
                entry_rhs->type = TYPE_IDENTIFIER;

                current_table->entries[current_table->symbol_count++] = entry_rhs;


                DataContext* temp_ctx_lhs = (DataContext*)arena_alloc(arena,sizeof(DataContext));
                temp_ctx_lhs->type = TYPE_INT;
                temp_ctx_lhs->acquired_type = TYPE_INT;
                temp_ctx_lhs->scope = current_table;
                temp_ctx_lhs->scope_id = current_table->scope_id;
                temp_ctx_lhs->val.ival = 0;

                DataContext* temp_ctx_rhs = (DataContext*)arena_alloc(arena,sizeof(DataContext));
                temp_ctx_rhs->type = TYPE_INT;
                temp_ctx_rhs->acquired_type = TYPE_INT;
                temp_ctx_rhs->scope = current_table;
                temp_ctx_rhs->scope_id = current_table->scope_id;
                temp_ctx_rhs->val.ival = 0;

                OperatorContext* op_ctx_lhs = (OperatorContext*)arena_alloc(arena,sizeof(OperatorContext));
                op_ctx_lhs->operator_str = "=";
                op_ctx_lhs->operator_type = BL_EQUAL;

                OperatorContext* op_ctx_rhs = (OperatorContext*)arena_alloc(arena,sizeof(OperatorContext));
                op_ctx_rhs->operator_str = "=";
                op_ctx_rhs->operator_type = BL_EQUAL;


                OperatorContext* op_ctx = (OperatorContext*)arena_alloc(arena,sizeof(OperatorContext));
                op_ctx->operator_str = "+";
                op_ctx->operator_type = BL_ADDBINOP;

                OperatorContext* aop_ctx = (OperatorContext*)arena_alloc(arena,sizeof(OperatorContext));
                aop_ctx->operator_str = "=";
                aop_ctx->operator_type = BL_EQUAL;

                DataContext* temp_ctx = (DataContext*)arena_alloc(arena,sizeof(DataContext));
                temp_ctx->type = TYPE_INT;
                temp_ctx->scope = current_table;
                temp_ctx->scope_id = current_table->scope_id;
                temp_ctx->acquired_type = TYPE_INT;
                temp_ctx->val.ival = 0;
                tac_append(prog,tac_create_instr(arena,TAC_ASSIGNDECL,result,temp_ctx,NULL,NULL,NULL));
                tac_append(prog,tac_create_instr(arena,TAC_ASSIGNDECL,lhs,temp_ctx_lhs,NULL,NULL,NULL));
                tac_append(prog,tac_create_instr(arena,TAC_ASSIGN,lhs,left,NULL,op_ctx_lhs,NULL));
                tac_append(prog,tac_create_instr(arena,TAC_ASSIGNDECL,rhs,temp_ctx_rhs,NULL,NULL,NULL));
                tac_append(prog,tac_create_instr(arena,TAC_ASSIGN,rhs,right,NULL,op_ctx_rhs,NULL));
                tac_append(prog, tac_create_instr(arena, TAC_BINOP, result, lhs, rhs, op_ctx, NULL));
                tac_append(prog, tac_create_instr(arena, TAC_ASSIGN, ctx, result, NULL,aop_ctx, NULL));
            }else if(strcmp(op_ctx->operator_str,"-=") == 0){
                DataContext* left = ctx;
                DataContext* right = rhs;
                DataContext* result = new_temp(arena);
                result->scope = current_table;
                result->scope_id = current_table->scope_id;

                SymbolEntry* entry = (SymbolEntry*)arena_alloc(arena,sizeof(SymbolEntry));
                entry->name = result->val.sval;
                entry->is_global = current_table->scope_id == 0 ? true : false;
                entry->type = TYPE_IDENTIFIER;

                current_table->entries[current_table->symbol_count++] = entry;

                DataContext* lhs = new_temp(arena);
                lhs->scope = current_table;
                lhs->scope_id = current_table->scope_id;

                SymbolEntry* entry_lhs = (SymbolEntry*)arena_alloc(arena,sizeof(SymbolEntry));
                entry_lhs->name = lhs->val.sval;
                entry_lhs->is_global = current_table->scope_id == 0 ? true : false;
                entry_lhs->type = TYPE_IDENTIFIER;

                current_table->entries[current_table->symbol_count++] = entry_lhs;


                DataContext* rhs = new_temp(arena);
                rhs->scope = current_table;
                rhs->scope_id = current_table->scope_id;

                SymbolEntry* entry_rhs = (SymbolEntry*)arena_alloc(arena,sizeof(SymbolEntry));
                entry_rhs->name = rhs->val.sval;
                entry_rhs->is_global = current_table->scope_id == 0 ? true : false;
                entry_rhs->type = TYPE_IDENTIFIER;

                current_table->entries[current_table->symbol_count++] = entry_rhs;


                DataContext* temp_ctx_lhs = (DataContext*)arena_alloc(arena,sizeof(DataContext));
                temp_ctx_lhs->type = TYPE_INT;
                temp_ctx_lhs->acquired_type = TYPE_INT;
                temp_ctx_lhs->scope = current_table;
                temp_ctx_lhs->scope_id = current_table->scope_id;
                temp_ctx_lhs->val.ival = 0;

                DataContext* temp_ctx_rhs = (DataContext*)arena_alloc(arena,sizeof(DataContext));
                temp_ctx_rhs->type = TYPE_INT;
                temp_ctx_rhs->acquired_type = TYPE_INT;
                temp_ctx_rhs->scope = current_table;
                temp_ctx_rhs->scope_id = current_table->scope_id;
                temp_ctx_rhs->val.ival = 0;

                OperatorContext* op_ctx_lhs = (OperatorContext*)arena_alloc(arena,sizeof(OperatorContext));
                op_ctx_lhs->operator_str = "=";
                op_ctx_lhs->operator_type = BL_EQUAL;

                OperatorContext* op_ctx_rhs = (OperatorContext*)arena_alloc(arena,sizeof(OperatorContext));
                op_ctx_rhs->operator_str = "=";
                op_ctx_rhs->operator_type = BL_EQUAL;


                OperatorContext* op_ctx = (OperatorContext*)arena_alloc(arena,sizeof(OperatorContext));
                op_ctx->operator_str = "-";
                op_ctx->operator_type = BL_SUBBINOP;

                OperatorContext* aop_ctx = (OperatorContext*)arena_alloc(arena,sizeof(OperatorContext));
                aop_ctx->operator_str = "=";
                aop_ctx->operator_type = BL_EQUAL;

                DataContext* temp_ctx = (DataContext*)arena_alloc(arena,sizeof(DataContext));
                temp_ctx->type = TYPE_INT;
                temp_ctx->scope = current_table;
                temp_ctx->scope_id = current_table->scope_id;
                temp_ctx->acquired_type = TYPE_INT;
                temp_ctx->val.ival = 0;
                tac_append(prog,tac_create_instr(arena,TAC_ASSIGNDECL,result,temp_ctx,NULL,NULL,NULL));
                tac_append(prog,tac_create_instr(arena,TAC_ASSIGNDECL,lhs,temp_ctx_lhs,NULL,NULL,NULL));
                tac_append(prog,tac_create_instr(arena,TAC_ASSIGN,lhs,left,NULL,op_ctx_lhs,NULL));
                tac_append(prog,tac_create_instr(arena,TAC_ASSIGNDECL,rhs,temp_ctx_rhs,NULL,NULL,NULL));
                tac_append(prog,tac_create_instr(arena,TAC_ASSIGN,rhs,right,NULL,op_ctx_rhs,NULL));
                tac_append(prog, tac_create_instr(arena, TAC_BINOP, result, lhs, rhs, op_ctx, NULL));
                tac_append(prog, tac_create_instr(arena, TAC_ASSIGN, ctx, result, NULL,aop_ctx, NULL));
            }else if(strcmp(op_ctx->operator_str,"*=") == 0){
                DataContext* left = ctx;
                DataContext* right = rhs;
                DataContext* result = new_temp(arena);
                result->scope = current_table;
                result->scope_id = current_table->scope_id;

                SymbolEntry* entry = (SymbolEntry*)arena_alloc(arena,sizeof(SymbolEntry));
                entry->name = result->val.sval;
                entry->is_global = current_table->scope_id == 0 ? true : false;
                entry->type = TYPE_IDENTIFIER;

                current_table->entries[current_table->symbol_count++] = entry;

                DataContext* lhs = new_temp(arena);
                lhs->scope = current_table;
                lhs->scope_id = current_table->scope_id;

                SymbolEntry* entry_lhs = (SymbolEntry*)arena_alloc(arena,sizeof(SymbolEntry));
                entry_lhs->name = lhs->val.sval;
                entry_lhs->is_global = current_table->scope_id == 0 ? true : false;
                entry_lhs->type = TYPE_IDENTIFIER;

                current_table->entries[current_table->symbol_count++] = entry_lhs;


                DataContext* rhs = new_temp(arena);
                rhs->scope = current_table;
                rhs->scope_id = current_table->scope_id;

                SymbolEntry* entry_rhs = (SymbolEntry*)arena_alloc(arena,sizeof(SymbolEntry));
                entry_rhs->name = rhs->val.sval;
                entry_rhs->is_global = current_table->scope_id == 0 ? true : false;
                entry_rhs->type = TYPE_IDENTIFIER;

                current_table->entries[current_table->symbol_count++] = entry_rhs;


                DataContext* temp_ctx_lhs = (DataContext*)arena_alloc(arena,sizeof(DataContext));
                temp_ctx_lhs->type = TYPE_INT;
                temp_ctx_lhs->acquired_type = TYPE_INT;
                temp_ctx_lhs->scope = current_table;
                temp_ctx_lhs->scope_id = current_table->scope_id;
                temp_ctx_lhs->val.ival = 0;

                DataContext* temp_ctx_rhs = (DataContext*)arena_alloc(arena,sizeof(DataContext));
                temp_ctx_rhs->type = TYPE_INT;
                temp_ctx_rhs->acquired_type = TYPE_INT;
                temp_ctx_rhs->scope = current_table;
                temp_ctx_rhs->scope_id = current_table->scope_id;
                temp_ctx_rhs->val.ival = 0;

                OperatorContext* op_ctx_lhs = (OperatorContext*)arena_alloc(arena,sizeof(OperatorContext));
                op_ctx_lhs->operator_str = "=";
                op_ctx_lhs->operator_type = BL_EQUAL;

                OperatorContext* op_ctx_rhs = (OperatorContext*)arena_alloc(arena,sizeof(OperatorContext));
                op_ctx_rhs->operator_str = "=";
                op_ctx_rhs->operator_type = BL_EQUAL;


                OperatorContext* op_ctx = (OperatorContext*)arena_alloc(arena,sizeof(OperatorContext));
                op_ctx->operator_str = "*";
                op_ctx->operator_type = BL_MULTBINOP;

                OperatorContext* aop_ctx = (OperatorContext*)arena_alloc(arena,sizeof(OperatorContext));
                aop_ctx->operator_str = "=";
                aop_ctx->operator_type = BL_EQUAL;

                DataContext* temp_ctx = (DataContext*)arena_alloc(arena,sizeof(DataContext));
                temp_ctx->type = TYPE_INT;
                temp_ctx->scope = current_table;
                temp_ctx->scope_id = current_table->scope_id;
                temp_ctx->acquired_type = TYPE_INT;
                temp_ctx->val.ival = 0;
                tac_append(prog,tac_create_instr(arena,TAC_ASSIGNDECL,result,temp_ctx,NULL,NULL,NULL));
                tac_append(prog,tac_create_instr(arena,TAC_ASSIGNDECL,lhs,temp_ctx_lhs,NULL,NULL,NULL));
                tac_append(prog,tac_create_instr(arena,TAC_ASSIGN,lhs,left,NULL,op_ctx_lhs,NULL));
                tac_append(prog,tac_create_instr(arena,TAC_ASSIGNDECL,rhs,temp_ctx_rhs,NULL,NULL,NULL));
                tac_append(prog,tac_create_instr(arena,TAC_ASSIGN,rhs,right,NULL,op_ctx_rhs,NULL));
                tac_append(prog, tac_create_instr(arena, TAC_BINOP, result, lhs, rhs, op_ctx, NULL));
                tac_append(prog, tac_create_instr(arena, TAC_ASSIGN, ctx, result, NULL,aop_ctx, NULL));
            }else if(strcmp(op_ctx->operator_str,"/=") == 0){
                DataContext* left = ctx;
                DataContext* right = rhs;
                DataContext* result = new_temp(arena);
                result->scope = current_table;
                result->scope_id = current_table->scope_id;

                SymbolEntry* entry = (SymbolEntry*)arena_alloc(arena,sizeof(SymbolEntry));
                entry->name = result->val.sval;
                entry->is_global = current_table->scope_id == 0 ? true : false;
                entry->type = TYPE_IDENTIFIER;

                current_table->entries[current_table->symbol_count++] = entry;

                DataContext* lhs = new_temp(arena);
                lhs->scope = current_table;
                lhs->scope_id = current_table->scope_id;

                SymbolEntry* entry_lhs = (SymbolEntry*)arena_alloc(arena,sizeof(SymbolEntry));
                entry_lhs->name = lhs->val.sval;
                entry_lhs->is_global = current_table->scope_id == 0 ? true : false;
                entry_lhs->type = TYPE_IDENTIFIER;

                current_table->entries[current_table->symbol_count++] = entry_lhs;


                DataContext* rhs = new_temp(arena);
                rhs->scope = current_table;
                rhs->scope_id = current_table->scope_id;

                SymbolEntry* entry_rhs = (SymbolEntry*)arena_alloc(arena,sizeof(SymbolEntry));
                entry_rhs->name = rhs->val.sval;
                entry_rhs->is_global = current_table->scope_id == 0 ? true : false;
                entry_rhs->type = TYPE_IDENTIFIER;

                current_table->entries[current_table->symbol_count++] = entry_rhs;


                DataContext* temp_ctx_lhs = (DataContext*)arena_alloc(arena,sizeof(DataContext));
                temp_ctx_lhs->type = TYPE_INT;
                temp_ctx_lhs->acquired_type = TYPE_INT;
                temp_ctx_lhs->scope = current_table;
                temp_ctx_lhs->scope_id = current_table->scope_id;
                temp_ctx_lhs->val.ival = 0;

                DataContext* temp_ctx_rhs = (DataContext*)arena_alloc(arena,sizeof(DataContext));
                temp_ctx_rhs->type = TYPE_INT;
                temp_ctx_rhs->acquired_type = TYPE_INT;
                temp_ctx_rhs->scope = current_table;
                temp_ctx_rhs->scope_id = current_table->scope_id;
                temp_ctx_rhs->val.ival = 0;

                OperatorContext* op_ctx_lhs = (OperatorContext*)arena_alloc(arena,sizeof(OperatorContext));
                op_ctx_lhs->operator_str = "=";
                op_ctx_lhs->operator_type = BL_EQUAL;

                OperatorContext* op_ctx_rhs = (OperatorContext*)arena_alloc(arena,sizeof(OperatorContext));
                op_ctx_rhs->operator_str = "=";
                op_ctx_rhs->operator_type = BL_EQUAL;


                OperatorContext* op_ctx = (OperatorContext*)arena_alloc(arena,sizeof(OperatorContext));
                op_ctx->operator_str = "/";
                op_ctx->operator_type = BL_DIVBINOP;

                OperatorContext* aop_ctx = (OperatorContext*)arena_alloc(arena,sizeof(OperatorContext));
                aop_ctx->operator_str = "=";
                aop_ctx->operator_type = BL_EQUAL;

                DataContext* temp_ctx = (DataContext*)arena_alloc(arena,sizeof(DataContext));
                temp_ctx->type = TYPE_INT;
                temp_ctx->scope = current_table;
                temp_ctx->scope_id = current_table->scope_id;
                temp_ctx->acquired_type = TYPE_INT;
                temp_ctx->val.ival = 0;
                tac_append(prog,tac_create_instr(arena,TAC_ASSIGNDECL,result,temp_ctx,NULL,NULL,NULL));
                tac_append(prog,tac_create_instr(arena,TAC_ASSIGNDECL,lhs,temp_ctx_lhs,NULL,NULL,NULL));
                tac_append(prog,tac_create_instr(arena,TAC_ASSIGN,lhs,left,NULL,op_ctx_lhs,NULL));
                tac_append(prog,tac_create_instr(arena,TAC_ASSIGNDECL,rhs,temp_ctx_rhs,NULL,NULL,NULL));
                tac_append(prog,tac_create_instr(arena,TAC_ASSIGN,rhs,right,NULL,op_ctx_rhs,NULL));
                tac_append(prog, tac_create_instr(arena, TAC_BINOP, result, lhs, rhs, op_ctx, NULL));
                tac_append(prog, tac_create_instr(arena, TAC_ASSIGN, ctx, result, NULL,aop_ctx, NULL));
            }else if(strcmp(op_ctx->operator_str,"&=") == 0){
                DataContext* left = ctx;
                DataContext* right = rhs;
                DataContext* result = new_temp(arena);
                result->scope = current_table;
                result->scope_id = current_table->scope_id;

                SymbolEntry* entry = (SymbolEntry*)arena_alloc(arena,sizeof(SymbolEntry));
                entry->name = result->val.sval;
                entry->is_global = current_table->scope_id == 0 ? true : false;
                entry->type = TYPE_IDENTIFIER;

                current_table->entries[current_table->symbol_count++] = entry;

                DataContext* lhs = new_temp(arena);
                lhs->scope = current_table;
                lhs->scope_id = current_table->scope_id;

                SymbolEntry* entry_lhs = (SymbolEntry*)arena_alloc(arena,sizeof(SymbolEntry));
                entry_lhs->name = lhs->val.sval;
                entry_lhs->is_global = current_table->scope_id == 0 ? true : false;
                entry_lhs->type = TYPE_IDENTIFIER;

                current_table->entries[current_table->symbol_count++] = entry_lhs;


                DataContext* rhs = new_temp(arena);
                rhs->scope = current_table;
                rhs->scope_id = current_table->scope_id;

                SymbolEntry* entry_rhs = (SymbolEntry*)arena_alloc(arena,sizeof(SymbolEntry));
                entry_rhs->name = rhs->val.sval;
                entry_rhs->is_global = current_table->scope_id == 0 ? true : false;
                entry_rhs->type = TYPE_IDENTIFIER;

                current_table->entries[current_table->symbol_count++] = entry_rhs;


                DataContext* temp_ctx_lhs = (DataContext*)arena_alloc(arena,sizeof(DataContext));
                temp_ctx_lhs->type = TYPE_INT;
                temp_ctx_lhs->acquired_type = TYPE_INT;
                temp_ctx_lhs->scope = current_table;
                temp_ctx_lhs->scope_id = current_table->scope_id;
                temp_ctx_lhs->val.ival = 0;

                DataContext* temp_ctx_rhs = (DataContext*)arena_alloc(arena,sizeof(DataContext));
                temp_ctx_rhs->type = TYPE_INT;
                temp_ctx_rhs->acquired_type = TYPE_INT;
                temp_ctx_rhs->scope = current_table;
                temp_ctx_rhs->scope_id = current_table->scope_id;
                temp_ctx_rhs->val.ival = 0;

                OperatorContext* op_ctx_lhs = (OperatorContext*)arena_alloc(arena,sizeof(OperatorContext));
                op_ctx_lhs->operator_str = "=";
                op_ctx_lhs->operator_type = BL_EQUAL;

                OperatorContext* op_ctx_rhs = (OperatorContext*)arena_alloc(arena,sizeof(OperatorContext));
                op_ctx_rhs->operator_str = "=";
                op_ctx_rhs->operator_type = BL_EQUAL;


                OperatorContext* op_ctx = (OperatorContext*)arena_alloc(arena,sizeof(OperatorContext));
                op_ctx->operator_str = "&";
                op_ctx->operator_type = BL_AND;

                OperatorContext* aop_ctx = (OperatorContext*)arena_alloc(arena,sizeof(OperatorContext));
                aop_ctx->operator_str = "=";
                aop_ctx->operator_type = BL_EQUAL;

                DataContext* temp_ctx = (DataContext*)arena_alloc(arena,sizeof(DataContext));
                temp_ctx->type = TYPE_INT;
                temp_ctx->scope = current_table;
                temp_ctx->scope_id = current_table->scope_id;
                temp_ctx->acquired_type = TYPE_INT;
                temp_ctx->val.ival = 0;
                tac_append(prog,tac_create_instr(arena,TAC_ASSIGNDECL,result,temp_ctx,NULL,NULL,NULL));
                tac_append(prog,tac_create_instr(arena,TAC_ASSIGNDECL,lhs,temp_ctx_lhs,NULL,NULL,NULL));
                tac_append(prog,tac_create_instr(arena,TAC_ASSIGN,lhs,left,NULL,op_ctx_lhs,NULL));
                tac_append(prog,tac_create_instr(arena,TAC_ASSIGNDECL,rhs,temp_ctx_rhs,NULL,NULL,NULL));
                tac_append(prog,tac_create_instr(arena,TAC_ASSIGN,rhs,right,NULL,op_ctx_rhs,NULL));
                tac_append(prog, tac_create_instr(arena, TAC_BINOP, result, lhs, rhs, op_ctx, NULL));
                tac_append(prog, tac_create_instr(arena, TAC_ASSIGN, ctx, result, NULL,aop_ctx, NULL));
            }else if(strcmp(op_ctx->operator_str,"^=") == 0){
                DataContext* left = ctx;
                DataContext* right = rhs;
                DataContext* result = new_temp(arena);
                result->scope = current_table;
                result->scope_id = current_table->scope_id;

                SymbolEntry* entry = (SymbolEntry*)arena_alloc(arena,sizeof(SymbolEntry));
                entry->name = result->val.sval;
                entry->is_global = current_table->scope_id == 0 ? true : false;
                entry->type = TYPE_IDENTIFIER;

                current_table->entries[current_table->symbol_count++] = entry;

                DataContext* lhs = new_temp(arena);
                lhs->scope = current_table;
                lhs->scope_id = current_table->scope_id;

                SymbolEntry* entry_lhs = (SymbolEntry*)arena_alloc(arena,sizeof(SymbolEntry));
                entry_lhs->name = lhs->val.sval;
                entry_lhs->is_global = current_table->scope_id == 0 ? true : false;
                entry_lhs->type = TYPE_IDENTIFIER;

                current_table->entries[current_table->symbol_count++] = entry_lhs;


                DataContext* rhs = new_temp(arena);
                rhs->scope = current_table;
                rhs->scope_id = current_table->scope_id;

                SymbolEntry* entry_rhs = (SymbolEntry*)arena_alloc(arena,sizeof(SymbolEntry));
                entry_rhs->name = rhs->val.sval;
                entry_rhs->is_global = current_table->scope_id == 0 ? true : false;
                entry_rhs->type = TYPE_IDENTIFIER;

                current_table->entries[current_table->symbol_count++] = entry_rhs;


                DataContext* temp_ctx_lhs = (DataContext*)arena_alloc(arena,sizeof(DataContext));
                temp_ctx_lhs->type = TYPE_INT;
                temp_ctx_lhs->acquired_type = TYPE_INT;
                temp_ctx_lhs->scope = current_table;
                temp_ctx_lhs->scope_id = current_table->scope_id;
                temp_ctx_lhs->val.ival = 0;

                DataContext* temp_ctx_rhs = (DataContext*)arena_alloc(arena,sizeof(DataContext));
                temp_ctx_rhs->type = TYPE_INT;
                temp_ctx_rhs->acquired_type = TYPE_INT;
                temp_ctx_rhs->scope = current_table;
                temp_ctx_rhs->scope_id = current_table->scope_id;
                temp_ctx_rhs->val.ival = 0;

                OperatorContext* op_ctx_lhs = (OperatorContext*)arena_alloc(arena,sizeof(OperatorContext));
                op_ctx_lhs->operator_str = "=";
                op_ctx_lhs->operator_type = BL_EQUAL;

                OperatorContext* op_ctx_rhs = (OperatorContext*)arena_alloc(arena,sizeof(OperatorContext));
                op_ctx_rhs->operator_str = "=";
                op_ctx_rhs->operator_type = BL_EQUAL;


                OperatorContext* op_ctx = (OperatorContext*)arena_alloc(arena,sizeof(OperatorContext));
                op_ctx->operator_str = "^";
                op_ctx->operator_type = BL_XOR;

                OperatorContext* aop_ctx = (OperatorContext*)arena_alloc(arena,sizeof(OperatorContext));
                aop_ctx->operator_str = "=";
                aop_ctx->operator_type = BL_EQUAL;

                DataContext* temp_ctx = (DataContext*)arena_alloc(arena,sizeof(DataContext));
                temp_ctx->type = TYPE_INT;
                temp_ctx->scope = current_table;
                temp_ctx->scope_id = current_table->scope_id;
                temp_ctx->acquired_type = TYPE_INT;
                temp_ctx->val.ival = 0;
                tac_append(prog,tac_create_instr(arena,TAC_ASSIGNDECL,result,temp_ctx,NULL,NULL,NULL));
                tac_append(prog,tac_create_instr(arena,TAC_ASSIGNDECL,lhs,temp_ctx_lhs,NULL,NULL,NULL));
                tac_append(prog,tac_create_instr(arena,TAC_ASSIGN,lhs,left,NULL,op_ctx_lhs,NULL));
                tac_append(prog,tac_create_instr(arena,TAC_ASSIGNDECL,rhs,temp_ctx_rhs,NULL,NULL,NULL));
                tac_append(prog,tac_create_instr(arena,TAC_ASSIGN,rhs,right,NULL,op_ctx_rhs,NULL));
                tac_append(prog, tac_create_instr(arena, TAC_BINOP, result, lhs, rhs, op_ctx, NULL));
                tac_append(prog, tac_create_instr(arena, TAC_ASSIGN, ctx, result, NULL,aop_ctx, NULL));
            }else if(strcmp(op_ctx->operator_str,"%=") == 0){
                DataContext* left = ctx;
                DataContext* right = rhs;
                DataContext* result = new_temp(arena);
                result->scope = current_table;
                result->scope_id = current_table->scope_id;

                SymbolEntry* entry = (SymbolEntry*)arena_alloc(arena,sizeof(SymbolEntry));
                entry->name = result->val.sval;
                entry->is_global = current_table->scope_id == 0 ? true : false;
                entry->type = TYPE_IDENTIFIER;

                current_table->entries[current_table->symbol_count++] = entry;

                DataContext* lhs = new_temp(arena);
                lhs->scope = current_table;
                lhs->scope_id = current_table->scope_id;

                SymbolEntry* entry_lhs = (SymbolEntry*)arena_alloc(arena,sizeof(SymbolEntry));
                entry_lhs->name = lhs->val.sval;
                entry_lhs->is_global = current_table->scope_id == 0 ? true : false;
                entry_lhs->type = TYPE_IDENTIFIER;

                current_table->entries[current_table->symbol_count++] = entry_lhs;


                DataContext* rhs = new_temp(arena);
                rhs->scope = current_table;
                rhs->scope_id = current_table->scope_id;

                SymbolEntry* entry_rhs = (SymbolEntry*)arena_alloc(arena,sizeof(SymbolEntry));
                entry_rhs->name = rhs->val.sval;
                entry_rhs->is_global = current_table->scope_id == 0 ? true : false;
                entry_rhs->type = TYPE_IDENTIFIER;

                current_table->entries[current_table->symbol_count++] = entry_rhs;


                DataContext* temp_ctx_lhs = (DataContext*)arena_alloc(arena,sizeof(DataContext));
                temp_ctx_lhs->type = TYPE_INT;
                temp_ctx_lhs->acquired_type = TYPE_INT;
                temp_ctx_lhs->scope = current_table;
                temp_ctx_lhs->scope_id = current_table->scope_id;
                temp_ctx_lhs->val.ival = 0;

                DataContext* temp_ctx_rhs = (DataContext*)arena_alloc(arena,sizeof(DataContext));
                temp_ctx_rhs->type = TYPE_INT;
                temp_ctx_rhs->acquired_type = TYPE_INT;
                temp_ctx_rhs->scope = current_table;
                temp_ctx_rhs->scope_id = current_table->scope_id;
                temp_ctx_rhs->val.ival = 0;

                OperatorContext* op_ctx_lhs = (OperatorContext*)arena_alloc(arena,sizeof(OperatorContext));
                op_ctx_lhs->operator_str = "=";
                op_ctx_lhs->operator_type = BL_EQUAL;

                OperatorContext* op_ctx_rhs = (OperatorContext*)arena_alloc(arena,sizeof(OperatorContext));
                op_ctx_rhs->operator_str = "=";
                op_ctx_rhs->operator_type = BL_EQUAL;


                OperatorContext* op_ctx = (OperatorContext*)arena_alloc(arena,sizeof(OperatorContext));
                op_ctx->operator_str = "%";
                op_ctx->operator_type = BL_MODBINOP;

                OperatorContext* aop_ctx = (OperatorContext*)arena_alloc(arena,sizeof(OperatorContext));
                aop_ctx->operator_str = "=";
                aop_ctx->operator_type = BL_EQUAL;

                DataContext* temp_ctx = (DataContext*)arena_alloc(arena,sizeof(DataContext));
                temp_ctx->type = TYPE_INT;
                temp_ctx->scope = current_table;
                temp_ctx->scope_id = current_table->scope_id;
                temp_ctx->acquired_type = TYPE_INT;
                temp_ctx->val.ival = 0;
                tac_append(prog,tac_create_instr(arena,TAC_ASSIGNDECL,result,temp_ctx,NULL,NULL,NULL));
                tac_append(prog,tac_create_instr(arena,TAC_ASSIGNDECL,lhs,temp_ctx_lhs,NULL,NULL,NULL));
                tac_append(prog,tac_create_instr(arena,TAC_ASSIGN,lhs,left,NULL,op_ctx_lhs,NULL));
                tac_append(prog,tac_create_instr(arena,TAC_ASSIGNDECL,rhs,temp_ctx_rhs,NULL,NULL,NULL));
                tac_append(prog,tac_create_instr(arena,TAC_ASSIGN,rhs,right,NULL,op_ctx_rhs,NULL));
                tac_append(prog, tac_create_instr(arena, TAC_BINOP, result, lhs, rhs, op_ctx, NULL));
                tac_append(prog, tac_create_instr(arena, TAC_ASSIGN, ctx, result, NULL,aop_ctx, NULL));
            }else if(strcmp(op_ctx->operator_str,"|=") == 0){
                DataContext* left = ctx;
                DataContext* right = rhs;
                DataContext* result = new_temp(arena);
                result->scope = current_table;
                result->scope_id = current_table->scope_id;

                SymbolEntry* entry = (SymbolEntry*)arena_alloc(arena,sizeof(SymbolEntry));
                entry->name = result->val.sval;
                entry->is_global = current_table->scope_id == 0 ? true : false;
                entry->type = TYPE_IDENTIFIER;

                current_table->entries[current_table->symbol_count++] = entry;

                DataContext* lhs = new_temp(arena);
                lhs->scope = current_table;
                lhs->scope_id = current_table->scope_id;

                SymbolEntry* entry_lhs = (SymbolEntry*)arena_alloc(arena,sizeof(SymbolEntry));
                entry_lhs->name = lhs->val.sval;
                entry_lhs->is_global = current_table->scope_id == 0 ? true : false;
                entry_lhs->type = TYPE_IDENTIFIER;

                current_table->entries[current_table->symbol_count++] = entry_lhs;


                DataContext* rhs = new_temp(arena);
                rhs->scope = current_table;
                rhs->scope_id = current_table->scope_id;

                SymbolEntry* entry_rhs = (SymbolEntry*)arena_alloc(arena,sizeof(SymbolEntry));
                entry_rhs->name = rhs->val.sval;
                entry_rhs->is_global = current_table->scope_id == 0 ? true : false;
                entry_rhs->type = TYPE_IDENTIFIER;

                current_table->entries[current_table->symbol_count++] = entry_rhs;


                DataContext* temp_ctx_lhs = (DataContext*)arena_alloc(arena,sizeof(DataContext));
                temp_ctx_lhs->type = TYPE_INT;
                temp_ctx_lhs->acquired_type = TYPE_INT;
                temp_ctx_lhs->scope = current_table;
                temp_ctx_lhs->scope_id = current_table->scope_id;
                temp_ctx_lhs->val.ival = 0;

                DataContext* temp_ctx_rhs = (DataContext*)arena_alloc(arena,sizeof(DataContext));
                temp_ctx_rhs->type = TYPE_INT;
                temp_ctx_rhs->acquired_type = TYPE_INT;
                temp_ctx_rhs->scope = current_table;
                temp_ctx_rhs->scope_id = current_table->scope_id;
                temp_ctx_rhs->val.ival = 0;

                OperatorContext* op_ctx_lhs = (OperatorContext*)arena_alloc(arena,sizeof(OperatorContext));
                op_ctx_lhs->operator_str = "=";
                op_ctx_lhs->operator_type = BL_EQUAL;

                OperatorContext* op_ctx_rhs = (OperatorContext*)arena_alloc(arena,sizeof(OperatorContext));
                op_ctx_rhs->operator_str = "=";
                op_ctx_rhs->operator_type = BL_EQUAL;


                OperatorContext* op_ctx = (OperatorContext*)arena_alloc(arena,sizeof(OperatorContext));
                op_ctx->operator_str = "|";
                op_ctx->operator_type = BL_OR;

                OperatorContext* aop_ctx = (OperatorContext*)arena_alloc(arena,sizeof(OperatorContext));
                aop_ctx->operator_str = "=";
                aop_ctx->operator_type = BL_EQUAL;

                DataContext* temp_ctx = (DataContext*)arena_alloc(arena,sizeof(DataContext));
                temp_ctx->type = TYPE_INT;
                temp_ctx->scope = current_table;
                temp_ctx->scope_id = current_table->scope_id;
                temp_ctx->acquired_type = TYPE_INT;
                temp_ctx->val.ival = 0;
                tac_append(prog,tac_create_instr(arena,TAC_ASSIGNDECL,result,temp_ctx,NULL,NULL,NULL));
                tac_append(prog,tac_create_instr(arena,TAC_ASSIGNDECL,lhs,temp_ctx_lhs,NULL,NULL,NULL));
                tac_append(prog,tac_create_instr(arena,TAC_ASSIGN,lhs,left,NULL,op_ctx_lhs,NULL));
                tac_append(prog,tac_create_instr(arena,TAC_ASSIGNDECL,rhs,temp_ctx_rhs,NULL,NULL,NULL));
                tac_append(prog,tac_create_instr(arena,TAC_ASSIGN,rhs,right,NULL,op_ctx_rhs,NULL));
                tac_append(prog, tac_create_instr(arena, TAC_BINOP, result, lhs, rhs, op_ctx, NULL));
                tac_append(prog, tac_create_instr(arena, TAC_ASSIGN, ctx, result, NULL,aop_ctx, NULL));
            }
            else{
                fprintf(stderr,"Unknown assignment operator, got `%s`\n",op_ctx->operator_str);
                exit(1);
            }

            return ctx;
        }

        case AST_ASSIGNDECL: {
            AST_Assign* asg = (AST_Assign*)node->data;
            DataContext* ctx = (DataContext*)arena_alloc(arena, sizeof(DataContext));

            if (asg->rhs) {
                DataContext* rhs = gen_tac(asg->rhs, prog, slist,current_table,arena, loop_ctx);

                if (asg->lhs->type == AST_UNOP && (((AST_Unop*)asg->lhs->data)->op == (enum KEYWORD_TYPES)BL_KW_BHAU_REF || ((AST_Unop*)asg->lhs->data)->op == (enum KEYWORD_TYPES)BL_KW_BHAU_PTR)) {
                    fprintf(stderr, "Pointer or Reference cannot be on the left side of assignment\n");
                    exit(69);
                }

                
                AST_Identifier* ident = (AST_Identifier*)asg->lhs->data;
                ctx->val.sval = ident->name;
                ctx->type = TYPE_IDENTIFIER;
                ctx->acquired_type = TYPE_IDENTIFIER;
                ctx->scope = current_table;
                ctx->scope_id = current_table->scope_id;

                SymbolEntry* entry = (SymbolEntry*)arena_alloc(arena,sizeof(SymbolEntry));
                entry->name = ctx->val.sval;
                entry->is_global = current_table->scope_id == 0 ? true : false;
                if(rhs->type == TYPE_STRING){
                    entry->string_val = rhs->val.sval;
                    entry->type = rhs->type;
                }else{
                    entry->type = TYPE_IDENTIFIER;
                }

                if(entry->is_global){
                    entry->type = rhs->type;
                    if(entry->type == TYPE_INT){
                        entry->int_val = rhs->val.ival;
                    }else if(entry->type == TYPE_FLOAT){
                        entry->float_val = rhs->val.fval;
                    }else if(entry->type == TYPE_CHAR){
                        entry->char_val = rhs->val.cval;
                    }else if(entry->type == TYPE_STRING){
                        entry->string_val = rhs->val.sval;
                    }else if(entry->type == TYPE_BOOL){
                        entry->bool_val = rhs->val.bval;
                    }else{
                        fprintf(stderr,"Unknown declaration type in global scope; Declaration can only be int, float, char, string and bool\n");
                        exit(1);
                    }
                }else{
                    entry->type = rhs->type;
                    if(entry->type == TYPE_INT){
                        entry->int_val = rhs->val.ival;
                    }else if(entry->type == TYPE_FLOAT){
                        entry->float_val = rhs->val.fval;
                    }else if(entry->type == TYPE_CHAR){
                        entry->char_val = rhs->val.cval;
                    }else if(entry->type == TYPE_STRING){
                        entry->string_val = rhs->val.sval;
                    }else if(entry->type == TYPE_BOOL){
                        entry->bool_val = rhs->val.bval;
                    }
                }

                current_table->entries[current_table->symbol_count++] = entry;

                tac_append(prog, tac_create_instr(arena, TAC_ASSIGNDECL, ctx, rhs, NULL, NULL, NULL));
                return ctx;
            } else {
                if (asg->lhs->type == AST_UNOP &&( ((AST_Unop*)asg->lhs->data)->op == (enum KEYWORD_TYPES)BL_KW_BHAU_REF || ((AST_Unop*)asg->lhs->data)->op == (enum KEYWORD_TYPES)BL_KW_BHAU_PTR)) {
                    fprintf(stderr, "Reference cannot be on the left side of assignment\n");
                    exit(69);
                }

                AST_Identifier* ident = (AST_Identifier*)asg->lhs->data;
                ctx->val.sval = ident->name;
                ctx->type = TYPE_IDENTIFIER;
                ctx->acquired_type = TYPE_IDENTIFIER;

                ctx->scope = current_table;
                ctx->scope_id = current_table->scope_id;

                SymbolEntry* entry = (SymbolEntry*)arena_alloc(arena,sizeof(SymbolEntry));
                entry->name = ctx->val.sval;
                entry->is_global = current_table->scope_id == 0 ? true : false;
                entry->type = TYPE_IDENTIFIER;
                if(entry->is_global){
                    entry->type = TYPE_UNDECLARED;
                }

                current_table->entries[current_table->symbol_count++] = entry;

                tac_append(prog, tac_create_instr(arena, TAC_ASSIGNDECL, ctx, NULL, NULL, NULL, NULL));
                return ctx;
            }
        }

        case AST_MAIN: {
            AST_Main* fn = (AST_Main*)node->data;
            SymbolTable* main_table = (SymbolTable*)arena_alloc(arena,sizeof(SymbolTable));
            main_table->parent = current_table;
            main_table->children = (SymbolTable**)arena_alloc(arena,sizeof(SymbolTable*)*128);
            main_table->symbol_capacity = 1024;
            main_table->entries = (SymbolEntry**)arena_alloc(arena,sizeof(SymbolEntry*)*1024);
            main_table->scope_id = ++scope_id_counter;
            main_table->scope_name = "main";
            main_table->symbol_count = 0;
            main_table->children_count = 0;
            current_table->children[current_table->children_count++] = main_table;
            slist->tables[slist->table_count++] = main_table;

            tac_append(prog, tac_create_instr(arena, TAC_MAIN_BEGIN, NULL, NULL, NULL, NULL, "main"));
            gen_tac(fn->block, prog, slist,main_table,arena,loop_ctx);
            tac_append(prog, tac_create_instr(arena, TAC_MAIN_END, NULL, NULL, NULL, NULL, NULL));
            return NULL;
        }

        case AST_BLOCK: {
                AST_Block* blk = (AST_Block*)node->data;

            for (size_t i = 0; i < blk->body_count; ++i) {
                gen_tac(blk->body[i], prog,slist,current_table, arena,loop_ctx);
            }
            return NULL;
        }

        case AST_RETURN: {
            AST_Return* ret = (AST_Return*)node->data;
            DataContext* val = gen_tac(ret->expr, prog,slist,current_table, arena,loop_ctx);
            if(val->type == TYPE_STRING && val->scope_id != 0){
                fprintf(stderr,"Cannot return strings, since a pointer to string is returned and the stack frame gets destroyed after function call ends,got \"%s\"\n",val->val.sval);
                exit(1);
            }
            DataContext* result = new_temp(arena);

            result->scope = current_table;
            result->scope_id = current_table->scope_id;

            SymbolEntry* entry = (SymbolEntry*)arena_alloc(arena,sizeof(SymbolEntry));
            entry->name = result->val.sval;
            entry->is_global = current_table->scope_id == 0 ? true : false;
            entry->type = TYPE_ARG;
               
            current_table->entries[current_table->symbol_count++] = entry;


            tac_append(prog,tac_create_instr(arena,TAC_ASSIGNDECL,result,val,NULL,NULL,NULL));
            tac_append(prog, tac_create_instr(arena, TAC_RETURN, NULL, result, NULL, NULL, NULL));
            return NULL;
        }

        case AST_IFELSE: {
            AST_Ifelse* ifs = (AST_Ifelse*)node->data;
            DataContext* cond = gen_tac(ifs->condition, prog,slist,current_table, arena,loop_ctx);
            char* then_label = new_label(arena);
            char* end_label  = new_label(arena);

            DataContext* zero_ctx = (DataContext*)arena_alloc(arena,sizeof(DataContext));
            zero_ctx->val.ival = 0;
            zero_ctx->type = TYPE_INT;
            zero_ctx->scope = current_table;
            zero_ctx->scope_id = current_table->scope_id;
            zero_ctx->acquired_type = TYPE_INT;

            OperatorContext* op_ctx = (OperatorContext*)arena_alloc(arena,sizeof(OperatorContext));
            op_ctx->operator_str = "!=";
            op_ctx->operator_type = BL_NOTEQ;

            tac_append(prog, tac_create_instr(arena, TAC_IFGOTO, NULL, cond, zero_ctx, op_ctx, then_label));

            if (ifs->else_block) {

                SymbolTable* else_table = (SymbolTable*)arena_alloc(arena,sizeof(SymbolTable));
                else_table->parent = current_table;
                else_table->children = (SymbolTable**)arena_alloc(arena,sizeof(SymbolTable*)*128);
                else_table->symbol_capacity = 1024;
                else_table->entries = (SymbolEntry**)arena_alloc(arena,sizeof(SymbolEntry*)*1024);
                else_table->scope_id = ++scope_id_counter;
                else_table->scope_name = "null";
                else_table->symbol_count = 0;
                else_table->children_count = 0;
                current_table->children[current_table->children_count++] = else_table;
                slist->tables[slist->table_count++] = else_table;

                gen_tac(ifs->else_block, prog,slist,else_table, arena,loop_ctx);
                tac_append(prog, tac_create_instr(arena, TAC_GOTO, NULL, NULL, NULL, NULL, end_label));
            }else{
                tac_append(prog,tac_create_instr(arena, TAC_GOTO,NULL,NULL,NULL,NULL,end_label));
            }

            tac_append(prog, tac_create_instr(arena, TAC_LABEL, NULL, NULL, NULL, NULL, then_label));

            SymbolTable* if_table = (SymbolTable*)arena_alloc(arena,sizeof(SymbolTable));
            if_table->parent = current_table;
            if_table->children = (SymbolTable**)arena_alloc(arena,sizeof(SymbolTable*)*128);
            if_table->symbol_capacity = 1024;
            if_table->entries = (SymbolEntry**)arena_alloc(arena,sizeof(SymbolEntry*)*1024);
            if_table->scope_id = ++scope_id_counter;
            if_table->scope_name = "null";
            if_table->symbol_count = 0;
            if_table->children_count = 0;
            current_table->children[current_table->children_count++] = if_table;
            slist->tables[slist->table_count++] = if_table;

            gen_tac(ifs->then_block, prog,slist,if_table, arena,loop_ctx);

            tac_append(prog, tac_create_instr(arena, TAC_LABEL, NULL, NULL, NULL, NULL, end_label));
            return NULL;
        }

        case AST_LOOP: {
            AST_Loop* loop = (AST_Loop*)node->data;

            char* cond_label = new_label(arena);
            char* body_label = new_label(arena);
            char* end_label  = new_label(arena);

            DataContext* zero_ctx = (DataContext*)arena_alloc(arena,sizeof(DataContext));
            zero_ctx->val.ival = 0;
            zero_ctx->type = TYPE_INT;
            zero_ctx->scope = current_table;
            zero_ctx->scope_id = current_table->scope_id;
            zero_ctx->acquired_type = TYPE_INT;

            LoopContext* new_ctx = (LoopContext*)arena_alloc(arena,sizeof(LoopContext));
            new_ctx->break_label = end_label,
            new_ctx->continue_label = cond_label;
            new_ctx->prev = loop_ctx;

            tac_append(prog, tac_create_instr(arena, TAC_LABEL, NULL, NULL, NULL, NULL, cond_label));

            OperatorContext* op_ctx = (OperatorContext*)arena_alloc(arena,sizeof(OperatorContext));
            op_ctx->operator_str = "!=";
            op_ctx->operator_type = BL_NOTEQ;

            DataContext* cond = gen_tac(loop->expr, prog,slist,current_table, arena, new_ctx);
            tac_append(prog, tac_create_instr(arena, TAC_IFGOTO, NULL, cond, zero_ctx, op_ctx, body_label));
            
            tac_append(prog, tac_create_instr(arena, TAC_GOTO, NULL, NULL, NULL, NULL, end_label));

            tac_append(prog, tac_create_instr(arena, TAC_LABEL, NULL, NULL, NULL, NULL, body_label));

            SymbolTable* loop_table = (SymbolTable*)arena_alloc(arena,sizeof(SymbolTable));
            loop_table->parent = current_table;
            loop_table->children = (SymbolTable**)arena_alloc(arena,sizeof(SymbolTable*)*128);
            loop_table->symbol_capacity = 1024;
            loop_table->entries = (SymbolEntry**)arena_alloc(arena,sizeof(SymbolEntry*)*1024);
            loop_table->scope_id = ++scope_id_counter;
            loop_table->scope_name = "null";
            loop_table->symbol_count = 0;
            loop_table->children_count = 0;
            current_table->children[current_table->children_count++] = loop_table;
            slist->tables[slist->table_count++] = loop_table;

            gen_tac(loop->block, prog,slist,loop_table, arena, new_ctx);
            

            tac_append(prog, tac_create_instr(arena, TAC_GOTO, NULL, NULL, NULL, NULL, cond_label));

            tac_append(prog, tac_create_instr(arena, TAC_LABEL, NULL, NULL, NULL, NULL, end_label));
            return NULL;
        }

        case AST_BREAK: {
            if (!loop_ctx) {
                fprintf(stderr, "FILE : %s LINE : %d Error: 'break' used outside of switch or loop.\n",__FILE__,__LINE__);
                exit(1);
            }
            tac_append(prog, tac_create_instr(arena, TAC_GOTO, NULL, NULL, NULL, NULL, loop_ctx->break_label));
            return NULL;
        }

        case AST_CONTINUE: {
            if (!loop_ctx) {
                fprintf(stderr, "Error: 'continue' used outside of loop.\n");
                exit(1);
            }
            if(!loop_ctx->continue_label){
                fprintf(stderr,"Error: `continue` cannot be used in switch.\n");
                exit(1);
            }

            tac_append(prog, tac_create_instr(arena, TAC_GOTO, NULL, NULL, NULL, NULL, loop_ctx->continue_label));
            return NULL;
        }

        case AST_FUNCTION: {
            AST_Function* fn = (AST_Function*)node->data;
            AST_Identifier* name = (AST_Identifier*)fn->name->data;

            SymbolTable* func_table = (SymbolTable*)arena_alloc(arena,sizeof(SymbolTable));
            func_table->parent = current_table;
            func_table->children = (SymbolTable**)arena_alloc(arena,sizeof(SymbolTable*)*128);
            func_table->symbol_capacity = 1024;
            func_table->entries = (SymbolEntry**)arena_alloc(arena,sizeof(SymbolEntry*)*1024);
            func_table->scope_id = ++scope_id_counter;
            func_table->scope_name = name->name;
            func_table->symbol_count = 0;
            func_table->children_count = 0;
            current_table->children[current_table->children_count++] = func_table;
            slist->tables[slist->table_count++] = func_table;

            tac_append(prog, tac_create_instr(arena, TAC_FUNC_BEGIN, NULL, NULL, NULL, NULL, name->name));

            for (int i = 0; i < (int)fn->param_count; ++i) {
                char* param = ((AST_Identifier*)((AST_Node*)((AST_Param*)fn->params[i]->data)->ident)->data)->name;
                DataContext* param_ctx = (DataContext*)arena_alloc(arena,sizeof(DataContext));
                param_ctx->val.sval = param;
                param_ctx->type = TYPE_IDENTIFIER;
                param_ctx->acquired_type = TYPE_IDENTIFIER;
                param_ctx->scope = func_table;
                param_ctx->scope_id = func_table->scope_id;


                SymbolEntry* entry = (SymbolEntry*)arena_alloc(arena,sizeof(SymbolEntry));
                entry->is_global = 0;
                entry->name = param_ctx->val.sval;
                entry->type = TYPE_PARAM;

                func_table->entries[func_table->symbol_count++] = entry;
                tac_append(prog, tac_create_instr(arena, TAC_PARAM, NULL, param_ctx, NULL, NULL, NULL));
            }

            gen_tac(fn->block, prog,slist,func_table, arena,loop_ctx);
            tac_append(prog, tac_create_instr(arena, TAC_FUNC_END, NULL, NULL, NULL, NULL, NULL));
            return NULL;
        }

        case AST_FUNCTIONCALL: {
            AST_FunctionCall* call = (AST_FunctionCall*)node->data;
            int is_float = 0;
            for (int i = 0; i < call->args_count; ++i) {
                DataContext* result = new_temp(arena);

                result->scope = current_table;
                result->scope_id = current_table->scope_id;

                SymbolEntry* entry = (SymbolEntry*)arena_alloc(arena,sizeof(SymbolEntry));
                entry->name = result->val.sval;
                entry->is_global = current_table->scope_id == 0 ? true : false;
                entry->type = TYPE_ARG;
                DataContext* arg = gen_tac(call->args[i], prog,slist,current_table, arena, loop_ctx);
                if(arg->acquired_type == TYPE_STRING){
                    entry->string_val = arg->val.sval;
                }
                if(arg->acquired_type == TYPE_FLOAT){
                    is_float = 1;
                }
                current_table->entries[current_table->symbol_count++] = entry;

                DataContext* temp_ctx = (DataContext*)arena_alloc(arena,sizeof(DataContext));
                temp_ctx->type = TYPE_INT;
                temp_ctx->acquired_type = TYPE_INT;
                temp_ctx->scope = current_table;
                temp_ctx->scope_id = current_table->scope_id;
                temp_ctx->val.ival = 0;

                OperatorContext* op_ctx = (OperatorContext*)arena_alloc(arena,sizeof(OperatorContext));
                op_ctx->operator_str = "=";
                op_ctx->operator_type = BL_EQUAL;

                tac_append(prog,tac_create_instr(arena,TAC_ASSIGNDECL,result,arg,NULL,NULL,NULL));
                tac_append(prog, tac_create_instr(arena, TAC_ARG, NULL, result, NULL, NULL, NULL));
            }

            DataContext* result = new_temp(arena);
            result->scope = current_table;
            result->scope_id = current_table->scope_id;

            SymbolEntry* entry = (SymbolEntry*)arena_alloc(arena,sizeof(SymbolEntry));
            entry->is_global = 0;
            entry->name = result->val.sval;
            entry->type = TYPE_IDENTIFIER;
            current_table->entries[current_table->symbol_count++] = entry;

            AST_Identifier* name = (AST_Identifier*)call->name->data;
            DataContext* name_ctx = (DataContext*)arena_alloc(arena, sizeof(DataContext));
            name_ctx->val.sval = name->name;
            name_ctx->type = TYPE_IDENTIFIER;
            name_ctx->scope = current_table;
            name_ctx->scope_id = current_table->scope_id;
            name_ctx->acquired_type = TYPE_IDENTIFIER;

            DataContext* temp_ctx = (DataContext*)arena_alloc(arena,sizeof(DataContext));
            if(!is_float){
                temp_ctx->type = TYPE_INT;
                temp_ctx->acquired_type = TYPE_INT;
            }else{
                temp_ctx->type = TYPE_FLOAT;
                temp_ctx->acquired_type = TYPE_FLOAT;
            }
            temp_ctx->scope = current_table;
            temp_ctx->scope_id = current_table->scope_id;
            temp_ctx->val.ival = 0;
            tac_append(prog,tac_create_instr(arena,TAC_ASSIGNDECL,result,temp_ctx,NULL,NULL,NULL));
            TACInstr* call_instr = tac_create_instr(arena, TAC_CALL, result, name_ctx, NULL, NULL, NULL);
            call_instr->arg_count = call->args_count;

            tac_append(prog, call_instr);
            return result;
        }

        default: {
            return NULL;
        }
    }
}

void tac_debug_print(TACList* list,bl_arena* arena){
    printf("\n==== TAC DEBUG DUMP ====\n");
    int index = 0;
    for (TACInstr* instr = list->head; instr; instr = instr->next, ++index) {
        printf("[%03d] op=%d, result=%s, arg1=%s, arg2=%s, relop=%s, label=%s, argc=%d\n",
            index,
            instr->op,
            instr->result ? print_type_val(instr->result,arena) : "NULL",
            instr->arg1 ? print_type_val(instr->arg1,arena) : "NULL",
            instr->arg2 ? print_type_val(instr->arg2,arena) : "NULL",
            instr->relop ? instr->relop->operator_str : "NULL",
            instr->label ? instr->label : "NULL",
            instr->arg_count
        );
    }
    printf("========================\n");
}

void tac_colored_print(TACList* list,bl_arena* arena) {
    printf("\n\x1b[1m==== TAC ====\x1b[0m\n\n");

    for (TACInstr* instr = list->head; instr; instr = instr->next) {
        switch (instr->op) {

            case TAC_EXTERN:
                printf("  %sextern%s      %s%-3s%s\n",
                        COLOR_RESULT, COLOR_RESET,
                        COLOR_ARG, print_type_val(instr->result,arena), COLOR_RESET);
                break;

            case TAC_ASSIGNDECL:
                if(instr->arg1){
                    printf("  %s%-3s%s = %s%-3s%s\n",
                            COLOR_RESULT, print_type_val(instr->result,arena), COLOR_RESET,
                            COLOR_ARG, print_type_val(instr->arg1,arena), COLOR_RESET);
                    break;
                }else{
                    printf("  %s%-3s%s\n",
                            COLOR_RESULT, print_type_val(instr->result,arena), COLOR_RESET);
                    break;
                }
            case TAC_ASSIGN:
                printf("  %s%-3s%s %s %s%-3s%s\n",
                        COLOR_RESULT, print_type_val(instr->result,arena), COLOR_RESET,
                        instr->relop->operator_str,
                        COLOR_ARG, print_type_val(instr->arg1,arena), COLOR_RESET);
                break;
            case TAC_BINOP:
                printf("  %s%-3s%s = %s%-3s%s %s%-3s%s %s%-3s%s\n",
                        COLOR_RESULT, print_type_val(instr->result,arena), COLOR_RESET,
                        COLOR_ARG, print_type_val(instr->arg1,arena), COLOR_RESET,
                        COLOR_OP, instr->relop->operator_str, COLOR_RESET,
                        COLOR_ARG, print_type_val(instr->arg2,arena), COLOR_RESET);
                break;
            
            case TAC_ADDR_OF:
            case TAC_LOAD_PTR:
            case TAC_UNOP:
                printf("  %s%-3s%s = %s%-3s%s %s%-3s%s\n",
                        COLOR_RESULT, print_type_val(instr->result,arena), COLOR_RESET,
                        COLOR_OP, instr->relop->operator_str, COLOR_RESET,
                        COLOR_ARG, print_type_val(instr->arg1,arena), COLOR_RESET);
                break;
            case TAC_LABEL:
                printf("%s%s:%s\n", COLOR_LABEL, instr->label, COLOR_RESET);
                break;
            case TAC_GOTO:
                printf("  %sgoto%s %s%s%s\n", COLOR_OP, COLOR_RESET, COLOR_LABEL, instr->label, COLOR_RESET);
                break;
            case TAC_IFGOTO:
                printf("  %sif%s %s%-3s%s %s%-3s%s %s%-3s%s %sgoto%s %s%s%s\n",
                        COLOR_OP, COLOR_RESET,
                        COLOR_ARG, print_type_val(instr->arg1,arena), COLOR_RESET,
                        COLOR_OP, instr->relop->operator_str, COLOR_RESET,
                        COLOR_ARG, print_type_val(instr->arg2,arena), COLOR_RESET,
                        COLOR_OP, COLOR_RESET, COLOR_LABEL, instr->label, COLOR_RESET);
                break;
            case TAC_PARAM:
                printf("  %sparam%s %s%s%s\n", COLOR_OP, COLOR_RESET, COLOR_ARG, print_type_val(instr->arg1,arena), COLOR_RESET);
                break;
            case TAC_ARG:
                printf("  %sarg%s %s%s%s\n", COLOR_OP, COLOR_RESET, COLOR_ARG, print_type_val(instr->arg1,arena), COLOR_RESET);
                break;
            case TAC_CALL:
                printf("  %s%-3s%s = %scall%s %s%s%s, %s%d%s\n",
                        COLOR_RESULT, print_type_val(instr->result,arena), COLOR_RESET,
                        COLOR_OP, COLOR_RESET,
                        COLOR_ARG, print_type_val(instr->arg1,arena), COLOR_RESET,
                        COLOR_COMMENT, instr->arg_count, COLOR_RESET);
                break;
            case TAC_RETURN:
                printf("  %sreturn%s %s%s%s\n", COLOR_OP, COLOR_RESET, COLOR_ARG, print_type_val(instr->arg1,arena), COLOR_RESET);
                break;
            case TAC_FUNC_BEGIN:
                printf("\n%sfunction %s begin:%s\n", COLOR_LABEL, instr->label, COLOR_RESET);
                break;
            case TAC_FUNC_END:
                printf("%send function%s\n", COLOR_LABEL, COLOR_RESET);
                break;
            case TAC_MAIN_BEGIN:
                printf("\n%smain begin:%s\n", COLOR_LABEL, COLOR_RESET);
                break;
            case TAC_MAIN_END:
                printf("%smain end%s\n", COLOR_LABEL, COLOR_RESET);
                break;
            case TAC_NOP:
            default:
                printf("  %snop%s\n", COLOR_COMMENT, COLOR_RESET);
        }
    }

    printf("\n");
}

void tac_export_dot(TACList* list, const char* filename,bl_arena* arena) {
    FILE* f = fopen(filename, "w");
    if (!f) {
        perror("fopen");
        return;
    }

    fprintf(f, "digraph TAC {\n");
    fprintf(f, "    node [shape=box fontname=\"Courier\"];\n");

    int instr_id = 0;
    for (TACInstr* instr = list->head; instr; instr = instr->next, instr_id++) {
        char node_name[32];
        snprintf(node_name, sizeof(node_name), "n%d", instr_id);


        char label[256] = "";
        switch (instr->op) {
            case TAC_EXTERN:
                snprintf(label,sizeof(label),"extern  %s", print_type_val(instr->result,arena));
                break;
            
            case TAC_FUNC_BEGIN:
                snprintf(label, sizeof(label),"function %s begin",instr->label);
                break;

            case TAC_FUNC_END:
                snprintf(label,sizeof(label),"function end");
                break;
            
            case TAC_MAIN_BEGIN:
                snprintf(label,sizeof(label),"function main begin");
                break;
            case TAC_MAIN_END:
                snprintf(label, sizeof(label), "function main end");
                break;
            case TAC_ASSIGN:
                snprintf(label,sizeof(label), "%s %s %s",print_type_val(instr->result,arena),instr->relop->operator_str, print_type_val(instr->arg1,arena));
                break;
            case TAC_ASSIGNDECL:
                if(instr->arg1){
                    snprintf(label, sizeof(label), "%s = %s", print_type_val(instr->result,arena), print_type_val(instr->arg1,arena));
                }else{
                    snprintf(label, sizeof(label), "%s", print_type_val(instr->result,arena));
                }
                break;
            case TAC_BINOP:
                snprintf(label, sizeof(label), "%s = %s %s %s", print_type_val(instr->result,arena), print_type_val(instr->arg1,arena), instr->relop->operator_str, print_type_val(instr->arg2,arena));
                break;
            case TAC_ADDR_OF:
            case TAC_LOAD_PTR:
            case TAC_UNOP:
                snprintf(label, sizeof(label), "%s = %s %s", print_type_val(instr->result,arena), instr->relop->operator_str, print_type_val(instr->arg1,arena));
                break;
            case TAC_IFGOTO:
                snprintf(label, sizeof(label), "if %s %s %s goto %s", print_type_val(instr->arg1,arena), instr->relop->operator_str, print_type_val(instr->arg2,arena), instr->label);
                break;
            case TAC_GOTO:
                snprintf(label, sizeof(label), "goto %s", instr->label);
                break;
            case TAC_LABEL:
                snprintf(label, sizeof(label), "%s:", instr->label);
                break;
            case TAC_CALL:
                snprintf(label, sizeof(label), "%s = call %s (%d)", print_type_val(instr->result,arena), print_type_val(instr->arg1,arena), instr->arg_count);
                break;
            case TAC_PARAM:
                snprintf(label, sizeof(label), "param %s", print_type_val(instr->arg1,arena));
                break;
            case TAC_ARG:
                snprintf(label,sizeof(label),"arg %s",print_type_val(instr->arg1,arena));
                break;
            case TAC_RETURN:
                snprintf(label, sizeof(label), "return %s", print_type_val(instr->arg1,arena));
                break;
            default:
                snprintf(label, sizeof(label), "TAC Op %d", instr->op);
        }

        fprintf(f, "    %s [label=\"%s\"];\n", node_name, label);

        if (instr->next) {
            fprintf(f, "    %s -> n%d;\n", node_name, instr_id + 1);
        }


        if (instr->op == TAC_GOTO || instr->op == TAC_IFGOTO) {
            TACInstr* target = list->head;
            int target_id = 0;
            while (target) {
                if (target->op == TAC_LABEL && strcmp(target->label, instr->label) == 0) {
                    fprintf(f, "    %s -> n%d [style=dashed color=blue];\n", node_name, target_id);
                    break;
                }
                target = target->next;
                target_id++;
            }
        }
    }

    fprintf(f, "}\n");
    fclose(f);
}

char* print_type_val(DataContext* context,bl_arena* arena){
    switch(context->type){
        case TYPE_BOOL:{
            char buf[32];
            snprintf(buf, sizeof(buf),"%d",context->val.bval == true? 1 : 0);
            char* str = (char*)arena_alloc(arena, strlen(buf) + 1);
            strcpy(str,buf);
            return str;
        }
        case TYPE_INT: {
            char buf[32];
            snprintf(buf,sizeof(buf),"%d",context->val.ival);
            char* str = (char*)arena_alloc(arena,strlen(buf) + 1);
            strcpy(str,buf);
            return str;
        }

        case TYPE_FLOAT: {
            char buf[32];
            snprintf(buf,sizeof(buf), "%.16f",context->val.fval);
            char* str = (char*)arena_alloc(arena, strlen(buf) + 1);
            strcpy(str,buf);
            return str;
        }

        case TYPE_CHAR: {
            char buf[32];
            snprintf(buf,sizeof(buf),"%c",context->val.cval);
            char* str = (char*)arena_alloc(arena,strlen(buf) + 1);
            strcpy(str,buf);
            return str;
        }

        case TYPE_STRING: {
            char buf[1024];
            snprintf(buf,sizeof(buf),"%s",context->val.sval);
            char* str = (char*)arena_alloc(arena,sizeof(buf) + 1);
            strcpy(str,buf);
            return str;
        }

        case TYPE_PTR: {
            char buf[32];
            snprintf(buf,sizeof(buf), "%s",context->val.sval);
            char* str = (char*)arena_alloc(arena,strlen(buf) + 1);
            strcpy(str,buf);
            return str;
        }

        case TYPE_REF: {
            char buf[32];
            snprintf(buf,sizeof(buf), "%s",context->val.sval);
            char* str = (char*)arena_alloc(arena,strlen(buf) + 1);
            strcpy(str,buf);
            return str;
        }
        
        case TYPE_IDENTIFIER: {
            char buf[1024];
            snprintf(buf,sizeof(buf),"%s",context->val.sval);
            char* str = (char*)arena_alloc(arena,strlen(buf) + 1);
            strcpy(str,buf);
            return str;
        }

        case TYPE_VOID : {
            char* str = (char*)arena_alloc(arena,10);
            str = "void";
            return str;
        }

        case TYPE_UNKNOWN: {
            char* str = (char*)arena_alloc(arena,10);
            str = "unknown";
            return str;
        }

        case TYPE_UNDECLARED: {
            char* str = (char*)arena_alloc(arena,10);
            str = "undeclared";
            return str;
        }

        case TYPE_FUNCTION: {
            char buf[1024];
            snprintf(buf,sizeof(buf),"%s",context->val.sval);
            char* str = (char*)arena_alloc(arena,strlen(buf) + 1);
            strcpy(str,buf);
            return str;
        }
        
        case TYPE_EXTERN: {
            char buf[1024];
            snprintf(buf,sizeof(buf),"%s",context->val.sval);
            char* str = (char*)arena_alloc(arena,strlen(buf) + 1);
            strcpy(str,buf);
            return str;
        }

        default: {
            return NULL;
        }
    }
    return NULL;
}

bool is_compare_type(TACInstr* instr){
    if(instr->relop->operator_type == BL_LESSTHAN    || 
       instr->relop->operator_type == BL_GRTTHAN     || 
       instr->relop->operator_type == BL_LESSEQ      || 
       instr->relop->operator_type == BL_GRTEQ       || 
       instr->relop->operator_type == BL_LOGAND      || 
       instr->relop->operator_type == BL_LOGOR       || 
       instr->relop->operator_type == BL_ISEQUALCOND || 
       instr->relop->operator_type == BL_NOTEQ){
        return 1;
    }else{
        return 0;
    }
}

bool is_binop_float(TACInstr* instr){
    if(instr->arg1->acquired_type == TYPE_FLOAT || instr->arg2->acquired_type == TYPE_FLOAT){
        return 1;
    }else{
        return 0;
    }
}

bool is_binop_int(TACInstr* instr){
    if(instr->arg1->acquired_type == TYPE_INT || instr->arg2->acquired_type == TYPE_INT){
        return 1;
    }else{
        return 0;
    }
}

bool is_binop_char(TACInstr* instr){
    if(instr->arg1->acquired_type == TYPE_CHAR || instr->arg2->acquired_type == TYPE_CHAR){
        return 1;
    }else{
        return 0;
    }
}

bool is_binop_bool(TACInstr* instr){
    if(instr->arg1->acquired_type == TYPE_BOOL || instr->arg2->acquired_type == TYPE_BOOL){
        return 1;
    }else{
        return 0;
    }
}

bool is_binop_string(TACInstr* instr){
    if(instr->arg1->acquired_type == TYPE_STRING || instr->arg2->acquired_type == TYPE_STRING){
        return 1;
    }else{
        return 0;
    }
}

void update_tac_values(TACInstr* instr,DataContext* ctx,SymbolTable* table,ValueType temp_type,bl_arena* arena){
    if(!ctx){
        return;
    }
    TACInstr* temp_ptr = instr;
    while(instr){
        if(instr->result){
            if(strcmp(print_type_val(ctx,arena),print_type_val(instr->result,arena)) == 0 && (table->scope_id == 0 || (instr->result->scope_id == table->scope_id))){
                instr->result->acquired_type = temp_type;
            }

        }
        if(instr->arg1){
            if(strcmp(print_type_val(ctx,arena),print_type_val(instr->arg1,arena)) == 0 && (table->scope_id == 0 || (instr->arg1->scope_id == table->scope_id))){
                instr->arg1->acquired_type = temp_type;
            }
        }
        if(instr->arg2){
            if(strcmp(print_type_val(ctx,arena),print_type_val(instr->arg2,arena)) == 0 && (table->scope_id == 0 || (instr->arg2->scope_id == table->scope_id))){
                instr->arg2->acquired_type = temp_type;
            }
        }
        instr = instr->next;
    }
    instr = temp_ptr;

    for(int i = 0;i<table->children_count;i++){
        update_tac_values(instr,ctx,table->children[i],temp_type,arena);
    }
}

void update_types_in_list(TACList* list,bl_arena* arena){
    TACInstr* instr = list->head;
    while(instr){
        switch(instr->op){
            case TAC_EXTERN:{
                instr->result->acquired_type = TYPE_EXTERN;
                DataContext* ctx = instr->result;
                ValueType temp_type = instr->result->acquired_type;
                update_tac_values(instr,ctx,ctx->scope,temp_type,arena);
                break;
            }
            case TAC_BINOP:{
                if(is_compare_type(instr)){
                    instr->result->acquired_type = TYPE_BOOL;
                    DataContext* ctx = instr->result;
                    ValueType temp_type = instr->result->acquired_type;
                    update_tac_values(instr,ctx,ctx->scope,temp_type,arena);
                    break;
                }else{
                    if(is_binop_float(instr)){
                        instr->result->acquired_type = TYPE_FLOAT;
                        DataContext* ctx = instr->result;
                        ValueType temp_type = instr->result->acquired_type;
                        update_tac_values(instr,ctx,ctx->scope,temp_type,arena);
                        break;
                    }
                    if(is_binop_int(instr)){
                        instr->result->acquired_type = TYPE_INT;
                        DataContext* ctx = instr->result;
                        ValueType temp_type = instr->result->acquired_type;
                        update_tac_values(instr,ctx,ctx->scope,temp_type,arena);
                        break;
                    }
                    if(is_binop_char(instr)){
                        instr->result->acquired_type = TYPE_CHAR;
                        DataContext* ctx = instr->result;
                        ValueType temp_type = instr->result->acquired_type;
                        update_tac_values(instr,ctx,ctx->scope,temp_type,arena);
                        break;
                    }
                    if(is_binop_bool(instr)){
                        instr->result->acquired_type = TYPE_BOOL;
                        DataContext* ctx = instr->result;
                        ValueType temp_type = instr->result->acquired_type;
                        update_tac_values(instr,ctx,ctx->scope,temp_type,arena);
                        break;
                    }
                    if(is_binop_string(instr)){
                        instr->result->acquired_type = TYPE_STRING;
                        DataContext* ctx = instr->result;
                        ValueType temp_type = instr->result->acquired_type;
                        update_tac_values(instr,ctx,ctx->scope,temp_type,arena);
                        break;
                    }
                    instr->result->acquired_type = TYPE_IDENTIFIER;
                    DataContext* ctx = instr->result;
                    ValueType temp_type = instr->result->acquired_type;
                    update_tac_values(instr,ctx,ctx->scope,temp_type,arena);
                    break;
                }
            }
            case TAC_ASSIGNDECL:
            case TAC_ASSIGN:
            case TAC_UNOP:{
                if(instr->arg1){
                    instr->result->acquired_type = instr->arg1->acquired_type;
                    DataContext* ctx = instr->result;
                    ValueType temp_type = instr->result->acquired_type;
                    update_tac_values(instr,ctx,ctx->scope,temp_type,arena);
                }else{
                    instr->result->acquired_type = TYPE_IDENTIFIER;
                    DataContext* ctx = instr->result;
                    ValueType temp_type = TYPE_IDENTIFIER;
                    update_tac_values(instr,ctx,ctx->scope,temp_type,arena);
                }
                break;
            }
            case TAC_LOAD_PTR:{
                    instr->result->acquired_type = instr->arg1->acquired_type;
                    DataContext* ctx = instr->result;
                    ValueType temp_type = TYPE_PTR;
                    update_tac_values(instr,ctx,ctx->scope,temp_type,arena);
                    break;
                }
            case TAC_ADDR_OF:{
                instr->result->acquired_type = instr->arg1->acquired_type;
                DataContext* ctx = instr->result;
                ValueType temp_type = TYPE_REF;
                update_tac_values(instr,ctx,ctx->scope,temp_type,arena);
                break;
            }
            case TAC_PARAM:{
                DataContext* ctx = instr->arg1;
                ValueType temp_type = instr->arg1->acquired_type;
                update_tac_values(instr,ctx,ctx->scope,temp_type,arena);
                break;
            }
            case TAC_FUNC_BEGIN:
            case TAC_FUNC_END:
            case TAC_MAIN_BEGIN:
            case TAC_MAIN_END:
            case TAC_IFGOTO:
            case TAC_GOTO:
            case TAC_ARG:
            case TAC_RETURN:
            case TAC_NOP:
            case TAC_LABEL:
            default:
                break;
            
        }
        instr = instr->next;
    }
}


void tac_print(TACList* list,bl_arena* arena) { 
    for (TACInstr* instr = list->head; instr; instr = instr->next) {
        switch (instr->op) {
            case TAC_LOAD_PTR:
                printf("[LOAD PTR] %s (%s) (%d) = *%s (%s) (%d)\n", 
                    print_type_val(instr->result, arena), 
                    get_str_type(instr->result->acquired_type),
                    instr->result->scope_id,
                    print_type_val(instr->arg1, arena),
                    get_str_type(instr->arg1->acquired_type),
                    instr->arg1->scope_id);
                
                break;

            case TAC_ADDR_OF:
                printf("[ADDR OF] %s (%s) (%d) = &%s (%s) (%d)\n", 
                    print_type_val(instr->result, arena), 
                    get_str_type(instr->result->acquired_type),
                    instr->result->scope_id,
                    instr->arg1 ?
                    print_type_val(instr->arg1, arena):
                    "null",
                    
                    instr->arg1 ?
                    get_str_type(instr->arg1->acquired_type):
                    "null",
                    
                    instr->arg1?
                    instr->arg1->scope_id : 0);
                break;
            case TAC_ASSIGNDECL:
                if(instr->arg1){
                    printf("[Declaration] %s (%s) (%d) = %s (%s) (%d)\n", print_type_val(instr->result,arena),get_str_type(instr->result->acquired_type),instr->result->scope_id, print_type_val(instr->arg1,arena),get_str_type(instr->arg1->acquired_type),instr->result->scope_id);
                }else{
                    printf("[Declaration] %s (%s) (%d) unassigned\n", print_type_val(instr->result,arena),get_str_type(instr->result->acquired_type),instr->result->scope_id);
                }
                break;
            case TAC_ASSIGN:
                printf("[Assignment] %s (%s) (%d) %s %s (%s) (%d)\n", print_type_val(instr->result,arena),get_str_type(instr->result->acquired_type),instr->result->scope_id,instr->relop->operator_str, print_type_val(instr->arg1,arena),get_str_type(instr->arg1->acquired_type),instr->arg1->scope_id);
                break;
            case TAC_BINOP:
                
                printf("[Binary Op] %s (%s) (%d) = %s (%s) (%d) %s %s (%s) (%d) \n", print_type_val(instr->result,arena),get_str_type(instr->result->acquired_type), instr->result->scope_id,print_type_val(instr->arg1,arena),get_str_type(instr->arg1->acquired_type),instr->arg1->scope_id, instr->relop->operator_str, print_type_val(instr->arg2,arena),get_str_type(instr->arg2->acquired_type),instr->arg2->scope_id);
                break;
            case TAC_UNOP:
                printf("[Unary op] %s (%s) (%d) = %s%s (%s) (%d) \n", print_type_val(instr->result,arena),get_str_type(instr->result->acquired_type), instr->result->scope_id,instr->relop->operator_str, print_type_val(instr->arg1,arena),get_str_type(instr->arg1->acquired_type),instr->arg1->scope_id);
                break;
            case TAC_LABEL:
                printf("\n");
                printf("[Label] %s:\n", instr->label);
                break;
            case TAC_GOTO:
                printf("[Jump] goto %s\n", instr->label);
                break;
            case TAC_IFGOTO:
                printf("[Conditional Jump] if %s (%s) (%d) %s %s (%s) (%d) goto %s\n", print_type_val(instr->arg1,arena),get_str_type(instr->arg1->acquired_type),instr->arg1->scope_id, instr->relop->operator_str, print_type_val(instr->arg2,arena),get_str_type(instr->arg2->acquired_type), instr->arg2->scope_id,instr->label);
                break;
            case TAC_PARAM:
                printf("[Parameter] param %s (%s) (%d)\n", print_type_val(instr->arg1,arena),get_str_type(instr->arg1->acquired_type),instr->arg1->scope_id);
                break;
            case TAC_ARG:
                printf("[Argument] arg %s (%s) (%d)\n",print_type_val(instr->arg1,arena),get_str_type(instr->arg1->acquired_type),instr->arg1->scope_id);
                break;
            case TAC_CALL:
                printf("[Function call] %s (%s) (%d) = call %s (%s) (%d), %d\n", print_type_val(instr->result,arena),get_str_type(instr->result->acquired_type), instr->result->scope_id,print_type_val(instr->arg1,arena),get_str_type(instr->arg1->acquired_type),instr->arg1->scope_id, instr->arg_count);
                break;
            case TAC_RETURN:
                printf("[Return] return %s (%s) (%d)\n", print_type_val(instr->arg1,arena),get_str_type(instr->arg1->acquired_type),instr->arg1->scope_id);
                break;
            case TAC_FUNC_BEGIN:
                printf("[Function start] function %s begin:\n", instr->label);
                break;
            case TAC_FUNC_END:
                printf("[Function end] function end\n");
                break;
            case TAC_MAIN_BEGIN:
                printf("[Main start] %s begin:\n",instr->label);
                break;
            case TAC_MAIN_END:
                printf("[Main end] main end\n");
                break;
            case TAC_EXTERN:
                printf("[Extern] extern %s (%s) (%d)\n",print_type_val(instr->result,arena),get_str_type(instr->result->acquired_type),instr->result->scope_id);
                break;
            default:
                printf("nop\n");
                
        }
    }
}

void symbol_table_list_init(SymbolTableList* list, bl_arena* arena) {
    list->arena = arena;
    list->table_count = 0;
    list->table_capacity = 256;
    list->tables = (SymbolTable**)arena_alloc(arena, sizeof(SymbolTable*) * list->table_capacity);
}



void print_all_symbol_tables(SymbolTableList* list) {
    for (int i = 0; i < list->table_count; ++i) {
        print_symbol_table(list->tables[i]);
    }
}

void allocate_offsets_for_func(SymbolTable* table,int *offset){
    if (table == NULL) return;
    for(int j = 0;j<table->symbol_count;j++){
        if(table->entries[j]->type == TYPE_STRING){
            int t_offset = strlen(table->entries[j]->string_val) + 1;
            t_offset = (t_offset + 7) & ~7;
            (*offset)+=t_offset;
            table->entries[j]->offset = *offset;
            (*offset)+=8;
        }else if(table->entries[j]->type == TYPE_ARG){
            if(table->entries[j]->string_val){
                int t_offset = strlen(table->entries[j]->string_val) + 1;
                t_offset = (t_offset + 7) & ~7;
                (*offset)+=t_offset;
                table->entries[j]->offset = *offset;
                (*offset)+=8;
            }else{
                table->entries[j]->offset = *offset;
                (*offset)+=8;
            }
        }else{
            table->entries[j]->offset = *offset;
            (*offset)+=8;
        }
    }
    for (int i = 0; i < table->children_count; i++) {
        allocate_offsets_for_func(table->children[i],offset);
    }
}

void allocate_offsets_for_all_funcs(SymbolTableList* list){
    SymbolTable* global_table = list->tables[0];
    for(int i = 0;i<global_table->symbol_count;i++){
        global_table->entries[i]->offset = 0;
    }
    global_table->total_offset = 0;
    for(int i = 0; i< global_table->children_count; i++){
        int offset = 8;
        allocate_offsets_for_func(global_table->children[i],&offset);
        int frame = (offset + 15) & ~15;
        global_table->children[i]->total_offset = frame;
    }
}

void print_symbol_table(SymbolTable* table) {
    printf(">> Symbol Table for Scope: %s %p, Scope ID : %d, Parent Scope : %s %p\n",table->scope_name,table,table->scope_id, table->parent ? table->parent->scope_name ? table->parent->scope_name : "null" : "TOP",table->parent ? table->parent : 0x00000000);
    for (int i = 0; i < table->symbol_count; ++i) {
        SymbolEntry* s = table->entries[i];
        printf("  [%d] %s (%s) | is Global : %d | Offset: %d\n", i, s->name, get_str_type(s->type),s->is_global,s->offset ? s->offset : 0);
    }
}

static void print_table_ascii(const SymbolTable *tbl, int depth)
{
    if (!tbl) return;


    for (int i = 0; i < depth; ++i) fputs("    ", stdout);

    
    printf("• %s (id=%d, symbols=%d, offset=%d)\n",
           tbl->scope_name ? tbl->scope_name : "<unnamed>",
           tbl->scope_id,
           tbl->symbol_count,
           tbl->total_offset);

    /* recurse into children */
    for (int i = 0; i < tbl->children_count; ++i)
        print_table_ascii(tbl->children[i], depth + 1);
}


static void emit_dot_nodes(const SymbolTable *tbl)
{
    if (!tbl) return;

    printf("  n%d [label=\"%s\\n(id=%d)\\nsyms=%d\\noff=%d\"];\n",
           tbl->scope_id,
           tbl->scope_name ? tbl->scope_name : "<unnamed>",
           tbl->scope_id,
           tbl->symbol_count,
           tbl->total_offset);

    for (int i = 0; i < tbl->children_count; ++i) {
        const SymbolTable *child = tbl->children[i];
        if (!child) continue;
        printf("  n%d -> n%d;\n", tbl->scope_id, child->scope_id);
        emit_dot_nodes(child);
    }
}

void print_table_dot(const SymbolTable *root)
{
    puts("digraph SymbolTables {");
    puts("  node [shape=box, fontname=\"Sans\", fontsize=10];");
    emit_dot_nodes(root);
    puts("}");
}


void visualize_symbol_tables_ascii(const SymbolTable *root)
{
    puts("=== Symbol Table Tree (SCOPES) ===");
    print_table_ascii(root, 0);
    puts("=================================");
}

void visualize_symbol_tables_dot(const SymbolTable *root)
{
    print_table_dot(root);
}


