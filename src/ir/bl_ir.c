#include "bl_astOptimizer.h"


#define COLOR_RESET     "\x1b[0m"
#define COLOR_LABEL     "\x1b[1;36m"
#define COLOR_OP        "\x1b[1;33m"
#define COLOR_RESULT    "\x1b[1;32m"
#define COLOR_ARG       "\x1b[1;34m"
#define COLOR_COMMENT   "\x1b[2;37m"


typedef enum {
    TAC_NOP,
    TAC_ASSIGNDECL,
    TAC_ASSIGN,     
    TAC_BINOP,   
    TAC_UNOP,       
    TAC_LABEL,
    TAC_GOTO,
    TAC_IFGOTO,     
    TAC_PARAM,
    TAC_ARG,
    TAC_CALL,
    TAC_FUNC_BEGIN,  
    TAC_FUNC_END,    
    TAC_MAIN_BEGIN,
    TAC_MAIN_END,
    TAC_RETURN,
    TAC_EXTERN,
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
} ValueType;


typedef union{
    int ival;
    float fval;
    char cval;
    bool bval;
    char* sval;
} ValuePrimitive;
typedef struct {
    ValuePrimitive val;
    ValueType type;
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



typedef struct LoopContext {
    char* break_label;
    char* continue_label;
    struct LoopContext* prev;
} LoopContext;



static char temp_counter = 0;
static char label_counter = 0;

TACInstr* tac_create_instr(bl_arena* arena, TAC_Op op, DataContext* result, DataContext* arg1, DataContext* arg2, OperatorContext* relop, char* label);
void tac_append(TACList* list, TACInstr* instr);
void tac_print(TACList* list,bl_arena* arena);
void tac_debug_print(TACList* list,bl_arena* arena);
void tac_colored_print(TACList* list,bl_arena* arena);
void tac_export_dot(TACList* list, const char* filename,bl_arena* arena);

TACList* generate_tac(AST_Node* ast, bl_arena* arena);
DataContext* gen_tac(AST_Node* node, TACList* prog, bl_arena* arena, LoopContext* loop_ctx);

DataContext* new_temp(bl_arena* arena);
char* get_binop_from_keyword(enum KEYWORD_TYPES type);
char* new_label(bl_arena* arena);
char* print_type_val(DataContext* context,bl_arena* arena);


int main(){
    bl_arena* arena = (bl_arena*)malloc(sizeof(bl_arena));
    arena_init(arena);
    AST_Node* node = bhaulang_optimizer("src/ir/one.bl",arena);

    TACList* list = generate_tac(node,arena);
    tac_print(list,arena);
    arena_stats(arena);
    return 0;
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
    }
    return NULL;
}

TACInstr* tac_create_instr(bl_arena* arena, TAC_Op op, DataContext* result, DataContext* arg1, DataContext* arg2, OperatorContext* relop, char* label) {
    TACInstr* instr = arena_alloc(arena, sizeof(TACInstr));
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
    char buf[32];
    snprintf(buf, sizeof(buf), "t%d", temp_counter++);
    char* tmp = arena_alloc(arena, strlen(buf) + 1);
    strcpy(tmp, buf);
    DataContext* ctx = (DataContext*)arena_alloc(arena,sizeof(DataContext));
    ctx->val.sval = tmp;
    ctx->type = TYPE_IDENTIFIER;
    return ctx;
}

char* new_label(bl_arena* arena) {
    char buf[32];
    snprintf(buf, sizeof(buf), "L%d", label_counter++);
    char* lbl = arena_alloc(arena, strlen(buf) + 1);
    strcpy(lbl, buf);
    return lbl;
}

TACList* generate_tac(AST_Node* ast, bl_arena* arena) {
    TACList* list = arena_alloc(arena, sizeof(TACList));
    list->head = list->tail = NULL;
    list->temp_id = 0;
    list->label_id = 0;
    gen_tac(ast, list, arena,NULL);
    return list;
}

DataContext* gen_tac(AST_Node* node, TACList* prog, bl_arena* arena,LoopContext* loop_ctx) {
    if (!node) return NULL;
    switch (node->type) {
        case AST_PROGRAM: {
            ASTProgram* prog_node = node->data;
            for (size_t i = 0; i < prog_node->count; ++i) {
                gen_tac(prog_node->statements[i], prog, arena,loop_ctx);
            }
            return NULL;
        }

        case AST_SWITCH: {
            AST_Switch* sw = node->data;


            char* end_label = new_label(arena);

            LoopContext* new_ctx = (LoopContext*)arena_alloc(arena,sizeof(LoopContext));
            new_ctx->break_label = end_label,
            new_ctx->continue_label = NULL;
            new_ctx->prev = loop_ctx;

            DataContext* switch_val_data = gen_tac(sw->expr, prog, arena,new_ctx);


            char** case_labels = arena_alloc(arena, sizeof(char*) * sw->case_count);
            for (int i = 0; i < (int)sw->case_count; ++i) {
                case_labels[i] = new_label(arena);
            }

            for (int i = 0; i < (int)sw->case_count; ++i) {
                AST_SwitchCase* case_node = sw->cases[i]->data;
                ASTNodeType type = case_node->value->type;
                if(type == AST_INTLITERAL){
                    AST_IntLiteral* ilit = ((AST_Node*)case_node->value)->data;
                    DataContext* sw_ctx = (DataContext*)arena_alloc(arena,sizeof(DataContext));
                    sw_ctx->val.ival = ilit->value;
                    sw_ctx->type = TYPE_INT;

                    OperatorContext* op_ctx = (OperatorContext*)arena_alloc(arena,sizeof(OperatorContext));
                    op_ctx->operator_str = "==";
                    op_ctx->operator_type = BL_ISEQUALCOND;
                    
                    tac_append(prog, tac_create_instr(arena, TAC_IFGOTO, NULL, switch_val_data,sw_ctx, op_ctx, case_labels[i]));
                }else if(type == AST_CHARLITERAL){
                    AST_CharLiteral* clit = ((AST_Node*)case_node->value)->data;
                    DataContext* sw_ctx = (DataContext*)arena_alloc(arena,sizeof(DataContext));
                    sw_ctx->val.cval = clit->value;
                    sw_ctx->type = TYPE_CHAR;

                    OperatorContext* op_ctx = (OperatorContext*)arena_alloc(arena,sizeof(OperatorContext));
                    op_ctx->operator_str = "==";
                    op_ctx->operator_type = BL_ISEQUALCOND;

                    tac_append(prog, tac_create_instr(arena, TAC_IFGOTO, NULL, switch_val_data,sw_ctx, op_ctx, case_labels[i]));
                }else{
                    fprintf(stderr,"Switch cannot be used with floats or strings");
                    exit(1);
                }
            }

            char* def_label = new_label(arena);
            tac_append(prog, tac_create_instr(arena, TAC_GOTO, NULL, NULL,NULL,NULL,def_label));

            for (int i = 0; i < (int)sw->case_count; ++i) {
                tac_append(prog, tac_create_instr(arena, TAC_LABEL, NULL, NULL,NULL,NULL, case_labels[i]));
                gen_tac(sw->cases[i], prog, arena,new_ctx);
            }
            tac_append(prog, tac_create_instr(arena, TAC_LABEL, NULL, NULL,NULL,NULL, def_label));

            if (sw->default_case) {
                gen_tac(sw->default_case, prog, arena,new_ctx);
            }

            tac_append(prog, tac_create_instr(arena, TAC_LABEL, NULL, NULL,NULL,NULL, end_label));
            return NULL;
        }

        case AST_CASE: {
            AST_SwitchCase* cs = node->data;
            for (int i = 0; i < (int)cs->body_count; ++i) {
                gen_tac(cs->body[i], prog, arena,loop_ctx);
            }
            return NULL;
        }

        case AST_DEFAULT: {
            AST_SwitchCase* def = node->data;
            for (int i = 0; i < (int)def->body_count; ++i) {
                gen_tac(def->body[i], prog, arena,loop_ctx);
            }
            return NULL;
        }

        case AST_EXTERN: {
            AST_Identifier* ext = (AST_Identifier*)((AST_Node*)((AST_Extern*)node->data)->ident)->data;
            DataContext* ext_ctx = (DataContext*)arena_alloc(arena,sizeof(DataContext));
            ext_ctx->val.sval = ext->name;
            ext_ctx->type = TYPE_IDENTIFIER;
            tac_append(prog, tac_create_instr(arena, TAC_EXTERN, ext_ctx,NULL, NULL, NULL, NULL));
            return NULL;
        }

        case AST_INTLITERAL: {
            AST_IntLiteral* lit = node->data;
            DataContext* int_val = (DataContext*)arena_alloc(arena,sizeof(DataContext));
            int_val->val.ival = lit->value;
            int_val->type = TYPE_INT;
            return int_val;
        }
        
        case AST_BOOLLITERAL: {
            AST_BoolLiteral* blit = node->data;
            DataContext* bool_val = (DataContext*)arena_alloc(arena,sizeof(DataContext));
            bool_val->val.bval=blit->value;
            bool_val->type = TYPE_BOOL;
            return bool_val;
        }

        case AST_STRINGLITERAL : {
            AST_StringLiteral* slit = node->data;
            DataContext* str_val = (DataContext*)arena_alloc(arena,sizeof(DataContext));
            str_val->val.sval = slit->value;
            str_val->type = TYPE_STRING;
            return str_val;
        }

        case AST_CHARLITERAL : {
            AST_CharLiteral* clit = node->data;
            DataContext* char_val = (DataContext*)arena_alloc(arena,sizeof(DataContext));
            char_val->val.cval = clit->value;
            char_val->type = TYPE_CHAR;
            return char_val;
        }

        case AST_FLOATLITERAL : {
            AST_FloatLiteral* flit = node->data;
            DataContext* float_val = (DataContext*)arena_alloc(arena,sizeof(DataContext));
            float_val->val.fval = flit->value;
            float_val->type = TYPE_FLOAT;
            return float_val;
        }

        case AST_IDENTIFIER: {
            AST_Identifier* ident = node->data;
            DataContext* ctx = (DataContext*)arena_alloc(arena,sizeof(DataContext));
            ctx->val.sval = ident->name;
            ctx->type = TYPE_IDENTIFIER;
            return ctx;
        }

        case AST_BINOP: {
            AST_Binop* bin = node->data;
            DataContext* left = gen_tac(bin->lhs, prog, arena,loop_ctx);
            DataContext* right = gen_tac(bin->rhs, prog, arena,loop_ctx);
            DataContext* result = new_temp(arena);

            OperatorContext* op_ctx = (OperatorContext*)arena_alloc(arena,sizeof(OperatorContext));
            op_ctx->operator_str = get_binop_from_keyword(bin->op);
            op_ctx->operator_type = bin->op;

            tac_append(prog, tac_create_instr(arena, TAC_BINOP, result, left, right, op_ctx, NULL));
            return result;
        }
        
        case AST_GROUP: {
            AST_Group* grp = node->data;
            return gen_tac(grp->expr, prog, arena, loop_ctx);
        }

        case AST_UNOP: {
            AST_Unop* un = node->data;
            DataContext* arg = gen_tac(un->node, prog, arena,loop_ctx);
            DataContext* result = new_temp(arena);

                OperatorContext* op_ctx = (OperatorContext*)arena_alloc(arena,sizeof(OperatorContext));
                op_ctx->operator_str = get_binop_from_keyword(un->op);
                op_ctx->operator_type = un->op;

            tac_append(prog, tac_create_instr(arena, TAC_UNOP, result, arg, NULL, op_ctx, NULL));
            return result;
        }

        case AST_ASSIGN: {
            AST_Assign* asg = node->data;
            DataContext* rhs = gen_tac(asg->rhs, prog, arena,loop_ctx);
            AST_Identifier* ident = asg->lhs->data;
            DataContext* ctx = (DataContext*)arena_alloc(arena,sizeof(DataContext));
            ctx->val.sval = ident->name;
            ctx->type = TYPE_IDENTIFIER;

            OperatorContext* op_ctx = (OperatorContext*)arena_alloc(arena,sizeof(OperatorContext));
            op_ctx->operator_str = get_binop_from_keyword(asg->op);
            op_ctx->operator_type = asg->op;

            tac_append(prog, tac_create_instr(arena, TAC_ASSIGN, ctx, rhs, NULL,op_ctx, NULL));
            return ctx;
        }

        case AST_ASSIGNDECL: {
            AST_Assign* asg = node->data;
            AST_Identifier* ident = asg->lhs->data;
            DataContext* ctx = (DataContext*)arena_alloc(arena,sizeof(DataContext));
            ctx->val.sval = ident->name;
            ctx->type = TYPE_IDENTIFIER;
            if(asg->rhs){
            DataContext* rhs = gen_tac(asg->rhs, prog, arena,loop_ctx);
            tac_append(prog, tac_create_instr(arena, TAC_ASSIGNDECL, ctx, rhs, NULL, NULL, NULL));
            }else{
                tac_append(prog, tac_create_instr(arena, TAC_ASSIGNDECL, ctx, NULL, NULL, NULL, NULL));
            }
            return ctx;
        }


        case AST_MAIN: {
            AST_Main* fn = node->data;
            tac_append(prog, tac_create_instr(arena, TAC_MAIN_BEGIN, NULL, NULL, NULL, NULL, "main"));
            gen_tac(fn->block, prog, arena,loop_ctx);
            tac_append(prog, tac_create_instr(arena, TAC_MAIN_END, NULL, NULL, NULL, NULL, NULL));
            return NULL;
        }

        case AST_BLOCK: {
            AST_Block* blk = node->data;
            for (size_t i = 0; i < blk->body_count; ++i) {
                gen_tac(blk->body[i], prog, arena,loop_ctx);
            }
            return NULL;
        }

        case AST_RETURN: {
            AST_Return* ret = node->data;
            DataContext* val = gen_tac(ret->expr, prog, arena,loop_ctx);
            tac_append(prog, tac_create_instr(arena, TAC_RETURN, NULL, val, NULL, NULL, NULL));
            return NULL;
        }

        case AST_IFELSE: {
            AST_Ifelse* ifs = node->data;
            DataContext* cond = gen_tac(ifs->condition, prog, arena,loop_ctx);
            char* then_label = new_label(arena);
            char* end_label  = new_label(arena);

            DataContext* zero_ctx = (DataContext*)arena_alloc(arena,sizeof(DataContext));
            zero_ctx->val.ival = 0;
            zero_ctx->type = TYPE_INT;

            OperatorContext* op_ctx = (OperatorContext*)arena_alloc(arena,sizeof(OperatorContext));
            op_ctx->operator_str = "!=";
            op_ctx->operator_type = BL_NOTEQ;

            tac_append(prog, tac_create_instr(arena, TAC_IFGOTO, NULL, cond, zero_ctx, op_ctx, then_label));

            if (ifs->else_block) {
                gen_tac(ifs->else_block, prog, arena,loop_ctx);
                tac_append(prog, tac_create_instr(arena, TAC_GOTO, NULL, NULL, NULL, NULL, end_label));
            }else{
                tac_append(prog,tac_create_instr(arena, TAC_GOTO,NULL,NULL,NULL,NULL,end_label));
            }

            tac_append(prog, tac_create_instr(arena, TAC_LABEL, NULL, NULL, NULL, NULL, then_label));
            gen_tac(ifs->then_block, prog, arena,loop_ctx);

            tac_append(prog, tac_create_instr(arena, TAC_LABEL, NULL, NULL, NULL, NULL, end_label));
            return NULL;
        }

        case AST_LOOP: {
            AST_Loop* loop = node->data;

            char* cond_label = new_label(arena);
            char* body_label = new_label(arena);
            char* end_label  = new_label(arena);

            DataContext* zero_ctx = (DataContext*)arena_alloc(arena,sizeof(DataContext));
            zero_ctx->val.ival = 0;
            zero_ctx->type = TYPE_INT;

            LoopContext* new_ctx = (LoopContext*)arena_alloc(arena,sizeof(LoopContext));
            new_ctx->break_label = end_label,
            new_ctx->continue_label = cond_label;
            new_ctx->prev = loop_ctx;

            tac_append(prog, tac_create_instr(arena, TAC_LABEL, NULL, NULL, NULL, NULL, cond_label));

            OperatorContext* op_ctx = (OperatorContext*)arena_alloc(arena,sizeof(OperatorContext));
            op_ctx->operator_str = "!=";
            op_ctx->operator_type = BL_NOTEQ;

            DataContext* cond = gen_tac(loop->expr, prog, arena, new_ctx);
            tac_append(prog, tac_create_instr(arena, TAC_IFGOTO, NULL, cond, zero_ctx, op_ctx, body_label));
            
            tac_append(prog, tac_create_instr(arena, TAC_GOTO, NULL, NULL, NULL, NULL, end_label));

            tac_append(prog, tac_create_instr(arena, TAC_LABEL, NULL, NULL, NULL, NULL, body_label));
            gen_tac(loop->block, prog, arena, new_ctx);
            

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
            AST_Function* fn = node->data;
            AST_Identifier* name = fn->name->data;

            tac_append(prog, tac_create_instr(arena, TAC_FUNC_BEGIN, NULL, NULL, NULL, NULL, name->name));

            for (int i = 0; i < (int)fn->param_count; ++i) {
                char* param = ((AST_Identifier*)((AST_Node*)((AST_Param*)fn->params[i]->data)->ident)->data)->name;
                DataContext* param_ctx = (DataContext*)arena_alloc(arena,sizeof(DataContext));
                param_ctx->val.sval = param;
                param_ctx->type = TYPE_IDENTIFIER;
                tac_append(prog, tac_create_instr(arena, TAC_PARAM, NULL, param_ctx, NULL, NULL, NULL));
            }

            gen_tac(fn->block, prog, arena,loop_ctx);
            tac_append(prog, tac_create_instr(arena, TAC_FUNC_END, NULL, NULL, NULL, NULL, NULL));
            return NULL;
        }

        case AST_FUNCTIONCALL: {
            AST_FunctionCall* call = node->data;
            for (int i = 0; i < call->args_count; ++i) {
                DataContext* arg = gen_tac(call->args[i], prog, arena, loop_ctx);
                tac_append(prog, tac_create_instr(arena, TAC_ARG, NULL, arg, NULL, NULL, NULL));
            }

            DataContext* result = new_temp(arena);
            AST_Identifier* name = call->name->data;
            DataContext* name_ctx = (DataContext*)arena_alloc(arena, sizeof(DataContext));
            name_ctx->val.sval = name->name;
            name_ctx->type = TYPE_IDENTIFIER;

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
            char* str = arena_alloc(arena, strlen(buf) + 1);
            strcpy(str,buf);
            return str;
        }
        case TYPE_INT: {
            char buf[32];
            snprintf(buf,sizeof(buf),"%d",context->val.ival);
            char* str = arena_alloc(arena,strlen(buf) + 1);
            strcpy(str,buf);
            return str;
        }

        case TYPE_FLOAT: {
            char buf[32];
            snprintf(buf,sizeof(buf), "%.16f",context->val.fval);
            char* str = arena_alloc(arena, strlen(buf) + 1);
            strcpy(str,buf);
            return str;
        }

        case TYPE_CHAR: {
            char buf[32];
            snprintf(buf,sizeof(buf),"%c",context->val.cval);
            char* str = arena_alloc(arena,strlen(buf) + 1);
            strcpy(str,buf);
            return str;
        }

        case TYPE_STRING: {
            char buf[1024];
            snprintf(buf,sizeof(buf),"%s",context->val.sval);
            char* str = arena_alloc(arena,sizeof(buf) + 1);
            strcpy(str,buf);
            return str;
        }
        
        case TYPE_IDENTIFIER: {
            char buf[1024];
            snprintf(buf,sizeof(buf),"%s",context->val.sval);
            char* str = arena_alloc(arena,strlen(buf) + 1);
            strcpy(str,buf);
            return str;
        }

        case TYPE_VOID : {
            char* str = arena_alloc(arena,10);
            str = "void";
            return str;
        }

        case TYPE_UNKNOWN: {
            char* str = arena_alloc(arena,10);
            str = "unknown";
            return str;
        }
        
        default: {
            return NULL;
        }
    }
    return NULL;
}

void tac_print(TACList* list,bl_arena* arena) { 
    for (TACInstr* instr = list->head; instr; instr = instr->next) {
        switch (instr->op) {
            case TAC_ASSIGNDECL:
                if(instr->arg1){
                    printf("[Declaration] %s (%s) = %s (%s)\n", print_type_val(instr->result,arena),get_str_type(instr->result->type), print_type_val(instr->arg1,arena),get_str_type(instr->arg1->type));
                }else{
                    printf("[Declaration] %s (%s) unassigned\n", print_type_val(instr->result,arena),get_str_type(instr->result->type));
                }
                break;
            case TAC_ASSIGN:
                printf("[Assignment] %s (%s) %s %s (%s)\n", print_type_val(instr->result,arena),get_str_type(instr->result->type),instr->relop->operator_str, print_type_val(instr->arg1,arena),get_str_type(instr->arg1->type));
                break;
            case TAC_BINOP:
                
                printf("[Binary Op] %s (%s) = %s (%s) %s %s (%s)\n", print_type_val(instr->result,arena),get_str_type(instr->result->type), print_type_val(instr->arg1,arena),get_str_type(instr->arg1->type), instr->relop->operator_str, print_type_val(instr->arg2,arena),get_str_type(instr->arg2->type));
                break;
            case TAC_UNOP:
                printf("[Unary op] %s (%s) = %s %s (%s)\n", print_type_val(instr->result,arena),get_str_type(instr->result->type), instr->relop->operator_str, print_type_val(instr->arg1,arena),get_str_type(instr->arg1->type));
                break;
            case TAC_LABEL:
                printf("\n");
                printf("[Label] %s:\n", instr->label);
                break;
            case TAC_GOTO:
                printf("[Jump] goto %s\n", instr->label);
                break;
            case TAC_IFGOTO:
                printf("[Conditional Jump] if %s (%s) %s %s (%s) goto %s\n", print_type_val(instr->arg1,arena),get_str_type(instr->arg1->type), instr->relop->operator_str, print_type_val(instr->arg2,arena),get_str_type(instr->arg2->type), instr->label);
                break;
            case TAC_PARAM:
                printf("[Parameter] param %s\n", print_type_val(instr->arg1,arena));
                break;
            case TAC_ARG:
                printf("[Argument] arg %s\n",print_type_val(instr->arg1,arena));
                break;
            case TAC_CALL:
                printf("[Function call] %s (%s) = call %s (%s), %d\n", print_type_val(instr->result,arena),get_str_type(instr->result->type), print_type_val(instr->arg1,arena),get_str_type(instr->arg1->type), instr->arg_count);
                break;
            case TAC_RETURN:
                printf("[Return] return %s (%s)\n", print_type_val(instr->arg1,arena),get_str_type(instr->arg1->type));
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
                printf("[Extern] extern %s (%s)\n",print_type_val(instr->result,arena),get_str_type(instr->result->type));
                break;
            default:
                printf("nop\n");
                
        }
    }
}