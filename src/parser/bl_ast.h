#ifndef BL_AST_H
#define BL_AST_H

#include <stdio.h>
#include <string.h>
#include "bl_lexer.h"


#define C_RESET   "\033[0m"
#define C_NODE    "\033[1;36m"
#define C_LABEL   "\033[0;33m"
#define C_VALUE   "\033[0;32m"

#define PRINT_MONOCHROME

int ast_id_counter = 0;

typedef enum {
    SCOPE_GLOBAL,
    SCOPE_FUNCTION,
    SCOPE_MAIN,
    SCOPE_IF,
    SCOPE_SWITCH,
    SCOPE_WHILE,
    SCOPE_BLOCK,
} ScopeType;


typedef struct Scope Scope;

typedef struct Scope {
    int id;
    char* scope_name;
    ScopeType type;
    Scope* scope_parent;
} Scope;

typedef enum {
    AST_PROGRAM, 
    AST_ASSIGN, 
    AST_ASSIGNDECL,
    AST_INTLITERAL,
    AST_BOOLLITERAL,
    AST_IDENTIFIER,
    AST_FLOATLITERAL,
    AST_CHARLITERAL,
    AST_STRINGLITERAL,
    AST_EXTERN,
    AST_BINOP,
    AST_UNOP, 
    AST_GROUP, 
    AST_FUNCTION,
    AST_MAIN, 
    AST_FUNCTIONCALL, 
    AST_IFELSE,
    AST_BLOCK,
    AST_SWITCH,
    AST_CASE,
    AST_BREAK,
    AST_CONTINUE,
    AST_DEFAULT,
    AST_LOOP, 
    AST_RETURN, 
    AST_COMMENT,
    AST_MULCOMMENT,
    AST_PARAM,
} ASTNodeType;

typedef struct {
    ASTNodeType type;
    void* data;
} AST_Node;

typedef struct {
    ASTNodeType type;
    AST_Node* ident;
    char* func_name;
} AST_Param;

typedef struct {
    AST_Node* expr;
    AST_Node* block;
    ASTNodeType type;
} AST_Loop;

typedef struct {
    AST_Node* expr;            
    AST_Node** cases;         
    size_t case_count;
    AST_Node* default_case;   
    ASTNodeType type;
} AST_Switch;

typedef struct {
    AST_Node* value;           
    AST_Node** body;           
    size_t body_count;
    ASTNodeType type;
} AST_SwitchCase;

typedef struct{
    AST_Node* condition;
    AST_Node* then_block;
    AST_Node* else_block;
    ASTNodeType type;
} AST_Ifelse;

typedef struct {
    AST_Node** body;
    size_t body_count;
    ASTNodeType type;
} AST_Block;

typedef struct {
    AST_Node* expr;
    ASTNodeType type;
} AST_Return;


typedef struct {
    AST_Node* name;
    AST_Node** params;
    AST_Node* block;
    size_t param_count;
    ASTNodeType type;
} AST_Function;

typedef struct {
    AST_Node* block;
    ASTNodeType type;
} AST_Main;

typedef struct {
    AST_Node* lhs;
    AST_Node* rhs;
    enum KEYWORD_TYPES op;
    ASTNodeType type;
} AST_Binop;

typedef struct {
    AST_Node* node;
    enum KEYWORD_TYPES op;
    ASTNodeType type;
} AST_Unop;

typedef struct {
    AST_Node* expr;
} AST_Group;

typedef struct {
    AST_Node** statements;
    size_t count;
    ASTNodeType type;
} ASTProgram;

typedef struct {
    AST_Node* ident;
    AST_Node* pseudoname;
    ASTNodeType type;
} AST_Extern;

typedef struct {
    AST_Node** args;
    int args_count;
    ASTNodeType type;
    AST_Node* name;

} AST_FunctionCall;


typedef struct {
    AST_Node* lhs;
    AST_Node* rhs;
    enum KEYWORD_TYPES op;
    ASTNodeType type;
} AST_Assign;


typedef struct {
    int value;
    ASTNodeType type;
} AST_IntLiteral;

typedef struct {
    bool value;
    ASTNodeType type;
} AST_BoolLiteral;

typedef struct {
    float value;
    ASTNodeType type;
} AST_FloatLiteral;

typedef struct {
    char* value;
    ASTNodeType type;
} AST_StringLiteral;

typedef struct {
    char value;
    ASTNodeType type;
} AST_CharLiteral;

typedef struct {
    char* name;
    Scope* scope_val;
    ASTNodeType type;
} AST_Identifier;

typedef struct{
    char* name;
    char* pseudoname;
} extern_pseudoname;



void print_ast_node_summary(AST_Node* node) {
    if (!node) {
        printf("NULL NODE\n");
        return;
    }

    switch (node->type) {
        case AST_IDENTIFIER: {
            AST_Identifier* id = (AST_Identifier*)node->data;
            printf("IDENTIFIER(%s)\n", id->name);
            break;
        }
        case AST_INTLITERAL: {
            AST_IntLiteral* lit = (AST_IntLiteral*)node->data;
            printf("INT(%d)\n", lit->value);
            break;
        }
        case AST_FLOATLITERAL: {
            AST_FloatLiteral* flt = (AST_FloatLiteral*)node->data;
            printf("FLOAT(%.2f)\n", flt->value);
            break;
        }
        case AST_CHARLITERAL: {
            AST_CharLiteral* ch = (AST_CharLiteral*)node->data;
            printf("CHAR('%c')\n", ch->value);
            break;
        }
        case AST_STRINGLITERAL: {
            AST_StringLiteral* str = (AST_StringLiteral*)node->data;
            printf("STRING(\"%s\")\n", str->value);
            break;
        }
        case AST_BOOLLITERAL: {
            AST_BoolLiteral* b = (AST_BoolLiteral*)node->data;
            printf("BOOL(%s)\n", b->value ? "true" : "false");
            break;
        }
        case AST_BINOP: {
            AST_Binop* bop = (AST_Binop*)node->data;
            printf("BINOP(%s)\n", keyword_enum_to_str(bop->op));
            break;
        }
        case AST_UNOP: {
            AST_Unop* uop = (AST_Unop*)node->data;
            printf("UNOP(%s)\n", keyword_enum_to_str(uop->op));
            break;
        }
        case AST_ASSIGN: {
            printf("ASSIGN NODE\n");
            break;
        }
        case AST_FUNCTION: {
            AST_Function* f = (AST_Function*)node->data;
            AST_Identifier* fid = (AST_Identifier*)f->name->data;
            printf("FUNCTION(%s)\n", fid->name);
            break;
        }

        case AST_PARAM: {
            AST_Param* param = (AST_Param*)node->data;
            printf("PARAM: %s\n",param->func_name);
            break;
        }
        case AST_MAIN:
            printf("MAIN FUNCTION\n");
            break;
        case AST_FUNCTIONCALL: {
            AST_FunctionCall* f = (AST_FunctionCall*)node->data;
            AST_Identifier* id = (AST_Identifier*)f->name->data;
            printf("FUNC_CALL(%s)\n", id->name);
            break;
        }
        case AST_IFELSE:
            printf("IF_ELSE NODE\n");
            break;
        case AST_BLOCK:
            printf("BLOCK NODE\n");
            break;
        case AST_LOOP:
            printf("LOOP NODE\n");
            break;
        case AST_SWITCH:
            printf("SWITCH NODE\n");
            break;
        case AST_CASE:
            printf("CASE NODE\n");
            break;
        case AST_DEFAULT:
            printf("DEFAULT CASE NODE\n");
            break;
        case AST_BREAK:
            printf("BREAK\n");
            break;
        case AST_CONTINUE:
            printf("CONTINUE\n");
            break;
        case AST_RETURN:
            printf("RETURN NODE\n");
            break;
        case AST_GROUP:
            printf("GROUP (Parenthesized expression)\n");
            break;
        case AST_EXTERN:
            printf("EXTERN NODE\n");
            break;
        case AST_COMMENT:
            printf("// COMMENT\n");
            break;
        case AST_MULCOMMENT:
            printf("/* MULTILINE COMMENT */\n");
            break;
        case AST_PROGRAM:
            printf("PROGRAM ROOT\n");
            break;
        default:
            printf("UNKNOWN NODE TYPE (%d)\n", node->type);
            break;
    }
}

void dump_astnode_raw(AST_Node* node) {
    if (!node) {
        printf("null\n");
        return;
    }
    printf("NODE Type: %d, \n  Ptr: %p\n", node->type, node);
    printf("  Data: %p\n", node->data);
}


void print_indent(const char* prefix, bool is_last) {
    printf("%s%s", prefix, is_last ? "└── " : "├── ");
}

void print_next_indent(const char* current, char* next, bool is_last) {
    snprintf(next, 128, "%s%s", current, is_last ? "    " : "│   ");
}

void print_ast_tree(AST_Node* node, const char* prefix, bool is_last) {
    if (!node) {
        print_indent(prefix, is_last);
        printf("(null node)\n");
        return;
    }
    print_indent(prefix, is_last);

    char next_prefix[128];
    print_next_indent(prefix, next_prefix, is_last);

    switch (node->type) {
        case AST_PROGRAM: {
            #ifdef PRINT_IN_COLOR
            printf(C_NODE "PROGRAM" C_RESET "\n");
            #endif
            
            #ifdef PRINT_MONOCHROME
            printf("PROGRAM\n");
            #endif

            ASTProgram* prog = (ASTProgram*)node->data;
            for (size_t i = 0; i < prog->count; ++i) {
                print_ast_tree(prog->statements[i], next_prefix, i == prog->count - 1);
            }
            break;
        }

        case AST_PARAM: {
            AST_Param* param = (AST_Param*)node->data;
            #ifdef PRINT_IN_COLOR
            printf(C_NODE "PARAM: %s" C_RESET "\n",param->func_name);
            #endif

            #ifdef PRINT_MONOCHROME
            printf("PARAM: %s\n",param->func_name);
            #endif

            print_ast_tree(param->ident,next_prefix,true);
            break;
        }

        case AST_FUNCTION: {
            AST_Function* func = (AST_Function*)node->data;
            AST_Identifier* func_id = (AST_Identifier*)func->name->data;
            #ifdef PRINT_IN_COLOR
            printf(C_NODE "FUNCTION: %s" C_RESET "\n", func_id->name);
            #endif

            #ifdef PRINT_MONOCHROME
            printf("FUNCTION: %s\n",func_id->name);
            #endif

            print_indent(next_prefix, false); printf("PARAMS\n");
            for (size_t i = 0; i < func->param_count; ++i) {
                print_ast_tree(func->params[i], next_prefix, i == func->param_count - 1);
            }
            print_indent(next_prefix, true); printf("BLOCK\n");
            print_ast_tree(func->block, next_prefix, true);
            break;
        }

        case AST_MAIN: {
            #ifdef PRINT_IN_COLOR
            printf(C_NODE "MAIN FUNCTION" C_RESET "\n");
            #endif

            #ifdef PRINT_MONOCHROME
            printf("MAIN FUNCTION\n");
            #endif

            AST_Main* main_func = (AST_Main*)node->data;
            print_ast_tree(main_func->block, next_prefix, true);
            break;
        }

        case AST_LOOP: {
            #ifdef PRINT_IN_COLOR
            printf(C_NODE "WHILE" C_RESET "\n");
            #endif

            #ifdef PRINT_MONOCHROME
            printf("WHILE\n");
            #endif

            AST_Loop* loop = (AST_Loop*)node->data;
            print_indent(next_prefix, false); printf("EXPR\n");
            print_ast_tree(loop->expr, next_prefix, false);
            print_indent(next_prefix, true); printf("BLOCK\n");
            print_ast_tree(loop->block, next_prefix, true);
            break;
        }

        case AST_SWITCH: {
            #ifdef PRINT_IN_COLOR
            printf(C_NODE "SWITCH" C_RESET "\n");
            #endif

            #ifdef PRINT_MONOCHROME
            printf("SWITCH\n");
            #endif

            AST_Switch* sw = (AST_Switch*)node->data;
            print_indent(next_prefix, false); printf("EXPR\n");
            print_ast_tree(sw->expr, next_prefix, false);
            print_indent(next_prefix, false); printf("CASES\n");
            for (size_t i = 0; i < sw->case_count; ++i) {
                print_ast_tree(sw->cases[i], next_prefix, i == sw->case_count - 1);
            }
            print_indent(next_prefix, true); printf("DEFAULT\n");
            print_ast_tree(sw->default_case, next_prefix, true);
            break;
        }

        case AST_CASE: {
            AST_SwitchCase* _case = (AST_SwitchCase*)node->data;
            #ifdef PRINT_IN_COLOR
            printf(C_NODE "CASE" C_RESET "\n");
            #endif

            #ifdef PRINT_MONOCHROME
            printf("CASE\n");
            #endif

            print_indent(next_prefix, false); printf("VALUE\n");
            print_ast_tree(_case->value, next_prefix, false);
            for (int i = 0; i < (int)_case->body_count; ++i) {
                print_ast_tree(_case->body[i], next_prefix, i == (int)_case->body_count - 1);
            }
            break;
        }

        case AST_DEFAULT: {
            AST_SwitchCase* def = (AST_SwitchCase*)node->data;
            #ifdef PRINT_IN_COLOR
            printf(C_NODE "DEFAULT" C_RESET "\n");
            #endif

            #ifdef PRINT_MONOCHROME
            printf("DEFAULT\n");
            #endif

            for (int i = 0; i < (int)def->body_count; ++i) {
                print_ast_tree(def->body[i], next_prefix, i == (int)def->body_count - 1);
            }
            break;
        }

        case AST_IFELSE: {
            #ifdef PRINT_IN_COLOR
            printf(C_NODE "IF_ELSE" C_RESET "\n");
            #endif

            #ifdef PRINT_MONOCHROME
            printf("IF_ELSE\n");
            #endif

            AST_Ifelse* ifs = (AST_Ifelse*)node->data;
            print_indent(next_prefix, false); printf("CONDITION\n");
            print_ast_tree(ifs->condition, next_prefix, false);
            print_indent(next_prefix, false); printf("IF BLOCK\n");
            print_ast_tree(ifs->then_block, next_prefix, false);
            print_indent(next_prefix, true); printf("ELSE BLOCK\n");
            print_ast_tree(ifs->else_block, next_prefix, true);
            break;
        }

        case AST_RETURN: {
            #ifdef PRINT_IN_COLOR
            printf(C_NODE "RETURN" C_RESET "\n");
            #endif

            #ifdef PRINT_MONOCHROME
            printf("RETURN\n");
            #endif

            AST_Return* ret = (AST_Return*)node->data;
            print_ast_tree(ret->expr, next_prefix, true);
            break;
        }

        case AST_ASSIGN: {
            AST_Assign* asg = (AST_Assign*)node->data;
            #ifdef PRINT_IN_COLOR
            printf(C_NODE "ASSIGN %s" C_RESET "\n",keyword_enum_to_str(asg->op));
            #endif

            #ifdef PRINT_MONOCHROME
            printf("ASSIGN %s\n",keyword_enum_to_str(asg->op));
            #endif

            print_ast_tree(asg->lhs, next_prefix, false);
            print_ast_tree(asg->rhs, next_prefix, true);
            break;
        }
        case AST_ASSIGNDECL: {
            AST_Assign* asg = (AST_Assign*)node->data;
            #ifdef PRINT_IN_COLOR
            printf(C_NODE "ASSIGN DECL %s" C_RESET "\n",keyword_enum_to_str(asg->op));
            #endif

            #ifdef PRINT_MONOCHROME
            printf("ASSIGN DECL %s\n",keyword_enum_to_str(asg->op));
            #endif

            print_ast_tree(asg->lhs,next_prefix,false);
            print_ast_tree(asg->rhs,next_prefix,true);
            break;
        }

        case AST_FUNCTIONCALL: {
            AST_FunctionCall* call = (AST_FunctionCall*)node->data;
            AST_Identifier* name = (AST_Identifier*)call->name->data;
            #ifdef PRINT_IN_COLOR
            printf(C_NODE "FUNCTION CALL: %s" C_RESET "\n", name->name);
            #endif

            #ifdef PRINT_MONOCHROME
            printf("FUNCTION CALL: %s\n",name->name);
            #endif

            for (size_t i = 0; i < (size_t)call->args_count; ++i) {
                print_ast_tree(call->args[i], next_prefix, i == (size_t)call->args_count - 1);
            }
            break;
        }

        case AST_BLOCK: {
            #ifdef PRINT_IN_COLOR
            printf(C_NODE "BLOCK" C_RESET "\n");
            #endif

            #ifdef PRINT_MONOCHROME
            printf("BLOCK\n");
            #endif

            AST_Block* blk = (AST_Block*)node->data;
            for (size_t i = 0; i < blk->body_count; ++i) {
                print_ast_tree(blk->body[i], next_prefix, i == blk->body_count - 1);
            }
            break;
        }

        case AST_IDENTIFIER: {
            AST_Identifier* id = (AST_Identifier*)node->data;
            #ifdef PRINT_IN_COLOR
            printf(C_LABEL "IDENTIFIER: %s" C_RESET " [" C_VALUE "%s#%d" C_RESET "]\n",
                   id->name ? id->name : "(null)",
                   id->scope_val ? id->scope_val->scope_name : "(null)",
                   id->scope_val ? id->scope_val->id : -1);
            #endif

            #ifdef PRINT_MONOCHROME
            printf("IDENTIFIER: %s [%s#%d]\n",id->name ? id->name : "(null)",id->scope_val ? id->scope_val->scope_name : "(null)",id->scope_val ? id->scope_val->id : -1);
            #endif

            break;
        }

        case AST_INTLITERAL: {
            AST_IntLiteral* ilit = (AST_IntLiteral*)node->data;
            #ifdef PRINT_IN_COLOR
            printf(C_LABEL "INT_LITERAL: " C_VALUE "%d" C_RESET "\n", ilit->value);
            #endif

            #ifdef PRINT_MONOCHROME
            printf("INT_LITERAL: %d\n",ilit->value);
            #endif

            break;
        }

        case AST_FLOATLITERAL: {
            AST_FloatLiteral* flit = (AST_FloatLiteral*)node->data;
            #ifdef PRINT_IN_COLOR
            printf(C_LABEL "FLOAT_LITERAL: " C_VALUE "%.2f" C_RESET "\n",flit->value);
            #endif

            #ifdef PRINT_MONOCHROME
            printf("FLOAT_LITERAL: %.2f\n",flit->value);
            #endif

            break;
        }

        case AST_CHARLITERAL: {
            AST_CharLiteral* clit = (AST_CharLiteral*)node->data;
            #ifdef PRINT_IN_COLOR
            printf(C_LABEL "CHAR_LITERAL: " C_VALUE "%c" C_RESET "\n",clit->value);
            #endif

            #ifdef PRINT_MONOCHROME
            printf("CHAR_LITERAL: %c\n",clit->value);
            #endif

            break;
        }

        case AST_BOOLLITERAL: {
            AST_BoolLiteral* blit = (AST_BoolLiteral*)node->data;
            #ifdef PRINT_IN_COLOR
            printf(C_LABEL "BOOL LITERAL: " C_VALUE "%s" C_RESET "\n",blit->value == true ? "true" : "false");
            #endif

            #ifdef PRINT_MONOCHROME
            printf("BOOL_LITERAL: %s\n",blit->value == true ? "true" : "false");
            #endif

            break;
        }

        case AST_STRINGLITERAL: {
            AST_StringLiteral* slit = (AST_StringLiteral*)node->data;
            #ifdef PRINT_IN_COLOR
            printf(C_LABEL "STRING_LITERAL: \"%s\"" C_RESET "\n", slit->value);
            #endif

            #ifdef PRINT_MONOCHROME
            printf("STRING_LITERAL: \"%s\"\n",slit->value);
            #endif

            break;
        }

        case AST_BINOP: {
            AST_Binop* bop = (AST_Binop*)node->data;
            #ifdef PRINT_IN_COLOR
            printf(C_LABEL "BINOP: " C_VALUE "%s" C_RESET "\n", keyword_enum_to_str(bop->op));
            #endif

            #ifdef PRINT_MONOCHROME
            printf("BINOP: %s\n",keyword_enum_to_str(bop->op));
            #endif

            print_ast_tree(bop->lhs, next_prefix, false);
            print_ast_tree(bop->rhs, next_prefix, true);
            break;
        }

        case AST_UNOP: {
            AST_Unop* uop = (AST_Unop*)node->data;
            #ifdef PRINT_IN_COLOR
            printf(C_LABEL "UNARYOP: " C_VALUE "%s" C_RESET "\n", keyword_enum_to_str(uop->op));
            #endif

            #ifdef PRINT_MONOCHROME
            printf("UNARYOP : %s\n",keyword_enum_to_str(uop->op));
            #endif

            print_ast_tree(uop->node, next_prefix, true);
            break;
        }

        case AST_EXTERN: {
            #ifdef PRINT_IN_COLOR
            printf(C_NODE "EXTERN" C_RESET "\n");
            #endif

            #ifdef PRINT_MONOCHROME
            printf("EXTERN\n");
            #endif

            AST_Extern* ext = (AST_Extern*)node->data;
            print_ast_tree(ext->ident, next_prefix, true);
            break;
        }

        case AST_BREAK: {
            #ifdef PRINT_IN_COLOR
            printf(C_NODE "BREAK" C_RESET "\n");
            #endif

            #ifdef PRINT_MONOCHROME
            printf("BREAK\n");
            #endif

            break;
        }

        case AST_COMMENT: {
            #ifdef PRINT_IN_COLOR
            printf(C_LABEL "// COMMENT" C_RESET "\n");
            #endif
            
            #ifdef PRINT_MONOCHROME
            printf("// COMMENT\n");
            #endif

            break;
        }

        case AST_GROUP: {
            #ifdef PRINT_IN_COLOR
            printf(C_NODE "GROUP" C_RESET "\n");
            #endif

            #ifdef PRINT_MONOCHROME
            printf("GROUP\n");
            #endif

            AST_Group* group = (AST_Group*)node->data;
            print_ast_tree(group->expr, next_prefix, true);
            break;
        }

        default: {
            printf("UNKNOWN NODE TYPE (%d), (%p)\n", node->type,node->data);
            break;
        }
    }
}


//REF Produces an image of AST using graphviz, you can install it using `sudo apt install graphviz`, than execute the command `dot -Tpng example.dot -o ast.png`


void print_ast_dot_node(FILE* out, AST_Node* node, int parent_id) {
    if (!node) return;

    int current_id = ast_id_counter++;

    switch (node->type) {
        case AST_PROGRAM: {
            fprintf(out, "  node%d [label=\"PROGRAM\"]\n", current_id);
            ASTProgram* prog = (ASTProgram*)node->data;
            for (size_t i = 0; i < prog->count; ++i)
                print_ast_dot_node(out, prog->statements[i], current_id);
            break;
        }
        case AST_PARAM : {
            AST_Param* param = (AST_Param*)node->data;
            AST_Identifier* param_id = (AST_Identifier*)param->ident->data;
            fprintf(out, "  node%d [label=\"IDENT: %s\"]\n", current_id, param_id->name);
            break;
        }
        case AST_FUNCTION: {
            AST_Function* func = (AST_Function*)node->data;
            AST_Identifier* fid = (AST_Identifier*)func->name->data;
            fprintf(out, "  node%d [label=\"FUNCTION: %s\"]\n", current_id, fid->name);
            for (size_t i = 0; i < func->param_count; ++i)
                print_ast_dot_node(out, func->params[i], current_id);
            print_ast_dot_node(out, func->block, current_id);
            break;
        }
        case AST_MAIN: {
            fprintf(out, "  node%d [label=\"MAIN\"]\n", current_id);
            AST_Main* main = (AST_Main*)node->data;
            print_ast_dot_node(out, main->block, current_id);
            break;
        }
        case AST_LOOP: {
            fprintf(out, "  node%d [label=\"WHILE\"]\n", current_id);
            AST_Loop* loop = (AST_Loop*)node->data;
            print_ast_dot_node(out, loop->expr, current_id);
            print_ast_dot_node(out, loop->block, current_id);
            break;
        }
        case AST_SWITCH: {
            fprintf(out, "  node%d [label=\"SWITCH\"]\n", current_id);
            AST_Switch* sw = (AST_Switch*)node->data;
            print_ast_dot_node(out, sw->expr, current_id);
            for (size_t i = 0; i < sw->case_count; ++i)
                print_ast_dot_node(out, sw->cases[i], current_id);
            print_ast_dot_node(out, sw->default_case, current_id);
            break;
        }
        case AST_CASE:
        case AST_DEFAULT: {
            const char* label = node->type == AST_CASE ? "CASE" : "DEFAULT";
            fprintf(out, "  node%d [label=\"%s\"]\n", current_id, label);
            AST_SwitchCase* cs = (AST_SwitchCase*)node->data;
            if (node->type == AST_CASE)
                print_ast_dot_node(out, cs->value, current_id);
            for (int i = 0; i < (int)cs->body_count; ++i)
                print_ast_dot_node(out, cs->body[i], current_id);
            break;
        }
        case AST_IFELSE: {
            fprintf(out, "  node%d [label=\"IF_ELSE\"]\n", current_id);
            AST_Ifelse* ie = (AST_Ifelse*)node->data;
            print_ast_dot_node(out, ie->condition, current_id);
            print_ast_dot_node(out, ie->then_block, current_id);
            print_ast_dot_node(out, ie->else_block, current_id);
            break;
        }
        case AST_RETURN: {
            fprintf(out, "  node%d [label=\"RETURN\"]\n", current_id);
            AST_Return* ret = (AST_Return*)node->data;
            print_ast_dot_node(out, ret->expr, current_id);
            break;
        }

        case AST_ASSIGNDECL : {
            AST_Assign* asg = (AST_Assign*)node->data;
            fprintf(out, "  node%d [label=\"ASSIGN: %s\"]\n", current_id, keyword_enum_to_str(asg->op));
            print_ast_dot_node(out, asg->lhs, current_id);
            print_ast_dot_node(out, asg->rhs, current_id);
            break;
        }
        case AST_ASSIGN: {
            AST_Assign* asg = (AST_Assign*)node->data;
            fprintf(out, "  node%d [label=\"ASSIGN: %s\"]\n", current_id, keyword_enum_to_str(asg->op));
            print_ast_dot_node(out, asg->lhs, current_id);
            print_ast_dot_node(out, asg->rhs, current_id);
            break;
        }
        case AST_BINOP: {
            AST_Binop* bop = (AST_Binop*)node->data;
            fprintf(out, "  node%d [label=\"BINOP: %s\"]\n", current_id, keyword_enum_to_str(bop->op));
            print_ast_dot_node(out, bop->lhs, current_id);
            print_ast_dot_node(out, bop->rhs, current_id);
            break;
        }
        case AST_UNOP: {
            AST_Unop* uop = (AST_Unop*)node->data;
            fprintf(out, "  node%d [label=\"UNOP: %s\"]\n", current_id, keyword_enum_to_str(uop->op));
            print_ast_dot_node(out, uop->node, current_id);
            break;
        }
        case AST_FUNCTIONCALL: {
            AST_FunctionCall* call = (AST_FunctionCall*)node->data;
            AST_Identifier* id = (AST_Identifier*)call->name->data;
            fprintf(out, "  node%d [label=\"CALL: %s\"]\n", current_id, id->name);
            for (size_t i = 0; i < (size_t)call->args_count; ++i)
                print_ast_dot_node(out, call->args[i], current_id);
            break;
        }
        case AST_BLOCK: {
            fprintf(out, "  node%d [label=\"BLOCK\"]\n", current_id);
            AST_Block* blk = (AST_Block*)node->data;
            for (size_t i = 0; i < blk->body_count; ++i)
                print_ast_dot_node(out, blk->body[i], current_id);
            break;
        }
        case AST_IDENTIFIER: {
            AST_Identifier* id = (AST_Identifier*)node->data;
            fprintf(out, "  node%d [label=\"IDENT: %s\"]\n", current_id, id->name);
            break;
        }
        case AST_INTLITERAL: {
            AST_IntLiteral* ilit = (AST_IntLiteral*)node->data;
            fprintf(out, "  node%d [label=\"INT: %d\"]\n", current_id, ilit->value);
            break;
        }
        case AST_STRINGLITERAL: {
            AST_StringLiteral* slit = (AST_StringLiteral*)node->data;
            fprintf(out, "  node%d [label=\"STRING: %s\"]\n", current_id, slit->value);
            break;
        }
        case AST_FLOATLITERAL: {
            AST_FloatLiteral* flit = (AST_FloatLiteral*)node->data;
            fprintf(out, "  node%d [label=\"FLOAT: %.2f\"]\n", current_id, flit->value);
            break;
        }
        case AST_EXTERN: {
            fprintf(out, "  node%d [label=\"EXTERN\"]\n", current_id);
            AST_Extern* ext = (AST_Extern*)node->data;
            print_ast_dot_node(out, ext->ident, current_id);
            break;
        }
        case AST_BREAK: {
            fprintf(out, "  node%d [label=\"BREAK\"]\n", current_id);
            break;
        }
        case AST_COMMENT: {
            fprintf(out, "  node%d [label=\"// COMMENT\"]\n", current_id);
            break;
        }
        case AST_GROUP: {
            fprintf(out, "  node%d [label=\"GROUP\"]\n", current_id);
            AST_Group* group = (AST_Group*)node->data;
            print_ast_dot_node(out, group->expr, current_id);
            break;
        }
        default: {
            fprintf(out, "  node%d [label=\"UNKNOWN\"]\n", current_id);
            break;
        }
    }

    if (parent_id != -1) {
        fprintf(out, "  node%d -> node%d;\n", parent_id, current_id);
    }
}

void generate_ast_dot(AST_Node* root, const char* filename) {
    FILE* out = fopen(filename, "w");
    if (!out) {
        perror("Could not open output DOT file");
        return;
    }
    fprintf(out, "digraph AST {\n  node [shape=box, style=filled, fillcolor=lightblue];\n");
    ast_id_counter = 0;
    print_ast_dot_node(out, root, -1);
    fprintf(out, "}\n");
    fclose(out);
}


#endif