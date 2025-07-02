#include "bl_parser.h"

//TODO implement constant propagation
typedef enum {
    CONSTKIND_NONE,
    CONSTKIND_INT,
    CONSTKIND_FLOAT,
    CONSTKIND_BOOL,
    CONSTKIND_CHAR,
    CONSTKIND_STRING,
} ConstKind;

//TODO assign NULL to declared but not assigned identifiers
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


ConstKind promote_kind(ConstKind a, ConstKind b);
ConstKind get_const_value(AST_Node* node, ConstValue* out);

bool is_constant(AST_Node* node);
bool is_terminating_node(AST_Node* node);
int eval_binop_int(enum KEYWORD_TYPES op, int lhs, int rhs);
void promote_values(ConstValue* lhs, ConstValue* rhs, ConstKind target);
void optimize_block(AST_Block* block, bl_arena* arena) ;
size_t count_assignment_chain(AST_Node* node);

AST_Node* fold_constants(AST_Binop* bin, bl_arena* arena);
AST_Node* make_int_literal_node(bl_arena* arena, int value);
AST_Node* make_bool_literal_node(bl_arena* arena, int value);
AST_Node* make_float_literal_node(bl_arena* arena, float value);
AST_Node* optimize_ast(AST_Node* node,bl_arena* arena);
AST_Node* flatten_blocks(AST_Node* node, bl_arena* arena);
AST_Block* flatten_block(AST_Block* block, bl_arena* arena);
AST_Node* flatten_assignment_chain(AST_Node* assign, bl_arena* arena);
AST_NodeList flatten_comma_chain(AST_Node* node, bl_arena* arena);




int main(){
    bl_arena* arena = (bl_arena*)malloc(sizeof(bl_arena));
    arena_init(arena);

    AST_Node* ast = bhaulang_parser("src/parser/one.bl",arena);
    print_ast_tree(ast,0,"");
    AST_Node* optimized_ast = optimize_ast(ast,arena);
    AST_Node* flattened_ast =  flatten_blocks(optimized_ast,arena);
    print_ast_tree(flattened_ast,0,"");


    return 0;
}

AST_Block* flatten_block(AST_Block* block, bl_arena* arena) {
    if (!block) return NULL;

    AST_Node** new_body = arena_alloc(arena, sizeof(AST_Node*) * block->body_count * 20);
    size_t new_count = 0;

    for (size_t i = 0; i < block->body_count; ++i) {
        AST_Node* stmt = flatten_blocks(block->body[i], arena); 

        if (stmt && stmt->type == AST_BLOCK) {
            AST_Block* inner = stmt->data;
            for (size_t j = 0; j < inner->body_count; ++j) {
                new_body[new_count++] = inner->body[j];
            }
        } else if (stmt) {
            new_body[new_count++] = stmt;
        }
    }

    block->body = new_body;
    block->body_count = new_count;
    return block;
}

AST_Node* flatten_blocks(AST_Node* node, bl_arena* arena) {
    if (!node) return NULL;

    switch (node->type) {
        case AST_PROGRAM: {
            ASTProgram* prog = node->data;
            for (size_t i = 0; i < prog->count; ++i) {
                prog->statements[i] = flatten_blocks(prog->statements[i], arena);
            }


            AST_Node** new_stmts = arena_alloc(arena, sizeof(AST_Node*) * prog->count * 2);
            size_t new_count = 0;

            for (size_t i = 0; i < prog->count; ++i) {
                AST_Node* stmt = prog->statements[i];
                if (stmt->type == AST_BLOCK) {
                    AST_Block* blk = stmt->data;
                    for (size_t j = 0; j < blk->body_count; ++j) {
                        new_stmts[new_count++] = blk->body[j];
                    }
                } else {
                    new_stmts[new_count++] = stmt;
                }
            }

            prog->statements = new_stmts;
            prog->count = new_count;
            return node;
        }

        case AST_BLOCK: {
            AST_Block* blk = node->data;

            AST_Node** new_body = arena_alloc(arena, sizeof(AST_Node*) * blk->body_count * 2);
            size_t new_count = 0;

            for (size_t i = 0; i < blk->body_count; ++i) {
                AST_Node* stmt = flatten_blocks(blk->body[i], arena);
                if (!stmt) continue;

                if (stmt->type == AST_BLOCK) {
                    AST_Block* inner = stmt->data;
                    for (size_t j = 0; j < inner->body_count; ++j) {
                        new_body[new_count++] = inner->body[j];
                    }
                } else {
                    new_body[new_count++] = stmt;
                }
            }

            blk->body = new_body;
            blk->body_count = new_count;
            return node;
        }

        case AST_IFELSE: {
            AST_Ifelse* ifs = node->data;
            ifs->condition = flatten_blocks(ifs->condition, arena);
            ifs->then_block = flatten_blocks(ifs->then_block, arena);
            ifs->else_block = flatten_blocks(ifs->else_block, arena);
            return node;
        }

        case AST_LOOP: {
            AST_Loop* loop = node->data;
            loop->expr = flatten_blocks(loop->expr, arena);
            loop->block = flatten_blocks(loop->block, arena);
            return node;
        }

        case AST_SWITCH: {
            AST_Switch* sw = node->data;
            sw->expr = flatten_blocks(sw->expr, arena);
            for (size_t i = 0; i < sw->case_count; ++i) {
                sw->cases[i] = flatten_blocks(sw->cases[i], arena);
            }
            sw->default_case = flatten_blocks(sw->default_case, arena);
            return node;
        }

        case AST_CASE:
        case AST_DEFAULT: {
            AST_SwitchCase* sc = node->data;
            for (size_t i = 0; i < sc->body_count; ++i) {
                sc->body[i] = flatten_blocks(sc->body[i], arena);
            }
            return node;
        }

        case AST_FUNCTION:
        case AST_MAIN: {

            AST_Node** body_ptr = (node->type == AST_FUNCTION)
                ? &((AST_Function*)node->data)->block
                : &((AST_Main*)node->data)->block;

            *body_ptr = flatten_blocks(*body_ptr, arena);
            return node;
        }

        default: {

            return node;
        }
    }
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

// int eval_assignment_int(enum KEYWORD_TYPES op, int lhs, int rhs){
//     switch(op){
//         case BL_ADDEQ   : return lhs += rhs;
//         case BL_SUBEQ   : return lhs -= rhs;
//         case BL_MULTEQ  : return lhs *= rhs;
//         case BL_DIVEQ   : return lhs /= rhs;
//         case BL_MODEQ   : return lhs %= rhs;
//         case BL_ANDEQ   : return lhs &= rhs;
//         case BL_OREQ    : return lhs |= rhs;
//         case BL_XOREQ   : return lhs ^= rhs;
//         default: return 0;
//     }
// }

ConstValue eval_unary_expr(enum KEYWORD_TYPES op, ConstValue val) {
    ConstValue result = val;

    switch (val.kind) {
        case CONSTKIND_INT:
        case CONSTKIND_CHAR: {
            int v = (val.kind == CONSTKIND_CHAR) ? val.c : val.i;
            switch (op) {
                case BL_NOT: result.kind = CONSTKIND_INT; result.i = !v; break;
                case BL_SUBBINOP: result.kind = CONSTKIND_INT; result.i = -v; break;
                default: break;
            }
            break;
        }

        case CONSTKIND_FLOAT: {
            switch (op) {
                case BL_NOT: result.kind = CONSTKIND_INT; result.i = !(val.f); break;
                case BL_SUBBINOP: result.kind = CONSTKIND_FLOAT; result.f = -val.f; break;
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
                    AST_Identifier* ident = (AST_Identifier*)idents.items[i]->data;
                    AST_Node* decl_node = arena_alloc(arena, sizeof(AST_Node));
                    decl_node->type = AST_IDENTIFIER;
                    decl_node->data = ident;

                    decls[i] = decl_node;
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
            if (is_constant(ifs->condition)) {
                AST_IntLiteral* lit = ifs->condition->data;
                return lit->value ? ifs->then_block : ifs->else_block;
            }

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
            AST_Function* fn = node->data;
            fn->block = optimize_ast(fn->block, arena);
            if (fn->block && fn->block->type == AST_BLOCK) {
                optimize_block(fn->block->data, arena);
            }

            return node;
        }
        case AST_MAIN: {
            AST_Main* fn = node->data;
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
            //WARN passing ASTProgram* instead of AST_Block* since only x->body & x->body_count are used
            optimize_block(prog, arena);
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