#include "bl_astOptimizer.h"


#define COLOR_RESET     "\x1b[0m"
#define COLOR_LABEL     "\x1b[1;36m"
#define COLOR_OP        "\x1b[1;33m"
#define COLOR_RESULT    "\x1b[1;32m"
#define COLOR_ARG       "\x1b[1;34m"
#define COLOR_COMMENT   "\x1b[2;37m"


typedef enum {
    TAC_NOP,
    TAC_ASSIGN,     
    TAC_BINOP,   
    TAC_UNOP,       
    TAC_LABEL,
    TAC_GOTO,
    TAC_IFGOTO,     
    TAC_PARAM,
    TAC_CALL,
    TAC_FUNC_BEGIN,  
    TAC_FUNC_END,    
    TAC_MAIN_BEGIN,
    TAC_MAIN_END,
    TAC_RETURN,
    TAC_EXTERN,
} TAC_Op;

typedef struct TACInstr {
    TAC_Op op;
    char* result;
    char* arg1;
    char* arg2;
    char* relop;    
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

TACInstr* tac_create_instr(bl_arena* arena, TAC_Op op, char* result, char* arg1, char* arg2, char* relop, char* label);
void tac_append(TACList* list, TACInstr* instr);
void tac_print(TACList* list);
void tac_debug_print(TACList* list);
void tac_colored_print(TACList* list);
void tac_export_dot(TACList* list, const char* filename);

TACList* generate_tac(AST_Node* ast, bl_arena* arena);
char* gen_tac(AST_Node* node, TACList* prog, bl_arena* arena, LoopContext* loop_ctx);

char* new_temp(bl_arena* arena);
char* new_label(bl_arena* arena);

int main(){
    bl_arena* arena = (bl_arena*)malloc(sizeof(bl_arena));
    arena_init(arena);
    AST_Node* node = bhaulang_optimizer("src/ir/one.bl",arena);


    TACList* list = generate_tac(node,arena);
    tac_print(list);
    return 0;
}

TACInstr* tac_create_instr(bl_arena* arena, TAC_Op op, char* result, char* arg1, char* arg2, char* relop, char* label) {
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

char* new_temp(bl_arena* arena) {
    char buf[32];
    snprintf(buf, sizeof(buf), "t%d", temp_counter++);
    char* tmp = arena_alloc(arena, strlen(buf) + 1);
    strcpy(tmp, buf);
    return tmp;
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

char* gen_tac(AST_Node* node, TACList* prog, bl_arena* arena,LoopContext* loop_ctx) {
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

            char* switch_val = gen_tac(sw->expr, prog, arena,new_ctx);


            char** case_labels = arena_alloc(arena, sizeof(char*) * sw->case_count);
            for (int i = 0; i < (int)sw->case_count; ++i) {
                case_labels[i] = new_label(arena);
            }

            for (int i = 0; i < (int)sw->case_count; ++i) {
                AST_SwitchCase* case_node = sw->cases[i]->data;
                char buf[32];
                ASTNodeType type = case_node->value->type;
                if(type == AST_INTLITERAL){
                    AST_IntLiteral* ilit = ((AST_Node*)case_node->value)->data;
                    snprintf(buf, sizeof(buf), "%d", ilit->value);
                    char* case_val = arena_alloc(arena, strlen(buf) + 1);
                    strcpy(case_val, buf);
                    tac_append(prog, tac_create_instr(arena, TAC_IFGOTO, NULL, switch_val, case_val, "==", case_labels[i]));
                }else if(type == AST_CHARLITERAL){
                    AST_CharLiteral* clit = ((AST_Node*)case_node->value)->data;
                    snprintf(buf, sizeof(buf), "%d", clit->value);
                    char* case_val = arena_alloc(arena, strlen(buf) + 1);
                    strcpy(case_val, buf);
                    tac_append(prog, tac_create_instr(arena, TAC_IFGOTO, NULL, switch_val, case_val, "==", case_labels[i]));
                }else{
                    fprintf(stderr,"Switch cannot be used with floats or strings");
                    exit(1);
                }
            }

            char* def_label = new_label(arena);
            tac_append(prog, tac_create_instr(arena, TAC_GOTO, NULL, NULL, NULL, NULL, def_label));

            for (int i = 0; i < (int)sw->case_count; ++i) {
                tac_append(prog, tac_create_instr(arena, TAC_LABEL, NULL, NULL, NULL, NULL, case_labels[i]));
                gen_tac(sw->cases[i], prog, arena,new_ctx);
            }
            tac_append(prog, tac_create_instr(arena, TAC_LABEL, NULL, NULL, NULL, NULL, def_label));

            if (sw->default_case) {
                gen_tac(sw->default_case, prog, arena,new_ctx);
            }

            tac_append(prog, tac_create_instr(arena, TAC_LABEL, NULL, NULL, NULL, NULL, end_label));
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

        case AST_EXTERN:
            AST_Identifier* ext = (AST_Identifier*)((AST_Node*)((AST_Extern*)node->data)->ident)->data;
            tac_append(prog, tac_create_instr(arena, TAC_EXTERN, ext->name, NULL, NULL, NULL, NULL));
            return NULL;

        case AST_INTLITERAL: {
            AST_IntLiteral* lit = node->data;
            char buf[32];
            snprintf(buf, sizeof(buf), "%d", lit->value);
            char* str = arena_alloc(arena, strlen(buf) + 1);
            strcpy(str, buf);
            return str;
        }
        
        case AST_BOOLLITERAL: {
            AST_BoolLiteral* blit = node->data;
            char buf[32];
            snprintf(buf, sizeof(buf),"%d",blit->value == true? 1 : 0);
            char* str = arena_alloc(arena, strlen(buf) + 1);
            strcpy(str,buf);
            return str;
        }

        case AST_STRINGLITERAL : {
            AST_StringLiteral* slit = node->data;
            char buf[1024];
            snprintf(buf,sizeof(buf),"%s",slit->value);
            char* str = arena_alloc(arena,strlen(buf) + 1);
            strcpy(str,buf);
            return str;
        }

        case AST_CHARLITERAL : {
            AST_CharLiteral* clit = node->data;
            char buf[32];
            snprintf(buf, sizeof(buf), "%c", clit->value);
            char* str = arena_alloc(arena, strlen(buf) + 1);
            strcpy(str,buf);
            return str;
        }

        case AST_FLOATLITERAL : {
            AST_FloatLiteral* flit = node->data;
            char buf[32];
            snprintf(buf,sizeof(buf), "%.16f",flit->value);
            char* str = arena_alloc(arena, strlen(buf) + 1);
            strcpy(str,buf);
            return str;
        }

        case AST_IDENTIFIER: {
            AST_Identifier* ident = node->data;
            return ident->name;
        }

        case AST_BINOP: {
            AST_Binop* bin = node->data;
            char* left = gen_tac(bin->lhs, prog, arena,loop_ctx);
            char* right = gen_tac(bin->rhs, prog, arena,loop_ctx);
            char* result = new_temp(arena);
            tac_append(prog, tac_create_instr(arena, TAC_BINOP, result, left, right, keyword_enum_to_str(bin->op), NULL));
            return result;
        }
        
        case AST_GROUP: {
            AST_Group* grp = node->data;
            return gen_tac(grp->expr, prog, arena, loop_ctx);
        }

        case AST_UNOP: {
            AST_Unop* un = node->data;
            char* arg = gen_tac(un->node, prog, arena,loop_ctx);
            char* result = new_temp(arena);
            tac_append(prog, tac_create_instr(arena, TAC_UNOP, result, arg, NULL, keyword_enum_to_str(un->op), NULL));
            return result;
        }

        case AST_ASSIGN: {
            AST_Assign* asg = node->data;
            char* rhs = gen_tac(asg->rhs, prog, arena,loop_ctx);
            AST_Identifier* ident = asg->lhs->data;
            tac_append(prog, tac_create_instr(arena, TAC_ASSIGN, ident->name, rhs, NULL, NULL, NULL));
            return ident->name;
        }

        case AST_ASSIGNDECL: {
            AST_Assign* asg = node->data;
            char* rhs = gen_tac(asg->rhs, prog, arena,loop_ctx);
            AST_Identifier* ident = asg->lhs->data;
            tac_append(prog, tac_create_instr(arena, TAC_ASSIGN, ident->name, rhs, NULL, NULL, NULL));
            return ident->name;
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
            char* val = gen_tac(ret->expr, prog, arena,loop_ctx);
            tac_append(prog, tac_create_instr(arena, TAC_RETURN, NULL, val, NULL, NULL, NULL));
            return NULL;
        }

        case AST_IFELSE: {
            AST_Ifelse* ifs = node->data;
            char* cond = gen_tac(ifs->condition, prog, arena,loop_ctx);
            char* then_label = new_label(arena);
            char* end_label  = new_label(arena);

            tac_append(prog, tac_create_instr(arena, TAC_IFGOTO, NULL, cond, "0", "!=", then_label));

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

            LoopContext* new_ctx = (LoopContext*)arena_alloc(arena,sizeof(LoopContext));
            new_ctx->break_label = end_label,
            new_ctx->continue_label = cond_label;
            new_ctx->prev = loop_ctx;

            tac_append(prog, tac_create_instr(arena, TAC_LABEL, NULL, NULL, NULL, NULL, cond_label));

            char* cond = gen_tac(loop->expr, prog, arena, new_ctx);
            tac_append(prog, tac_create_instr(arena, TAC_IFGOTO, NULL, cond, "0", "!=", body_label));
            
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
                tac_append(prog, tac_create_instr(arena, TAC_PARAM, NULL, param, NULL, NULL, NULL));
            }

            gen_tac(fn->block, prog, arena,loop_ctx);
            tac_append(prog, tac_create_instr(arena, TAC_FUNC_END, NULL, NULL, NULL, NULL, NULL));
            return NULL;
        }

        case AST_FUNCTIONCALL: {
            AST_FunctionCall* call = node->data;
            for (int i = 0; i < call->args_count; ++i) {
                char* arg = gen_tac(call->args[i], prog, arena, loop_ctx);
                tac_append(prog, tac_create_instr(arena, TAC_PARAM, NULL, arg, NULL, NULL, NULL));
            }

            char* result = new_temp(arena);
            AST_Identifier* name = call->name->data;

            TACInstr* call_instr = tac_create_instr(arena, TAC_CALL, result, name->name, NULL, NULL, NULL);
            call_instr->arg_count = call->args_count;

            tac_append(prog, call_instr);
            return result;
        }

        default: {
            return NULL;
        }
    }
}

void tac_debug_print(TACList* list) {
    printf("\n==== TAC DEBUG DUMP ====\n");
    int index = 0;
    for (TACInstr* instr = list->head; instr; instr = instr->next, ++index) {
        printf("[%03d] op=%d, result=%s, arg1=%s, arg2=%s, relop=%s, label=%s, argc=%d\n",
            index,
            instr->op,
            instr->result ? instr->result : "NULL",
            instr->arg1 ? instr->arg1 : "NULL",
            instr->arg2 ? instr->arg2 : "NULL",
            instr->relop ? instr->relop : "NULL",
            instr->label ? instr->label : "NULL",
            instr->arg_count
        );
    }
    printf("========================\n");
}

void tac_colored_print(TACList* list) {
    printf("\n\x1b[1m==== TAC ====\x1b[0m\n\n");

    for (TACInstr* instr = list->head; instr; instr = instr->next) {
        switch (instr->op) {

            case TAC_EXTERN:
                printf("  %sextern%s      %s%-10s%s\n",
                        COLOR_RESULT, COLOR_RESET,
                        COLOR_ARG, instr->result, COLOR_RESET);
                break;
            case TAC_ASSIGN:
                printf("  %s%-10s%s = %s%-10s%s\n",
                        COLOR_RESULT, instr->result, COLOR_RESET,
                        COLOR_ARG, instr->arg1, COLOR_RESET);
                break;
            case TAC_BINOP:
                printf("  %s%-10s%s = %s%-10s%s %s%-8s%s %s%-10s%s\n",
                        COLOR_RESULT, instr->result, COLOR_RESET,
                        COLOR_ARG, instr->arg1, COLOR_RESET,
                        COLOR_OP, instr->relop, COLOR_RESET,
                        COLOR_ARG, instr->arg2, COLOR_RESET);
                break;
            case TAC_UNOP:
                printf("  %s%-10s%s = %s%-8s%s %s%-10s%s\n",
                        COLOR_RESULT, instr->result, COLOR_RESET,
                        COLOR_OP, instr->relop, COLOR_RESET,
                        COLOR_ARG, instr->arg1, COLOR_RESET);
                break;
            case TAC_LABEL:
                printf("%s%s:%s\n", COLOR_LABEL, instr->label, COLOR_RESET);
                break;
            case TAC_GOTO:
                printf("  %sgoto%s %s%s%s\n", COLOR_OP, COLOR_RESET, COLOR_LABEL, instr->label, COLOR_RESET);
                break;
            case TAC_IFGOTO:
                printf("  %sif%s %s%-10s%s %s%-8s%s %s%-10s%s %sgoto%s %s%s%s\n",
                        COLOR_OP, COLOR_RESET,
                        COLOR_ARG, instr->arg1, COLOR_RESET,
                        COLOR_OP, instr->relop, COLOR_RESET,
                        COLOR_ARG, instr->arg2, COLOR_RESET,
                        COLOR_OP, COLOR_RESET, COLOR_LABEL, instr->label, COLOR_RESET);
                break;
            case TAC_PARAM:
                printf("  %sparam%s %s%s%s\n", COLOR_OP, COLOR_RESET, COLOR_ARG, instr->arg1, COLOR_RESET);
                break;
            case TAC_CALL:
                printf("  %s%-10s%s = %scall%s %s%s%s, %s%d%s\n",
                        COLOR_RESULT, instr->result, COLOR_RESET,
                        COLOR_OP, COLOR_RESET,
                        COLOR_ARG, instr->arg1, COLOR_RESET,
                        COLOR_COMMENT, instr->arg_count, COLOR_RESET);
                break;
            case TAC_RETURN:
                printf("  %sreturn%s %s%s%s\n", COLOR_OP, COLOR_RESET, COLOR_ARG, instr->arg1, COLOR_RESET);
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

void tac_export_dot(TACList* list, const char* filename) {
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
                snprintf(label,sizeof(label),"extern  %s", instr->result);
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
                snprintf(label, sizeof(label), "%s = %s", instr->result, instr->arg1);
                break;
            case TAC_BINOP:
                snprintf(label, sizeof(label), "%s = %s %s %s", instr->result, instr->arg1, instr->relop, instr->arg2);
                break;
            case TAC_UNOP:
                snprintf(label, sizeof(label), "%s = %s %s", instr->result, instr->relop, instr->arg1);
                break;
            case TAC_IFGOTO:
                snprintf(label, sizeof(label), "if %s %s %s goto %s", instr->arg1, instr->relop, instr->arg2, instr->label);
                break;
            case TAC_GOTO:
                snprintf(label, sizeof(label), "goto %s", instr->label);
                break;
            case TAC_LABEL:
                snprintf(label, sizeof(label), "%s:", instr->label);
                break;
            case TAC_CALL:
                snprintf(label, sizeof(label), "%s = call %s (%d)", instr->result, instr->arg1, instr->arg_count);
                break;
            case TAC_PARAM:
                snprintf(label, sizeof(label), "param %s", instr->arg1);
                break;
            case TAC_RETURN:
                snprintf(label, sizeof(label), "return %s", instr->arg1);
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

void tac_print(TACList* list) { 
    for (TACInstr* instr = list->head; instr; instr = instr->next) {
        switch (instr->op) {
            case TAC_ASSIGN:
                printf("%s = %s\n", instr->result, instr->arg1);
                break;
            case TAC_BINOP:
                printf("%s = %s %s %s\n", instr->result, instr->arg1, instr->relop, instr->arg2);
                break;
            case TAC_UNOP:
                printf("%s = %s %s\n", instr->result, instr->relop, instr->arg1);
                break;
            case TAC_LABEL:
                printf("%s:\n", instr->label);
                break;
            case TAC_GOTO:
                printf("goto %s\n", instr->label);
                break;
            case TAC_IFGOTO:
                printf("if %s %s %s goto %s\n", instr->arg1, instr->relop, instr->arg2, instr->label);
                break;
            case TAC_PARAM:
                printf("param %s\n", instr->arg1);
                break;
            case TAC_CALL:
                printf("%s = call %s, %d\n", instr->result, instr->arg1, instr->arg_count);
                break;
            case TAC_RETURN:
                printf("return %s\n", instr->arg1);
                break;
            case TAC_FUNC_BEGIN:
                printf("function %s begin:\n", instr->label);
                break;
            case TAC_FUNC_END:
                printf("function end\n");
                break;
            case TAC_MAIN_BEGIN:
                printf("%s begin:\n",instr->label);
                break;
            case TAC_MAIN_END:
                printf("main end\n");
                break;
            case TAC_EXTERN:
                printf("extern %s\n",instr->result);
                break;
            default:
                printf("nop\n");
                
        }
    }
}