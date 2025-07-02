#include "bl_parser.h"


bool is_constant(AST_Node* node);
int eval_binop_int(enum KEYWORD_TYPES op, int lhs, int rhs);
int eval_unary_int(enum KEYWORD_TYPES op, int value);
AST_Node* make_int_literal_node(bl_arena* arena, int value);

void optimize_block(AST_Block* block, bl_arena* arena) ;
AST_Node* optimize_ast(AST_Node* node,bl_arena* arena);

int main(){
    bl_arena* arena = (bl_arena*)malloc(sizeof(bl_arena));
    arena_init(arena);

    AST_Node* ast = bhaulang_parser("src/parser/one.bl",arena);
    print_ast_tree(ast,0,"");
    AST_Node* optimized_ast = optimize_ast(ast,arena);
    print_ast_tree(optimized_ast,0,"");

    return 0;
}

bool is_constant(AST_Node* node) {
    if(node->type == AST_INTLITERAL){
            return true;
        }
    return false;
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

int eval_unary_int(enum KEYWORD_TYPES op, int value){
    switch(op){
        case BL_NOT : return !value;
        case BL_INC : return ++value;
        case BL_DEC : return --value;
        case BL_SUBBINOP : return -value;
        default: return value;
    }
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

        if (stmt->type == AST_RETURN) {
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
                AST_IntLiteral* l = bin->lhs->data;
                AST_IntLiteral* r = bin->rhs->data;
                int folded = eval_binop_int(bin->op, l->value, r->value);
                return make_int_literal_node(arena, folded);
            }
            return node;
        }

        case AST_UNOP: {
            AST_Unop* uop = node->data;
            uop->node = optimize_ast(uop->node, arena);
            if(is_constant(uop->node)){
                AST_IntLiteral* l = uop->node->data;
                int folded = eval_unary_int(uop->op,l->value);
                return make_int_literal_node(arena,folded);
            }
            return node;
        }

        case AST_ASSIGN: {
            AST_Assign* asg = node->data;
            asg->lhs = optimize_ast(asg->lhs, arena);
            asg->rhs = optimize_ast(asg->rhs, arena);
            return node;
        }

        case AST_IFELSE: {
            AST_Ifelse* ifs = node->data;
            ifs->condition = optimize_ast(ifs->condition, arena);
            ifs->then_block = optimize_ast(ifs->then_block, arena);

            if (ifs->then_block && ifs->then_block->type == AST_BLOCK) {
                optimize_block(ifs->then_block->data, arena);
            }

            ifs->else_block = optimize_ast(ifs->else_block, arena);
            if (ifs->else_block && ifs->else_block->type == AST_BLOCK) {
                optimize_block(ifs->else_block->data, arena);
            }
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
            if (loop->block && loop->block->type == AST_BLOCK) {
                optimize_block(loop->block->data, arena);
            }

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