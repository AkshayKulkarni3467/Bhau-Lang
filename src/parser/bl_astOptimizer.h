#include "bl_parser.h"
#include "bl_set.h"

// #define BL_OPTIMIZER_TEST

typedef enum {
    CONSTKIND_NONE,
    CONSTKIND_INT,
    CONSTKIND_FLOAT,
    CONSTKIND_BOOL,
    CONSTKIND_CHAR,
    CONSTKIND_STRING,
} ConstKind;

typedef struct {
    ConstKind kind;
    union {
        int i;
        float f;
        bool b;
        char c;
        const char* s;
    };
} ConstValue;

typedef struct {
    AST_Node** items;
    size_t count;
} AST_NodeList;

typedef struct{
    char* name;
    AST_Node* value;
    bool is_constant;
} ScopeVar;

typedef struct {
    char* name;
    int param_count;
} FunctionInfo;

typedef struct {
    FunctionInfo** items;
    int count;
    int capacity;
} FunctionRegistry;


ConstKind promote_kind(ConstKind a, ConstKind b);
ConstKind get_const_value(AST_Node* node, ConstValue* out);


bl_stack* scope_stack_init(bl_arena* arena);
void scope_push(bl_stack* stack,char* name, AST_Node* value,bool is_constant, bl_arena* arena);
ScopeVar* scope_pop(bl_stack* stack);
ScopeVar* scope_pop_until(bl_stack* stack,AST_Node* value,bool is_constant);
bool scope_find(bl_stack* stack, char* name);
int get_scope_size(bl_stack* stack);
void scope_switch_constant(bl_stack* stack,bl_set* set,char* name,bl_arena* arena);
void scope_update(bl_stack* stack,char* name, AST_Node* value);
void print_current_scope(bl_stack* stack);
AST_Node* scope_get_most_recent(bl_stack* stack, char* name);

bool is_constant(AST_Node* node);
bool is_terminating_node(AST_Node* node);
int eval_binop_int(enum KEYWORD_TYPES op, int lhs, int rhs);
void promote_values(ConstValue* lhs, ConstValue* rhs, ConstKind target);
void optimize_block(AST_Block* block, bl_arena* arena) ;
size_t count_assignment_chain(AST_Node* node);
AST_Node* transform_undeclared_assigns(AST_Node* node, bl_arena* arena);
AST_Node* propogate_scope(AST_Node* node, bl_stack* stack,bl_set* set,bl_arena* arena);
AST_Node* fold_constants_from_scope(AST_Node* node, bl_stack* stack, bl_set* non_const_set, bl_arena* arena);
AST_Node* check_function_arity(AST_Node* node, FunctionRegistry* reg,bl_arena* arena);


AST_Node* fold_constants(AST_Binop* bin, bl_arena* arena);
AST_Node* make_int_literal_node(bl_arena* arena, int value);
AST_Node* make_bool_literal_node(bl_arena* arena, int value);
AST_Node* make_float_literal_node(bl_arena* arena, float value);
AST_Node* optimize_ast(AST_Node* node,bl_arena* arena);
AST_Node* flatten_assignment_chain(AST_Node* assign, bl_arena* arena);
AST_NodeList flatten_comma_chain(AST_Node* node, bl_arena* arena);

void func_registry_init(FunctionRegistry* reg, bl_arena* arena);
void func_registry_add(FunctionRegistry* reg, char* name, int param_count, bl_arena* arena);
int func_registry_get(FunctionRegistry* reg, char* name);

AST_Node* perform_optimization(AST_Node* ast,bl_arena* arena);
AST_Node* bhaulang_optimizer(char* filename, bl_arena* arena);


#ifdef BL_OPTIMIZER_TEST

int main(){
    bl_arena* arena = (bl_arena*)malloc(sizeof(bl_arena));
    arena_init(arena);



    AST_Node* op_ast = bhaulang_optimizer("src/ir/one.bl",arena);

    print_ast_tree(op_ast,0,"");
    arena_stats(arena);
    return 0;
}

#endif

AST_Node* bhaulang_optimizer(char* filename, bl_arena* arena){
    AST_Node* ast = bhaulang_parser(filename,arena);
    AST_Node* op_ast = perform_optimization(ast,arena);
    return op_ast;
}

AST_Node* perform_optimization(AST_Node* ast,bl_arena* arena){
    bl_stack* scope_stack = scope_stack_init(arena);    
    bl_set* scope_set = set_create(arena);
    FunctionRegistry* reg = arena_alloc(arena, sizeof(FunctionRegistry));
    func_registry_init(reg, arena);
    AST_Node* optimized_ast = optimize_ast(ast,arena);
    AST_Node* transformed_ast = transform_undeclared_assigns(optimized_ast,arena);
    AST_Node* scoped_ast = propogate_scope(transformed_ast,scope_stack,scope_set,arena);
    scope_stack = scope_stack_init(arena);
    AST_Node* const_prop_ast = fold_constants_from_scope(scoped_ast,scope_stack,scope_set,arena);
    AST_Node* reoptimized_ast = optimize_ast(const_prop_ast,arena);
    AST_Node* arity_checked_ast = check_function_arity(reoptimized_ast,reg,arena);
    return arity_checked_ast;
}

void func_registry_init(FunctionRegistry* reg, bl_arena* arena) {
    reg->count = 0;
    reg->capacity = 1024;
    reg->items = arena_alloc(arena, sizeof(FunctionInfo*) * reg->capacity);
    memset(reg->items, 0, sizeof(FunctionInfo*) * reg->capacity);
}

void func_registry_add(FunctionRegistry* reg, char* name, int param_count, bl_arena* arena) {
    if (reg->count >= reg->capacity) return; 
    FunctionInfo* info = arena_alloc(arena, sizeof(FunctionInfo));
    info->name = name;
    info->param_count = param_count;
    reg->items[reg->count++] = info;
}

int func_registry_get(FunctionRegistry* reg, char* name) {
    for (int i = 0; i < reg->count; ++i) {
        if (strcmp(reg->items[i]->name, name) == 0) {
            return reg->items[i]->param_count;
        }
    }
    return -1;
}



ConstKind promote_kind(ConstKind a, ConstKind b) {
    if (a == CONSTKIND_STRING || b == CONSTKIND_STRING) return CONSTKIND_STRING;
    if (a == CONSTKIND_FLOAT || b == CONSTKIND_FLOAT) return CONSTKIND_FLOAT;
    if (a == CONSTKIND_INT || b == CONSTKIND_INT) return CONSTKIND_INT;
    if (a == CONSTKIND_CHAR || b == CONSTKIND_CHAR) return CONSTKIND_INT;
    if (a == CONSTKIND_BOOL || b == CONSTKIND_BOOL) return CONSTKIND_INT;
    return CONSTKIND_NONE;
}

ConstKind get_const_value(AST_Node* node, ConstValue* out) {
    if (!node) return CONSTKIND_NONE;

    switch (node->type) {
        case AST_INTLITERAL: {
            AST_IntLiteral* lit = node->data;
            out->kind = CONSTKIND_INT;
            out->i = lit->value;
            return CONSTKIND_INT;
        }
        case AST_FLOATLITERAL: {
            AST_FloatLiteral* lit = node->data;
            out->kind = CONSTKIND_FLOAT;
            out->f = lit->value;
            return CONSTKIND_FLOAT;
        }
        case AST_BOOLLITERAL: {
            AST_BoolLiteral* lit = node->data;
            out->kind = CONSTKIND_BOOL;
            out->b = lit->value;
            return CONSTKIND_BOOL;
        }
        case AST_CHARLITERAL: {
            AST_CharLiteral* lit = node->data;
            out->kind = CONSTKIND_CHAR;
            out->c = lit->value;
            return CONSTKIND_CHAR;
        }
        case AST_STRINGLITERAL: {
            AST_StringLiteral* lit = node->data;
            out->kind = CONSTKIND_STRING;
            out->s = lit->value;
            return CONSTKIND_STRING;
        }
        default:
            return CONSTKIND_NONE;
    }
}

void promote_values(ConstValue* lhs, ConstValue* rhs, ConstKind target) {
    if (lhs->kind != target) {
        switch (target) {
            case CONSTKIND_INT:
                if (lhs->kind == CONSTKIND_BOOL) lhs->i = lhs->b;
                if (lhs->kind == CONSTKIND_CHAR) lhs->i = lhs->c;
                lhs->kind = CONSTKIND_INT;
                break;
            case CONSTKIND_FLOAT:
                if (lhs->kind == CONSTKIND_INT) lhs->f = lhs->i;
                if (lhs->kind == CONSTKIND_BOOL) lhs->f = lhs->b;
                if (lhs->kind == CONSTKIND_CHAR) lhs->f = lhs->c;
                lhs->kind = CONSTKIND_FLOAT;
                break;
            default: break;
        }
    }
    if (rhs->kind != target) {
        switch (target) {
            case CONSTKIND_INT:
                if (rhs->kind == CONSTKIND_BOOL) rhs->i = rhs->b;
                if (rhs->kind == CONSTKIND_CHAR) rhs->i = rhs->c;
                rhs->kind = CONSTKIND_INT;
                break;
            case CONSTKIND_FLOAT:
                if (rhs->kind == CONSTKIND_INT) rhs->f = rhs->i;
                if (rhs->kind == CONSTKIND_BOOL) rhs->f = rhs->b;
                if (rhs->kind == CONSTKIND_CHAR) rhs->f = rhs->c;
                rhs->kind = CONSTKIND_FLOAT;
                break;
            default: break;
        }
    }
}

AST_Node* fold_constants(AST_Binop* bin, bl_arena* arena) {
    ConstValue lhs = {0}, rhs = {0};
    ConstKind lhs_kind = get_const_value(bin->lhs, &lhs);
    ConstKind rhs_kind = get_const_value(bin->rhs, &rhs);

    if (lhs_kind == CONSTKIND_NONE || rhs_kind == CONSTKIND_NONE)
        return NULL;

    ConstKind target_kind = promote_kind(lhs_kind, rhs_kind);
    promote_values(&lhs, &rhs, target_kind);

    switch (target_kind) {
        case CONSTKIND_INT: {
            int result;
            switch (bin->op) {
                case BL_ADDBINOP: result = lhs.i + rhs.i; break;
                case BL_SUBBINOP: result = lhs.i - rhs.i; break;
                case BL_MULTBINOP: result = lhs.i * rhs.i; break;
                case BL_DIVBINOP: result = rhs.i != 0 ? lhs.i / rhs.i : 0; break;
                case BL_MODBINOP: result = rhs.i != 0 ? lhs.i % rhs.i : 0; break;
                case BL_AND: result = lhs.i & rhs.i; break;
                case BL_OR: result = lhs.i | rhs.i; break;
                case BL_XOR: result = lhs.i ^ rhs.i; break;
                case BL_LSHIFT: result = lhs.i << rhs.i; break;
                case BL_RSHIFT: result = lhs.i >> rhs.i; break;
                case BL_LOGAND: return make_bool_literal_node(arena, lhs.i && rhs.i);
                case BL_LOGOR: return make_bool_literal_node(arena, lhs.i || rhs.i);
                case BL_ISEQUALCOND: return make_bool_literal_node(arena, lhs.i == rhs.i);
                case BL_NOTEQ: return make_bool_literal_node(arena, lhs.i != rhs.i);
                case BL_LESSTHAN: return make_bool_literal_node(arena, lhs.i < rhs.i);
                case BL_GRTEQ: return make_bool_literal_node(arena, lhs.i >= rhs.i);
                case BL_LESSEQ: return make_bool_literal_node(arena,lhs.i <= rhs.i);
                case BL_GRTTHAN: return make_bool_literal_node(arena, lhs.i > rhs.i);
                default: return NULL;
            }
            return make_int_literal_node(arena, result);
        }

        case CONSTKIND_FLOAT: {
            float result;
            switch (bin->op) {
                case BL_ADDBINOP: result = lhs.f + rhs.f; break;
                case BL_SUBBINOP: result = lhs.f - rhs.f; break;
                case BL_MULTBINOP: result = lhs.f * rhs.f; break;
                case BL_DIVBINOP: result = rhs.f != 0.0f ? lhs.f / rhs.f : 0.0f; break;
                case BL_ISEQUALCOND: return make_bool_literal_node(arena, lhs.f == rhs.f);
                case BL_NOTEQ: return make_bool_literal_node(arena, lhs.f != rhs.f);
                case BL_LESSTHAN: return make_bool_literal_node(arena, lhs.f < rhs.f);
                case BL_GRTEQ: return make_bool_literal_node(arena, lhs.f >= rhs.f);
                case BL_LESSEQ: return make_bool_literal_node(arena,lhs.f <= rhs.f);
                case BL_GRTTHAN: return make_bool_literal_node(arena,lhs.f > rhs.f);
                case BL_LOGAND: return make_bool_literal_node(arena,lhs.f && rhs.f);
                case BL_LOGOR: return make_bool_literal_node(arena,lhs.f || rhs.f);
                default: return NULL;
            }
            return make_float_literal_node(arena, result);
        }

        case CONSTKIND_STRING: {
            if (bin->op == BL_ISEQUALCOND || bin->op == BL_NOTEQ) {
                bool same = strcmp(lhs.s, rhs.s) == 0;
                return make_bool_literal_node(arena, bin->op == BL_ISEQUALCOND ? same : !same);
            }
            fprintf(stderr,"Only comparsion is allowed between strings\n");
            exit(12);
            return NULL;
        }

        default:
            return NULL;
    }
}

AST_Node* make_float_literal_node(bl_arena* arena, float value){
    AST_FloatLiteral* lit = arena_alloc(arena,sizeof(AST_FloatLiteral));
    lit->type = AST_FLOATLITERAL;
    lit->value = value;

    AST_Node* node = arena_alloc(arena,sizeof(AST_Node));
    node->type = AST_FLOATLITERAL;
    node->data = lit;

    return node;
}

AST_Node* make_bool_literal_node(bl_arena* arena, int value){
    AST_BoolLiteral* lit = arena_alloc(arena,sizeof(AST_BoolLiteral));
    lit->type = AST_BOOLLITERAL;
    lit->value = value == 1 ? true : false;

    AST_Node* node = arena_alloc(arena,sizeof(AST_Node));
    node->type = AST_BOOLLITERAL;
    node->data = lit;
    return node;
}

AST_Node* make_int_literal_node(bl_arena* arena, int value) {
    AST_IntLiteral* lit = arena_alloc(arena, sizeof(AST_IntLiteral));
    lit->type = AST_INTLITERAL;
    lit->value = value;

    AST_Node* node = arena_alloc(arena, sizeof(AST_Node));
    node->type = AST_INTLITERAL;
    node->data = lit;
    return node;
}

bool is_constant(AST_Node* node) {
    if(node->type == AST_INTLITERAL    ||
        node->type == AST_FLOATLITERAL ||
        node->type == AST_CHARLITERAL  ||
        node->type == AST_STRINGLITERAL){
            return true;
        }
    return false;
}

bool is_terminating_node(AST_Node* node) {
    if (!node) return false;
    switch (node->type) {
        case AST_RETURN:
        case AST_BREAK:
        case AST_CONTINUE:
            return true;
        
        default:
            return false;
    }
}

int eval_binop_int(enum KEYWORD_TYPES op, int lhs, int rhs) {
    switch (op) {
        case BL_ADDBINOP: return lhs + rhs;
        case BL_SUBBINOP: return lhs - rhs;
        case BL_MULTBINOP: return lhs * rhs;
        case BL_DIVBINOP: return rhs != 0 ? lhs / rhs : 0; 
        case BL_MODBINOP: return rhs != 0 ? lhs % rhs : 0;
        case BL_LESSTHAN: return lhs < rhs;
        case BL_LESSEQ  : return lhs <= rhs;
        case BL_GRTEQ   :    return lhs >= rhs;
        case BL_GRTTHAN : return lhs > rhs;
        case BL_ISEQUALCOND: return lhs == rhs;
        case BL_NOTEQ: return lhs != rhs;
        case BL_AND     : return lhs & rhs;
        case BL_OR      : return lhs | rhs;
        case BL_XOR     : return lhs ^ rhs;
        case BL_LSHIFT  : return lhs << rhs;
        case BL_RSHIFT  : return lhs >> rhs;
        case BL_LOGAND  : return lhs && rhs;
        case BL_LOGOR  : return lhs || rhs;
        default: return 0;
    }
}


ConstValue eval_unary_expr(enum KEYWORD_TYPES op, ConstValue val) {
    ConstValue result = val;

    switch (val.kind) {
        case CONSTKIND_INT:
        case CONSTKIND_CHAR: {
            int v = (val.kind == CONSTKIND_CHAR) ? val.c : val.i;
            switch (op) {
                case BL_NOT: result.kind = CONSTKIND_INT; result.i = !v; break;
                case BL_SUBBINOP: result.kind = CONSTKIND_INT; result.i = -v; break;
                case BL_INC : result.kind = CONSTKIND_INT; result.i = v+1; break;
                case BL_DEC : result.kind = CONSTKIND_INT; result.i = v-1; break;
                default: break;
            }
            break;
        }

        case CONSTKIND_FLOAT: {
            switch (op) {
                case BL_NOT: result.kind = CONSTKIND_INT; result.i = !(val.f); break;
                case BL_SUBBINOP: result.kind = CONSTKIND_FLOAT; result.f = -val.f; break;
                case BL_INC: result.kind = CONSTKIND_FLOAT; result.f = val.f+1; break;
                case BL_DEC: result.kind = CONSTKIND_FLOAT; result.f = val.f-1; break;
                default: break;
            }
            break;
        }

        case CONSTKIND_BOOL: {
            switch (op) {
                case BL_NOT: result.kind = CONSTKIND_INT; result.i = !val.b; break;
                case BL_SUBBINOP: result.kind = CONSTKIND_INT; result.i = -(int)(val.b); break;
                default: break;
            }
            break;
        }

        default:
            result.kind = CONSTKIND_NONE;
            break;
    }

    return result;
}

void optimize_block(AST_Block* block, bl_arena* arena) {
    AST_Node** new_body = arena_alloc(arena, sizeof(AST_Node*) * block->body_count);
    size_t new_count = 0;
    bool reached_return = false;

    for (size_t i = 0; i < block->body_count; ++i) {
        AST_Node* stmt = optimize_ast(block->body[i], arena);
        if (!stmt) continue;

        if (reached_return) continue;

        if (stmt->type == AST_COMMENT || stmt->type == AST_MULCOMMENT) {
            continue;
        }

        new_body[new_count++] = stmt;

        if(is_terminating_node(stmt)){
            reached_return = true;
        }
    }

    block->body = new_body;
    block->body_count = new_count;
}

size_t count_assignment_chain(AST_Node* node) {
    size_t count = 0;
    while (node && node->type == AST_ASSIGNDECL) {
        AST_Assign* asg = node->data;
        count++;
        node = asg->rhs;
    }
    return count;
}

AST_NodeList flatten_comma_chain(AST_Node* node, bl_arena* arena) {
    size_t max = 16;  
    AST_Node** list = arena_alloc(arena, sizeof(AST_Node*) * max);
    size_t count = 0;

    AST_Node* current = node;
    while (current && current->type == AST_ASSIGNDECL) {
        AST_Assign* asg = current->data;

        if (asg->op != BL_COMMA) break;

        if (count >= max) {
            fprintf(stderr, "Comma chain too deep\n");
            break;
        }

        list[count++] = asg->lhs;
        current = asg->rhs;
    }

    if (count < max) {
        list[count++] = current;
    }

    AST_NodeList result = { .items = list, .count = count };
    return result;
}

AST_Node* flatten_assignment_chain(AST_Node* assign, bl_arena* arena) {
    size_t count = count_assignment_chain(assign);

 
    AST_Node** lhs_list = arena_alloc(arena, sizeof(AST_Node*) * count);
    AST_Node* rhs = NULL;

    AST_Node* current = assign;
    for (size_t i = 0; i < count; ++i) {
        AST_Assign* asg = current->data;
        lhs_list[i] = asg->lhs;
        if (asg->rhs->type != AST_ASSIGNDECL) {
            rhs = asg->rhs;
            break;
        }
        current = asg->rhs;
    }


    AST_Node** assigns = arena_alloc(arena, sizeof(AST_Node*) * count);

    for (size_t i = 0; i < count; ++i) {
        AST_Assign* new_asg = arena_alloc(arena, sizeof(AST_Assign));
        new_asg->lhs = lhs_list[count - 1 - i];  
        new_asg->rhs = rhs;
        new_asg->op = BL_EQUAL;
        new_asg->type = AST_ASSIGNDECL;

        AST_Node* asg_node = arena_alloc(arena, sizeof(AST_Node));
        asg_node->type = AST_ASSIGNDECL;
        asg_node->data = new_asg;

        assigns[i] = asg_node;
    }

    AST_Block* blk = arena_alloc(arena, sizeof(AST_Block));
    blk->type = AST_BLOCK;
    blk->body = assigns;
    blk->body_count = count;

    AST_Node* block_node = arena_alloc(arena, sizeof(AST_Node));
    block_node->type = AST_BLOCK;
    block_node->data = blk;

    return block_node;
}

AST_Node* transform_undeclared_assigns(AST_Node* node, bl_arena* arena){
    if (!node) return NULL;
    switch (node->type) {
        case AST_PROGRAM: {
            ASTProgram* prog = (ASTProgram*)node->data;
            for (size_t i = 0; i < prog->count; ++i) {
                prog->statements[i] = transform_undeclared_assigns(prog->statements[i], arena);
            }
            break;
        }

        case AST_BLOCK:{
            AST_Block* blk = (AST_Block*)node->data;
            for (size_t i = 0; i < blk->body_count; ++i) {
                blk->body[i] = transform_undeclared_assigns(blk->body[i], arena);
            }
            break;
        }

        case AST_MAIN: {
            AST_Main* main = (AST_Main*)node->data;
            main->block = transform_undeclared_assigns(main->block, arena);
            break;
        }

        case AST_FUNCTION: {
            AST_Function* func = (AST_Function*)node->data;
            func->block = transform_undeclared_assigns(func->block,arena);
            break;
        }

        case AST_IFELSE: {
            AST_Ifelse* ifs = (AST_Ifelse*)node->data;
            ifs->then_block = transform_undeclared_assigns(ifs->then_block, arena);
            ifs->else_block = transform_undeclared_assigns(ifs->else_block, arena);
            break;
        }

        case AST_LOOP: {
            AST_Loop* loop = (AST_Loop*)node->data;
            loop->block = transform_undeclared_assigns(loop->block, arena);
            break;
        }

        case AST_SWITCH: {
            AST_Switch* sw = (AST_Switch*)node->data;
            for (size_t i = 0; i < sw->case_count; ++i) {
                sw->cases[i] = transform_undeclared_assigns(sw->cases[i], arena);
            }
            sw->default_case = transform_undeclared_assigns(sw->default_case, arena);
            break;
        }

        case AST_CASE:
        case AST_DEFAULT: {
            AST_SwitchCase* sc = (AST_SwitchCase*)node->data;
            if (node->type == AST_CASE)
                sc->value = transform_undeclared_assigns(sc->value, arena);
            for (size_t i = 0; i < sc->body_count; ++i) {
                sc->body[i] = transform_undeclared_assigns(sc->body[i], arena);
            }
            break;
        }

        case AST_UNOP: {
            AST_Unop* u_node = (AST_Unop*)node->data;
            if(u_node->op == (enum KEYWORD_TYPES)BL_KW_BHAU_PTR){
                AST_Assign* decl = (AST_Assign*)arena_alloc(arena, sizeof(AST_Assign));
                decl->lhs = node;
                decl->rhs = NULL;
                decl->op = BL_EQUAL;
                decl->type = AST_ASSIGNDECL;
                AST_Node* wrapper = (AST_Node*)arena_alloc(arena, sizeof(AST_Node));
                wrapper->type = AST_ASSIGNDECL;
                wrapper->data = decl;
                return wrapper;
            }
            break;
        }

        case AST_IDENTIFIER: {
            AST_Assign* decl = (AST_Assign*)arena_alloc(arena, sizeof(AST_Assign));
            decl->lhs = node;
            decl->rhs = NULL;
            decl->op = BL_EQUAL;
            decl->type = AST_ASSIGNDECL;
            AST_Node* wrapper = (AST_Node*)arena_alloc(arena, sizeof(AST_Node));
            wrapper->type = AST_ASSIGNDECL;
            wrapper->data = decl;
            return wrapper;
        }

        default:
            break;
    }
    return node;
}

bl_stack* scope_stack_init(bl_arena* arena){
    bl_stack* scope_stack = (bl_stack*)arena_alloc(arena,sizeof(bl_stack));
    stack_init(scope_stack,arena,4096);
    return scope_stack;
}

void scope_push_seperation(bl_stack* stack, char* sep_name,bl_arena* arena){
    ScopeVar* var = (ScopeVar*)arena_alloc(arena,sizeof(ScopeVar));
    var->name = sep_name;
    var->value = NULL;
    var->is_constant = NULL;
    stack_push(stack,var);
}

void scope_push(bl_stack* stack,char* name, AST_Node* value,bool is_constant, bl_arena* arena){
    ScopeVar* var = (ScopeVar*)arena_alloc(arena,sizeof(ScopeVar));
    var->name = name;
    var->value = value;
    var->is_constant = is_constant;
    stack_push(stack,var);
}

void scope_update(bl_stack* stack,char* name, AST_Node* value){
    int num = stack_size(stack) - 1;
    for(int i = num;i>=0;i--){
        ScopeVar* item = stack->items[i];
        if(item->name == NULL) continue;
        if(strcmp(name,item->name) == 0){
                item->value = value;
        }
    }
}

ScopeVar* scope_pop(bl_stack* stack){
    return stack_pop(stack);
}

ScopeVar* scope_pop_until(bl_stack* stack,AST_Node* value,bool is_constant){
    while(stack_size(stack) > 0){
        ScopeVar* var = stack_peek(stack);
        if(!var || (var->value == value && var->is_constant == is_constant)){
            ScopeVar* var = stack_pop(stack);
            if(stack_size(stack) != 0){
                var = stack_peek(stack);
            }else{
                var = NULL;
            }
            return var;
        }else{
            stack_pop(stack);
        }
    }
    return NULL;
}

bool scope_find(bl_stack* stack, char* name){
    int num = stack_size(stack) - 1;
    for(int i = num;i>=0;i--){
        ScopeVar* item = stack->items[i];
        if(item->name == NULL) continue;
        if(strcmp(name,item->name) == 0){
                if(item->value == NULL){
                    return false;
                }else{
                    return true;
                }
        }
    }
    return false;
}

int get_scope_size(bl_stack* stack){
    int num = 0;
    for(int i = 0;i< (int)stack_size(stack);i++){
        ScopeVar* var = stack_get_index(stack,i);
        if(!(var->name == NULL && var->value == NULL && var->is_constant == (long)NULL)){
            num++;
        }
    }   
    return num;
}

void scope_switch_constant(bl_stack* stack,bl_set* set,char* name,bl_arena* arena){
    int num = stack_size(stack) - 1;
    for(int i = num; i>= 0; i--){
        ScopeVar* var = stack->items[i];
        if(var->name == NULL) continue;
        if(strcmp(var->name,name) == 0){
            if(var->is_constant == true){
                var->is_constant = false;
                set_insert(set,var->name,arena);
            }
        }
    }
}


void print_current_scope(bl_stack* stack){
    int size = stack_size(stack);
    for(int i = size-1; i>=0; i--){
        ScopeVar* val = stack->items[i];
        if(val->value == NULL && val->is_constant == (long)NULL){
            printf("==================================== (%s)\n",val->name);
        }else if(val->value == NULL){
            printf("%s  : (null) <- Undefined (%s)\n",val->name,val->is_constant == true? "true":"false");
        }else{
            printf("%s      : ",val->name);
            if(val->value->type == AST_INTLITERAL){
                AST_IntLiteral* ilit = (AST_IntLiteral*)val->value->data;
                printf("%d <- int (%s)\n",ilit->value,val->is_constant == true? "constant" : "not constant");
            }else if(val->value->type == AST_CHARLITERAL){
                AST_CharLiteral* clit = (AST_CharLiteral*)val->value->data;
                printf("%c <- char (%s)\n",clit->value,val->is_constant == true? "constant" : "not constant");
            }else if(val->value->type == AST_STRINGLITERAL){
                AST_StringLiteral* slit = (AST_StringLiteral*)val->value->data;
                printf("%s <- str (%s)\n",slit->value,val->is_constant == true? "constant" : "not constant");
            }else if(val->value->type == AST_FLOATLITERAL){
                AST_FloatLiteral* flit = (AST_FloatLiteral*)val->value->data;
                printf("%.2f <- float (%s)\n",flit->value,val->is_constant == true? "constant" : "not constant");
            }else if(val->value->type == AST_BOOLLITERAL){
                AST_BoolLiteral* blit = (AST_BoolLiteral*)val->value->data;
                printf("%s <- bool (%s)\n",blit->value == true ? "true" : "false",val->is_constant == true? "constant" : "not constant");
            }else if(val->value->type == AST_IDENTIFIER){
                AST_Identifier* ilit = (AST_Identifier*)val->value->data;
                printf("%s <- ident (%s)\n",ilit->name, val->is_constant == true? "constant":"not constant");
            }else if(val->value->type == AST_FUNCTIONCALL){
                AST_FunctionCall* fcall = (AST_FunctionCall*)val->value->data;
                AST_Identifier* fcall_name = (AST_Identifier*)fcall->name->data;
                printf("%s <- func call (%s)\n",fcall_name->name,val->is_constant == true? "constant":"not constant");
            }
            else{
                printf("Undefined node\n");
            }
        }
    }
}

AST_Node* scope_get_most_recent(bl_stack* stack, char* name) {
    int num = stack_size(stack) - 1;
    for (int i = num; i >= 0; i--) {
        ScopeVar* item = stack->items[i];
        if (!item || item->name == NULL || item->value == NULL) continue;

        if (strcmp(name, item->name) == 0) {
            return item->value;
        }
    }
    return NULL; 
}

AST_Node* optimize_ast(AST_Node* node, bl_arena* arena) {
    if (!node) return NULL;

    switch (node->type) {
        case AST_BINOP: {
            AST_Binop* bin = node->data;
            bin->lhs = optimize_ast(bin->lhs, arena);
            bin->rhs = optimize_ast(bin->rhs, arena);

            if (is_constant(bin->lhs) && is_constant(bin->rhs)) {
                return fold_constants(bin,arena);
            }
            return node;
        }

        case AST_UNOP: {
            AST_Unop* uop = node->data;
            uop->node = optimize_ast(uop->node, arena);
            
            ConstValue val = {0};
            if (get_const_value(uop->node, &val) != CONSTKIND_NONE) {
                ConstValue folded = eval_unary_expr(uop->op, val);
                switch (folded.kind) {
                    case CONSTKIND_INT:
                        return make_int_literal_node(arena, folded.i);
                    case CONSTKIND_FLOAT:
                        return make_float_literal_node(arena, folded.f);
                    case CONSTKIND_BOOL:
                        return make_bool_literal_node(arena, folded.i != 0); 
                    default:
                        break;
                }
            }

            return node;
        }

        case AST_ASSIGN: {
            AST_Assign* asg = node->data;
            asg->lhs = optimize_ast(asg->lhs, arena);
            asg->rhs = optimize_ast(asg->rhs, arena);
            return node;
        }

        case AST_ASSIGNDECL: {
            AST_Assign* asg = node->data;
            if (asg->op == BL_COMMA) {
                AST_NodeList idents = flatten_comma_chain(node, arena);

                AST_Node** decls = arena_alloc(arena, sizeof(AST_Node*) * idents.count);

                for (size_t i = 0; i < idents.count; ++i) {
                    AST_Assign* decl = arena_alloc(arena, sizeof(AST_Assign));
                    decl->lhs = idents.items[i];
                    if(idents.items[i]->type != AST_UNOP){
                        AST_Identifier* ident = (AST_Identifier*)idents.items[i]->data;
                        AST_Node* decl_node = arena_alloc(arena, sizeof(AST_Node));
                        decl_node->type = AST_IDENTIFIER;
                        decl_node->data = ident;

                        decls[i] = decl_node;
                    }else{
                        fprintf(stderr,"Cannot assign pointers with comma currently\n");
                        exit(69);
                    }
                }


                AST_Block* blk = arena_alloc(arena, sizeof(AST_Block));
                blk->type = AST_BLOCK;
                blk->body = decls;
                blk->body_count = idents.count;
                

                AST_Node* blk_node = arena_alloc(arena, sizeof(AST_Node));
                blk_node->type = AST_BLOCK;
                blk_node->data = blk;


                return blk_node;
            }
            if (asg->rhs && asg->rhs->type == AST_ASSIGNDECL && asg->op == BL_EQUAL) {
                AST_Node* flattened = flatten_assignment_chain(node, arena);
                return optimize_ast(flattened, arena);
            }

            asg->lhs = optimize_ast(asg->lhs, arena);
            if (asg->rhs) {
                asg->rhs = optimize_ast(asg->rhs, arena);
            }
            return node;
        }

        case AST_IFELSE: {
            AST_Ifelse* ifs = node->data;
            ifs->condition = optimize_ast(ifs->condition, arena);
            ifs->then_block = optimize_ast(ifs->then_block, arena);

            ifs->else_block = optimize_ast(ifs->else_block, arena);
            return node;
        }

        case AST_LOOP: {
            AST_Loop* loop = node->data;
            loop->expr = optimize_ast(loop->expr, arena);
            loop->block = optimize_ast(loop->block, arena);

            if (is_constant(loop->expr)) {
                AST_IntLiteral* lit = loop->expr->data;
                if (lit->value == 0) return NULL; 
            }
            return node;
        }

        case AST_FUNCTION: {
            AST_Function* fn = (AST_Function*)node->data;
            fn->block = optimize_ast(fn->block, arena);
            if (fn->block && fn->block->type == AST_BLOCK) {
                optimize_block(fn->block->data, arena);
            }

            return node;
        }
        case AST_MAIN: {
            AST_Main* fn = (AST_Main*)node->data;
            fn->block = optimize_ast(fn->block, arena);
            if (fn->block && fn->block->type == AST_BLOCK) {
                optimize_block(fn->block->data, arena);
            }

            return node;
        }

        case AST_BLOCK: {
            AST_Block* block = node->data;
            for (size_t i = 0; i < block->body_count; ++i) {
                block->body[i] = optimize_ast(block->body[i], arena);
            }
            optimize_block(block, arena);
            return node;
        }

        case AST_PROGRAM: {
            ASTProgram* prog = node->data;
            for (size_t i = 0; i < prog->count; ++i) {
                prog->statements[i] = optimize_ast(prog->statements[i], arena);
            }
            //WARN sneaky hack!! can cause undefined behaviour :)
            optimize_block((AST_Block*)prog, arena);
            return node;
        }

        case AST_FUNCTIONCALL: {
            AST_FunctionCall* call = node->data;
            for (int i = 0; i < call->args_count; ++i) {
                call->args[i] = optimize_ast(call->args[i], arena);
            }
            return node;
        }

        case AST_GROUP: {
            AST_Group* grp = node->data;
            grp->expr = optimize_ast(grp->expr, arena);
            return grp->expr;
        }

        case AST_RETURN: {
            AST_Return* ret = node->data;
            ret->expr = optimize_ast(ret->expr, arena);
            return node;
        }


        default:
            return node;
    }
}

AST_Node* propogate_scope(AST_Node* node, bl_stack* stack,bl_set* set,bl_arena* arena){
    if (!node) return NULL;
    switch (node->type){
        case AST_PROGRAM:{
            scope_push_seperation(stack,"program",arena);
            ASTProgram* prog = node->data;
            for (size_t i = 0; i < prog->count; ++i) {
                prog->statements[i] = propogate_scope(prog->statements[i],stack,set, arena);
            }
            scope_pop_until(stack,NULL,NULL);
            return node;
        }

        case AST_PARAM: {
            AST_Param* param = (AST_Param*)arena_alloc(arena,sizeof(AST_Param));
            param = (AST_Param*)node->data;
            AST_Node* ide = (AST_Node*)param->ident;
            AST_Identifier* ident = (AST_Identifier*)ide->data;
            AST_Node* val_wrapper = (AST_Node*)arena_alloc(arena,sizeof(AST_Node));
            AST_IntLiteral* ilit = (AST_IntLiteral*)arena_alloc(arena,sizeof(AST_IntLiteral));
            ilit->value = 0;
            ilit->type = AST_INTLITERAL;
            val_wrapper->data = ilit;
            val_wrapper->type = AST_INTLITERAL;
            scope_push(stack,ident->name,val_wrapper,false,arena);
            set_insert(set,ident->name,arena);
            return node;
        }
            
        case AST_ASSIGNDECL:{
            AST_Assign* assign = (AST_Assign*)node->data;
            if(assign->lhs->type != AST_UNOP){
                AST_Identifier* ident = assign->lhs->data;
                assign->rhs = propogate_scope(assign->rhs,stack,set,arena);
                scope_push(stack,ident->name,assign->rhs,true,arena);
                return node;
            }else{
                AST_Unop* unop = (AST_Unop*)assign->lhs->data;
                while(unop->node->type == AST_UNOP){
                    unop = (AST_Unop*)unop->node->data;
                }
                AST_Identifier* ident = unop->node->data;
                assign->rhs = propogate_scope(assign->rhs,stack,set,arena);
                scope_push(stack,ident->name,assign->rhs,true,arena);
                return node;
            }
        }

        case AST_ASSIGN: {
            AST_Assign* assign = (AST_Assign*)node->data;
            if(assign->lhs->type != AST_UNOP){
                AST_Identifier* ident = assign->lhs->data;
                scope_switch_constant(stack,set,ident->name,arena);
                scope_update(stack,ident->name,assign->rhs);
                assign->rhs = propogate_scope(assign->rhs,stack,set,arena);
                return node;
            }else{
                AST_Unop* unop = (AST_Unop*)assign->lhs->data;
                while(unop->node->type == AST_UNOP){
                    unop = (AST_Unop*)unop->node->data;
                }
                AST_Identifier* ident = unop->node->data;
                scope_update(stack,ident->name,assign->rhs);
                unop->node = propogate_scope(unop->node,stack,set,arena);
                assign->rhs = propogate_scope(assign->rhs,stack,set,arena);
                return node;
            }
        }

        case AST_IFELSE: {
            AST_Ifelse* ifs = node->data;
            ifs->condition = propogate_scope(ifs->condition,stack,set,arena);
            scope_push_seperation(stack,"if statement",arena);
            ifs->then_block = propogate_scope(ifs->then_block,stack,set,arena);
            scope_pop_until(stack,NULL,NULL);
            scope_push_seperation(stack,"else statement",arena);
            ifs->else_block = propogate_scope(ifs->else_block,stack,set,arena);
            scope_pop_until(stack,NULL,NULL);
            return node;
        }

        case AST_LOOP : {
            AST_Loop* loop = node->data;
            loop->expr = propogate_scope(loop->expr,stack,set,arena);
            scope_push_seperation(stack,"while loop",arena);
            loop->block = propogate_scope(loop->block,stack,set,arena);
            scope_pop_until(stack,NULL,NULL);
            return node;
        }

        case AST_FUNCTION : {
            scope_push_seperation(stack,"function",arena);
            AST_Function* fn = (AST_Function*)node->data;
            for(int i = 0;i<(int)fn->param_count;i++){             
                fn->params[i] = propogate_scope(fn->params[i],stack,set,arena);
            }
            fn->block = propogate_scope(fn->block,stack,set,arena);
            scope_pop_until(stack,NULL,NULL);
            return node;
        }

        case AST_MAIN : {
            scope_push_seperation(stack,"main",arena);
            AST_Main* main = (AST_Main*)node->data;
            main->block = propogate_scope(main->block,stack,set,arena);
            scope_pop_until(stack,NULL,NULL);
            return node;
        }

        case AST_BLOCK : {
            AST_Block* block = node->data;
            for (size_t i = 0; i < block->body_count; ++i) {
                block->body[i] = propogate_scope(block->body[i],stack,set,arena);
            }
            return node;
        }

        case AST_IDENTIFIER: {
            AST_Identifier* ident = (AST_Identifier*)node->data;
            if(scope_find(stack,ident->name)){
                return node;
            }else{
                fprintf(stderr,"FILE: %s LINE : %d Cannot find identfier in given scope: `%s`\n",__FILE__,__LINE__,ident->name);
                exit(69);
            }
        }
        
        case AST_BINOP: {
            AST_Binop* binop = (AST_Binop*)node->data;
            binop->lhs = propogate_scope(binop->lhs,stack,set,arena);
            binop->rhs = propogate_scope(binop->rhs,stack,set,arena);
            return node;
        }

        case AST_UNOP: {
            AST_Unop* unop = (AST_Unop*)node->data;
            if(unop->op == BL_INC || unop->op == BL_DEC){
                AST_Identifier* ident = (AST_Identifier*)unop->node->data;
                scope_switch_constant(stack,set,ident->name,arena);
            }
            unop->node = propogate_scope(unop->node,stack,set,arena);
            return node;
        }

        case AST_GROUP: {
            AST_Group* grp = (AST_Group*)node->data;
            grp->expr = propogate_scope(grp->expr,stack,set,arena);
            return node;
        }

        case AST_FUNCTIONCALL: {
            AST_FunctionCall* call = node->data;
            for (int i = 0; i < call->args_count; ++i) {
                call->args[i] = propogate_scope(call->args[i],stack,set,arena);
            }
            return node;
        }

        case AST_SWITCH: {
            AST_Switch* switchnode = node->data;
            switchnode->expr = propogate_scope(switchnode->expr,stack,set,arena);
            scope_push_seperation(stack,"switch statement",arena);
            for(int i = 0;i<(int)switchnode->case_count;i++){
                switchnode->cases[i] = propogate_scope(switchnode->cases[i],stack,set,arena);
            }
            switchnode->default_case = propogate_scope(switchnode->default_case,stack,set,arena);

            scope_pop_until(stack,NULL,NULL);
            return node;
        }

        case AST_CASE:{
            AST_SwitchCase* swc = node->data;
            for(int i = 0;i<(int)swc->body_count;i++){
                swc->body[i] = propogate_scope(swc->body[i],stack,set,arena);
            }
            return node;
        }

        case AST_DEFAULT:{
            AST_SwitchCase* def = node->data;
            for(int i = 0;i<(int)def->body_count;i++){
                def->body[i] = propogate_scope(def->body[i],stack,set,arena);
            }
            return node;
        }

        default:
            return node;
    }
}

AST_Node* fold_constants_from_scope(AST_Node* node, bl_stack* stack, bl_set* non_const_set, bl_arena* arena) {
    if (!node) return NULL;

    switch (node->type) {
        case AST_PROGRAM: {
            scope_push_seperation(stack, "program", arena);
            ASTProgram* prog = node->data;
            for (size_t i = 0; i < prog->count; ++i) {
                prog->statements[i] = fold_constants_from_scope(prog->statements[i], stack, non_const_set, arena);
            }
            scope_pop_until(stack, NULL, NULL);
            return node;
        }

        case AST_PARAM: {
            AST_Param* param = node->data;
            AST_Identifier* ident = (AST_Identifier*)param->ident->data;
            AST_Node* dummy_val = make_int_literal_node(arena, 0);
            scope_push(stack, ident->name, dummy_val, false, arena);
            return node;
        }

        case AST_ASSIGNDECL: {
            AST_Assign* assign = node->data;
            assign->rhs = fold_constants_from_scope(assign->rhs, stack, non_const_set, arena);

            if(assign->lhs->type != AST_UNOP){
                AST_Identifier* ident = (AST_Identifier*)assign->lhs->data;
                scope_push(stack, ident->name, assign->rhs, true, arena);
                return node;
            }else{
                AST_Unop* unop = (AST_Unop*)assign->lhs->data;
                if(!(unop->op == (enum KEYWORD_TYPES)BL_KW_BHAU_PTR || unop->op == (enum KEYWORD_TYPES)BL_KW_BHAU_REF)){
                    while(unop->node->type == AST_UNOP){
                        unop = (AST_Unop*)unop->node->data;
                    }
                    AST_Identifier* ident = unop->node->data;
                    scope_push(stack,ident->name,assign->rhs,true,arena);
                }
                return node;
            }
        }

        case AST_ASSIGN: {
            AST_Assign* assign = node->data;
            assign->rhs = fold_constants_from_scope(assign->rhs, stack, non_const_set, arena);
            if(assign->lhs->type != AST_UNOP){
                AST_Identifier* ident = assign->lhs->data;
                scope_push(stack, ident->name, assign->rhs, false, arena); 
                return node;
            }else{
                AST_Unop* unop = (AST_Unop*)assign->lhs->data;
                if(!(unop->op == (enum KEYWORD_TYPES)BL_KW_BHAU_PTR || unop->op == (enum KEYWORD_TYPES)BL_KW_BHAU_REF)){
                    while(unop->node->type == AST_UNOP){
                        unop = (AST_Unop*)unop->node->data;
                    }
                    AST_Identifier* ident = unop->node->data;
                    scope_update(stack,ident->name,assign->rhs);
                    unop->node = fold_constants_from_scope(unop->node,stack,non_const_set,arena);
                }
                return node;
            }
        }

        case AST_IFELSE: {
            AST_Ifelse* ifs = node->data;
            ifs->condition = fold_constants_from_scope(ifs->condition, stack, non_const_set, arena);

            scope_push_seperation(stack, "if block", arena);
            ifs->then_block = fold_constants_from_scope(ifs->then_block, stack, non_const_set, arena);
            scope_pop_until(stack, NULL, NULL);

            scope_push_seperation(stack, "else block", arena);
            ifs->else_block = fold_constants_from_scope(ifs->else_block, stack, non_const_set, arena);
            scope_pop_until(stack, NULL, NULL);

            return node;
        }

        case AST_LOOP: {
            AST_Loop* loop = node->data;
            loop->expr = fold_constants_from_scope(loop->expr, stack, non_const_set, arena);

            scope_push_seperation(stack, "loop block", arena);
            loop->block = fold_constants_from_scope(loop->block, stack, non_const_set, arena);
            scope_pop_until(stack, NULL, NULL);

            return node;
        }

        case AST_FUNCTION: {
            scope_push_seperation(stack, "function", arena);
            AST_Function* fn = node->data;

            for (int i = 0; i < (int)fn->param_count; ++i) {
                fn->params[i] = fold_constants_from_scope(fn->params[i], stack, non_const_set, arena);
            }

            fn->block = fold_constants_from_scope(fn->block, stack, non_const_set, arena);
            scope_pop_until(stack, NULL, NULL);
            return node;
        }

        case AST_MAIN: {
            scope_push_seperation(stack, "main", arena);
            AST_Main* main = node->data;
            main->block = fold_constants_from_scope(main->block, stack, non_const_set, arena);
            scope_pop_until(stack, NULL, NULL);
            return node;
        }

        case AST_BLOCK: {
            AST_Block* block = node->data;
            for (size_t i = 0; i < block->body_count; ++i) {
                block->body[i] = fold_constants_from_scope(block->body[i], stack, non_const_set, arena);
            }
            return node;
        }

        case AST_IDENTIFIER: {
            AST_Identifier* ident = node->data;

            if (set_contains(non_const_set, ident->name)) {
                return node; 
            }

            AST_Node* found = scope_get_most_recent(stack, ident->name);
            if (found && found->type != AST_IDENTIFIER) {
                return found;  
            }

            return node;
        }

        case AST_BINOP: {
            AST_Binop* bin = node->data;
            bin->lhs = fold_constants_from_scope(bin->lhs, stack, non_const_set, arena);
            bin->rhs = fold_constants_from_scope(bin->rhs, stack, non_const_set, arena);
            return node;
        }

        case AST_UNOP: {
            return node;
        }

        case AST_GROUP: {
            AST_Group* grp = node->data;
            grp->expr = fold_constants_from_scope(grp->expr, stack, non_const_set, arena);
            return grp->expr;
        }

        case AST_RETURN: {
            AST_Return* ret = node->data;
            ret->expr = fold_constants_from_scope(ret->expr, stack, non_const_set, arena);
            return node;
        }

        case AST_FUNCTIONCALL: {
            return node;
        }

        case AST_SWITCH: {
            AST_Switch* sw = node->data;
            sw->expr = fold_constants_from_scope(sw->expr, stack, non_const_set, arena);

            scope_push_seperation(stack, "switch", arena);
            for (int i = 0; i < (int)sw->case_count; ++i) {
                sw->cases[i] = fold_constants_from_scope(sw->cases[i], stack, non_const_set, arena);
            }
            sw->default_case = fold_constants_from_scope(sw->default_case, stack, non_const_set, arena);
            scope_pop_until(stack, NULL, NULL);
            return node;
        }

        case AST_CASE: {
            AST_SwitchCase* sc = node->data;
            for (int i = 0; i < (int)sc->body_count; ++i) {
                sc->body[i] = fold_constants_from_scope(sc->body[i], stack, non_const_set, arena);
            }
            return node;
        }

        default:
            return node;
    }
}

AST_Node* check_function_arity(AST_Node* node, FunctionRegistry* reg,bl_arena* arena) {
    if (!node) return NULL;

    switch (node->type) {
        case AST_PROGRAM: {
            ASTProgram* prog = node->data;
            for (size_t i = 0; i < (size_t)prog->count; ++i) {
                prog->statements[i] = check_function_arity(prog->statements[i], reg,arena);
            }
            return node;
        } 
        

        case AST_FUNCTION: {
            AST_Function* fn = node->data;
            AST_Identifier* name = fn->name->data;
            func_registry_add(reg, name->name, fn->param_count, arena);
            fn->block = check_function_arity(fn->block, reg,arena);
            return node;
        } 

        case AST_EXTERN : {
            AST_Extern* ext = node->data;
            AST_Identifier* ident = ext->ident->data;
            func_registry_add(reg,ident->name,1000,arena);
            return node;
        }

        case AST_MAIN: {
            AST_Main* m = node->data;
            m->block=check_function_arity(m->block, reg,arena);
            return node;
        } 

        case AST_BLOCK: {
            AST_Block* blk = node->data;
            for (size_t i = 0; i < blk->body_count; ++i) {
                blk->body[i]  = check_function_arity(blk->body[i], reg,arena);
            }
            return node;
        } 

        case AST_IFELSE: {
            AST_Ifelse* ifs = node->data;
            ifs->condition = check_function_arity(ifs->condition, reg,arena);
            ifs->then_block = check_function_arity(ifs->then_block, reg,arena);
            ifs->else_block = check_function_arity(ifs->else_block, reg,arena);
            return node;
        } 

        case AST_LOOP: {
            AST_Loop* loop = node->data;
            loop->expr = check_function_arity(loop->expr, reg,arena);
            loop->block = check_function_arity(loop->block, reg,arena);
            return node;
        } 

        case AST_FUNCTIONCALL: {
            AST_FunctionCall* call = node->data;

            if (!call->name || call->name->type != AST_IDENTIFIER) {
                fprintf(stderr, "Invalid function call: name is not an identifier.\n");
                exit(99);
            }

            if (!call->name) {
                fprintf(stderr, "Function call with missing name\n");
                exit(88);
            }

            AST_Identifier* name = call->name->data;
            int expected = func_registry_get(reg, name->name);
            if (expected == -1) {
                fprintf(stderr, "Function `%s` not declared.\n", name->name);
                exit(1);
            }
            if(expected < 999){
                if (expected != call->args_count) {
                    fprintf(stderr, "Function `%s` expects %d args but got %d.\n",
                            name->name, expected, call->args_count);
                    exit(2);
                }
                if (call->args_count > 0 && call->args == NULL) {
                    fprintf(stderr, "Function `%s` has %d args but call->args is NULL\n", name->name, call->args_count);
                    exit(87);
                }
            }
            for (int i = 0; i < call->args_count; ++i) {
                call->args[i] = check_function_arity(call->args[i], reg, arena);
            }
            return node;
        }

        case AST_RETURN: {
            AST_Return* ret = node->data;
            ret->expr = check_function_arity(ret->expr, reg,arena);
            return node;
        } 

        case AST_ASSIGN:
        case AST_ASSIGNDECL: {
            AST_Assign* asg = node->data;
            asg->rhs = check_function_arity(asg->rhs, reg,arena);
            return node;
        } 

        case AST_BINOP: {
            AST_Binop* bin = node->data;
            bin ->lhs = check_function_arity(bin->lhs, reg,arena);
            bin-> rhs = check_function_arity(bin->rhs, reg,arena);
            return node;
        } 

        case AST_UNOP: {
            AST_Unop* uop = node->data;
            uop->node = check_function_arity(uop->node, reg,arena);
            return node;
        } 

        case AST_GROUP: {
            AST_Group* grp = node->data;
            grp->expr = check_function_arity(grp->expr, reg,arena);
            return node;
        } 

        case AST_SWITCH: {
            AST_Switch* sw = node->data;
            sw->expr = check_function_arity(sw->expr, reg,arena);
            for (int i = 0; i < (int)sw->case_count; ++i) {
                sw->cases[i] = check_function_arity(sw->cases[i], reg,arena);
            }
            sw->default_case = check_function_arity(sw->default_case, reg,arena);
            return node;
        } 

        case AST_CASE: {
            AST_SwitchCase* cs = node->data;
            for (int i = 0; i < (int)cs->body_count; ++i) {
                cs->body[i] = check_function_arity(cs->body[i], reg,arena);
            }
            return node;
        } 

        default: {
            return node;
        };
    }
}