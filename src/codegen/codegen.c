#include "bl_ir.h"

static void mangleGlobal(char *out, const char *name);
static int get_offset(SymbolTableList* slist,char* name,int scope_id);
static SymbolTable* search_table_given_scopeid(SymbolTableList* slist,int scope_id);
static SymbolTable* symbol_table_values(SymbolTableList* slist, char* table_name,bl_arena* arena);
char* double_to_hex(float value);
static bool check_in_global(char* name,SymbolTableList* slist);
static bool is_function_called(char* name, TACInstr* current,bl_arena* arena);
bl_stack* get_float_reg_stack(bl_arena* arena);
bl_stack* get_norm_reg_stack(bl_arena* arena);


static void emitProlog(FILE *fp, SymbolTableList* slist);
static void emitExterns(FILE* fp,SymbolTableList* slist);
static void emitUndeclared(FILE* fp, SymbolTableList* slist);
static void emitGlobals(FILE *fp, SymbolTableList* slist);
static void emitFunction(FILE* fp,SymbolTable* table,SymbolTableList* slist,TACList* list,bl_arena* arena);
static void emitMain(FILE* fp, SymbolTable* table, SymbolTableList* slist,TACList* instr);
static void emitFuncHeader(FILE *fp, char* table_name,int frameSize);
static void emitMainHeader(FILE *fp, char* table_name,int frameSize);
static void emitFuncFooter(FILE *fp);
static void emitMainFooter(FILE* fp);

void generateAssembly(const char* outfile, SymbolTableList* slist, TACList* list,bl_arena* arena);

int main(){
    char* filename = "src/codegen/one.bl";
    bl_arena* arena = (bl_arena*)malloc(sizeof(bl_arena));
    arena_init(arena);

    bl_ir* ir = bhaulang_ir(filename,arena);
    // print_all_symbol_tables(ir->slist);
    // visualize_symbol_tables_ascii(ir->slist->tables[0]);
    // tac_print(ir->list,arena);

    generateAssembly("src/codegen/out.asm",ir->slist,ir->list,arena);
    
    // arena_stats(arena);
}


static void mangleGlobal(char *out, const char *name){ 
    sprintf(out,"global_%s",name); 
}
// static void mangleLocal (char *out, const char* func_name, const char *name){ 
//     sprintf(out,"%s_%s",func_name,  name); 
// }


static void emitProlog(FILE *fp, SymbolTableList* slist)
{
    fputs("SECTION .text\n" 
          "global  main\n", fp);
    emitExterns(fp,slist);
}

static void emitEpilog(FILE* fp){
    fputs("SECTION .note.GNU-stack\n", fp);
}

void generateAssembly(const char* outfile, SymbolTableList* slist, TACList* list,bl_arena* arena){
    FILE *fp = fopen(outfile,"w");
    if (!fp) {fprintf(stderr,"Cannot open build file\n"); exit(1);}
    emitGlobals(fp,slist);
    emitUndeclared(fp,slist);
    emitProlog(fp,slist);
    for (TACInstr* instr = list->head; instr; instr = instr->next){
        if(instr->op == TAC_FUNC_BEGIN || instr->op == TAC_MAIN_BEGIN){
            switch(instr->op){
                case TAC_FUNC_BEGIN:{
                    if(is_function_called(instr->label,instr,arena)){
                        list = update_list_types(list,arena);
                        SymbolTable* table = symbol_table_values(slist,instr->label,arena);
                        list->head = instr->next;
                        emitFunction(fp,table,slist,list,arena);
                        break;
                    }else{
                        while(instr->op != TAC_FUNC_END){
                            instr = instr->next;
                        }
                        list->head = instr->next;
                        break;
                    }
                }
                case TAC_MAIN_BEGIN:{
                    SymbolTable* table = symbol_table_values(slist,instr->label,arena);
                    list->head = instr->next;
                    emitMain(fp,table,slist,list);
                    break;
                }
                default:
                    break;
            }
        }
    }
    emitEpilog(fp);
}

static bool check_in_global(char* name,SymbolTableList* slist){
    char cmp_label[64];
    mangleGlobal(cmp_label,name);
    SymbolTable* gtable = slist->tables[0];
    for(int i = 0;i< gtable->symbol_count; i++){
        char label[64]; 
        mangleGlobal(label, gtable->entries[i]->name);
        if(strcmp(label,cmp_label) == 0){
            return 1;
        }
    }
    return 0;
}

//WARN language does not support function overloading :0
static bool is_function_called(char* name, TACInstr* current,bl_arena* arena){
    TACInstr* instr = current;
    TACInstr* params = current->next;
    TACInstr* call_ptr = (TACInstr*)arena_alloc(arena,sizeof(TACInstr));
    //WARN sneaky hack :)
    int arg_count = 2000;
    while(instr){
        if(instr->op == TAC_CALL){
            if(strcmp(name,instr->arg1->val.sval) == 0){
                call_ptr = instr;
                arg_count = instr->arg_count;
            }
        }
        instr = instr->next;
    }

    instr = current;
    //TODO, currently, something like printf("%d\n",func(1)); wont work, because it will generate a TAC of
    //TODO printf->arg1 : func->arg1 : printf->arg2
    if(arg_count < 1000){
        bl_stack* instr_arg_stack = (bl_stack*)arena_alloc(arena,sizeof(bl_stack));
        bl_stack* instr_param_stack = (bl_stack*)arena_alloc(arena,sizeof(bl_stack));
        stack_init(instr_param_stack,arena,2048);
        stack_init(instr_arg_stack,arena,2048);
        while(params->op == TAC_PARAM){
            stack_push(instr_param_stack,params);
            params = params->next;
        }
        while(instr){
            stack_push(instr_arg_stack,instr);
            if(instr == call_ptr){
                call_ptr = instr;
                break;
            }
            instr = instr->next;
        }
        int tmp_arg_count = arg_count;
        while(tmp_arg_count > 0){
            TACInstr* arg_instr = stack_pop(instr_arg_stack);
            if(arg_instr->op == TAC_ARG){
                TACInstr* param_instr = stack_pop(instr_param_stack);
                param_instr->arg1->acquired_type = arg_instr->arg1->acquired_type;
                tmp_arg_count--;
            }
        }

        return 1;
    }else{
        return 0;
    }
}

static bool get_fromGlobal(FILE* fp,SymbolTableList* slist,TACInstr* instr,char* name){
    char cmp_label[64];
    mangleGlobal(cmp_label,name);
    SymbolTable* gtable = slist->tables[0];
    for(int i = 0;i< gtable->symbol_count; i++){
        char label[64]; 
        mangleGlobal(label, gtable->entries[i]->name);
        if(strcmp(label,cmp_label) == 0){
            switch(gtable->entries[i]->type){
                case TYPE_INT:
                case TYPE_FLOAT:
                case TYPE_CHAR:
                case TYPE_BOOL:
                    fprintf(fp,"    mov rax, [%s]\n"
                               "    mov QWORD [rbp - %d], rax\n", label,get_offset(slist,instr->result->val.sval,instr->result->scope_id));
                    return 1;
                case TYPE_STRING:
                    fprintf(fp,"    mov rax, %s\n"
                               "    mov QWORD [rbp - %d], rax\n",label,get_offset(slist,instr->result->val.sval,instr->result->scope_id));
                    return 1;
                
                default:
                    fprintf(stderr, "Globals can only be int, float, string, char and bool");
                    exit(1);

            }
        }
    }
    return 0;
}

static void emitGlobals(FILE *fp, SymbolTableList* slist){
    fputs("SECTION .data\n", fp);
    SymbolTable* table = slist->tables[0];
    for(int i = 0;i<table->symbol_count;i++){
        //REF variable length is limited to 64 characters

        switch(table->entries[i]->type){
            case TYPE_INT : {
                char label[64];  
                mangleGlobal(label, table->entries[i]->name);
                fprintf(fp,"%-20s %s ", label, "dq");
                fprintf(fp,"%d",table->entries[i]->int_val);
                fputc('\n',fp);
                break;
            }
            case TYPE_FLOAT : {
                char label[64];  
                mangleGlobal(label, table->entries[i]->name);
                fprintf(fp,"%-20s %s ", label, "dq");
                fprintf(fp,"%.16f",table->entries[i]->float_val);
                fputc('\n',fp);
                break;
            }            
            case TYPE_CHAR : {
                char label[64];  
                mangleGlobal(label, table->entries[i]->name);
                fprintf(fp,"%-20s %s ", label, "dq");
                fprintf(fp,"\'%c\'",table->entries[i]->char_val);
                fputc('\n',fp);
                break;
            }            
            case TYPE_STRING : {
                char label[64];  
                mangleGlobal(label, table->entries[i]->name);
                fprintf(fp,"%-20s %s ", label, "dq");
                fprintf(fp,"\"%s\",0",table->entries[i]->string_val);
                fputc('\n',fp);
                break;
            }            
            case TYPE_BOOL : {
                char label[64];  
                mangleGlobal(label, table->entries[i]->name);
                fprintf(fp,"%-20s %s ", label, "dq");
                fprintf(fp,"%d",table->entries[i]->bool_val == true ? 1 : 0);
                fputc('\n',fp);
                break;
            }            
            default: 
                break;
        }
    }
    fputc('\n',fp);
}

static void emitExterns(FILE* fp,SymbolTableList* slist){
    SymbolTable* table = slist->tables[0];

    for(int i = 0; i<table->symbol_count; i++){
        switch(table->entries[i]->type){
            case TYPE_EXTERN:
                fprintf(fp,"extern %s\n",table->entries[i]->name);
                break;
            default:
                break;
        }
    }
}

static void emitUndeclared(FILE* fp, SymbolTableList* slist){
    SymbolTable* table = slist->tables[0];
    
    fputs(
    "SECTION .bss\n", fp);
    for(int i = 0; i<table->symbol_count; i++){
        switch(table->entries[i]->type){
            case TYPE_UNDECLARED:
                char label[64];
                mangleGlobal(label,table->entries[i]->name);
                fprintf(fp,"%s resq 1\n",label);
                break;
            default:
                break;
        }
    }
    fputc('\n',fp);
}


static int get_offset(SymbolTableList* slist,char* name,int scope_id){
    SymbolTable* tmp_table = search_table_given_scopeid(slist,scope_id);
    while(tmp_table->parent != NULL){
        for(int i = 0;i<tmp_table->symbol_count;i++){
            if(strcmp(tmp_table->entries[i]->name,name) == 0){
                return tmp_table->entries[i]->offset;
            }
        }
        tmp_table = tmp_table->parent;
    }
    return 0;
}

static SymbolTable* search_table_given_scopeid(SymbolTableList* slist,int scope_id){
    for(int i = 0;i<slist->table_count;i++){
        if(slist->tables[i]->scope_id == scope_id){
            return slist->tables[i];
        }
    }
    return NULL;
}



static SymbolTable* symbol_table_values(SymbolTableList* slist, char* table_name,bl_arena* arena){
    SymbolTable* g_table = slist->tables[0];
    SymbolTable* table = (SymbolTable*)arena_alloc(arena,sizeof(SymbolTable));
    for(int i = 0;i<g_table->children_count;i++){
        if(strcmp(g_table->children[i]->scope_name,table_name) == 0){
            table = g_table->children[i];
        }
    }
    return table;
}

bl_stack* get_norm_reg_stack(bl_arena* arena){
    bl_stack* norm_stack = (bl_stack*)arena_alloc(arena,sizeof(bl_stack));
    stack_init(norm_stack,arena,32);
    stack_push(norm_stack,"r9");
    stack_push(norm_stack,"r8");
    stack_push(norm_stack,"rcx");
    stack_push(norm_stack,"rdx");
    stack_push(norm_stack,"rsi");
    stack_push(norm_stack,"rdi");
    return norm_stack;
}

bl_stack* get_float_reg_stack(bl_arena* arena){
    bl_stack* float_stack = (bl_stack*)arena_alloc(arena,sizeof(bl_stack));
    stack_init(float_stack,arena,32);
    stack_push(float_stack,"xmm7");
    stack_push(float_stack,"xmm6");
    stack_push(float_stack,"xmm5");
    stack_push(float_stack,"xmm4");
    stack_push(float_stack,"xmm3");
    stack_push(float_stack,"xmm2");
    stack_push(float_stack,"xmm1");
    stack_push(float_stack,"xmm0");
    return float_stack;
}

static void emitFunction(FILE* fp, SymbolTable* table,  SymbolTableList* slist,TACList* list,bl_arena* arena){

    emitFuncHeader(fp,table->scope_name,table->total_offset);
    TACInstr* instr = list->head;
    int param_norm_count = 0;
    int param_float_count = 0;
    bl_stack* reg_norm_stack = get_norm_reg_stack(arena);
    bl_stack* reg_float_stack = get_float_reg_stack(arena);
    while(instr->op != TAC_FUNC_END){
       switch(instr->op){
            case TAC_PARAM: {
                if(param_norm_count > 6 || param_float_count > 8){
                    fprintf(stderr,"Arguments can only be upto 6 non-floats + 8 floats; Need to implement assigning args on stack\n");
                    exit(1);
                }
                if(instr->arg1->acquired_type != TYPE_FLOAT){
                    fprintf(fp,"    mov QWORD [rbp - %d], %s\n",get_offset(slist,instr->arg1->val.sval,instr->arg1->scope_id),(char*)stack_pop(reg_norm_stack));
                    param_norm_count++;
                }else{
                    fprintf(fp,"    movsd QWORD [rbp - %d], %s\n",get_offset(slist,instr->arg1->val.sval,instr->arg1->scope_id),(char *)stack_pop(reg_float_stack));
                    param_float_count++;
                }
                break;
            }
            case TAC_RETURN: {
                fprintf(fp,"    mov rax, QWORD [rbp - %d]\n",get_offset(slist,instr->arg1->val.sval,instr->arg1->scope_id));
                break;
            }
            case TAC_ASSIGNDECL:{
                if(instr->arg1){
                    switch(instr->arg1->type){
                        case TYPE_INT:{
                            fprintf(fp,"    mov QWORD [rbp - %d], %d\n",get_offset(slist,instr->result->val.sval,instr->result->scope_id),instr->arg1->val.ival);
                            break;
                        }
                        case TYPE_FLOAT:{
                            fprintf(fp,"    mov rax, %s\n"
                                       "    movq xmm0, rax\n"
                                       "    movsd QWORD [rbp - %d], xmm0\n",double_to_hex(instr->arg1->val.fval), get_offset(slist,instr->result->val.sval,instr->result->scope_id));
                            break;
                        }
                        case TYPE_CHAR:{
                            fprintf(fp,"    mov QWORD [rbp - %d], \'%c\'\n",get_offset(slist,instr->result->val.sval,instr->result->scope_id),instr->arg1->val.cval);
                            break;
                        }
                        case TYPE_BOOL:{
                            fprintf(fp,"    mov QWORD [rbp - %d], %d\n",get_offset(slist,instr->result->val.sval,instr->result->scope_id),instr->arg1->val.bval == true ? 1 : 0);
                            break;
                        }
                        case TYPE_STRING:{
                            char* tmp_str = instr->arg1->val.sval;
                            int tmp_offset = get_offset(slist,instr->result->val.sval,instr->result->scope_id);
                            fprintf(fp,
                            "    lea rax, [rbp - %d]\n"
                            "    mov QWORD [rbp - %d], rax\n",tmp_offset-8,tmp_offset);
                            tmp_offset -= 8;
                            int i = 0;
                            char tmp_char = tmp_str[i];
                            while(tmp_char != '\0'){
                                if(tmp_char == '\\'){
                                    if(tmp_str[i+1] == '\0'){
                                        fprintf(stderr,"Cannot use single backslash in string, use `\\\\`\n");
                                        exit(1);
                                    }
                                    if(tmp_str[i+1] == 'n'){
                                        fprintf(fp,"    mov byte [rbp - %d], 0x0A\n",tmp_offset);
                                        i+=2;
                                        tmp_char = tmp_str[i];
                                        tmp_offset-=1;
                                    }else if(tmp_str[i+1] == 't'){
                                        fprintf(fp,"    mov byte [rbp - %d], 0x09\n",tmp_offset);
                                        i+=2;
                                        tmp_char = tmp_str[i];
                                        tmp_offset-=1;
                                    }else if(tmp_str[i+1] == 'r'){
                                        fprintf(fp,"    mov byte [rbp - %d], 0x0D\n",tmp_offset);
                                        i+=2;
                                        tmp_char = tmp_str[i];
                                        tmp_offset-=1;
                                    }else if(tmp_str[i+1] == '"'){
                                        fprintf(fp,"    mov byte [rbp - %d], 0x22\n",tmp_offset);
                                        i+=2;
                                        tmp_char = tmp_str[i];
                                        tmp_offset-=1;
                                    }else if(tmp_str[i+1] == '\''){
                                        fprintf(fp,"    mov byte [rbp - %d], 0x27\n",tmp_offset);
                                        i+=2;
                                        tmp_char = tmp_str[i];
                                        tmp_offset-=1;
                                    }else if(tmp_str[i+1] == '\\'){
                                        fprintf(fp,"    mov byte [rbp - %d], 0x5C\n",tmp_offset);
                                        i+=2;
                                        tmp_char = tmp_str[i];
                                        tmp_offset-=1;
                                    }else{
                                        fprintf(stderr,"Cannot use single backslash in a string, use `\\\\`\n");
                                        exit(1);
                                    }
                                }else{
                                    fprintf(fp,"    mov byte [rbp - %d], \'%c\'\n",tmp_offset,tmp_char);
                                    i++;
                                    tmp_char = tmp_str[i];
                                    tmp_offset-=1;
                                }
                            }
                            fprintf(fp,"    mov byte [rbp - %d], %d\n",tmp_offset,0);
                            break;
                        }
                        case TYPE_REF:{
                                fprintf(fp,"    mov rax, QWORD [rbp - %d]\n"
                                           "    mov QWORD [rbp - %d], rax\n",get_offset(slist,instr->arg1->val.sval,instr->arg1->scope_id),get_offset(slist,instr->result->val.sval,instr->result->scope_id));
                                break;
                            }
                        case TYPE_PTR:{
                                fprintf(fp,"    mov rax, QWORD [rbp - %d]\n"
                                           "    mov QWORD [rbp - %d], rax\n",get_offset(slist,instr->arg1->val.sval,instr->arg1->scope_id),get_offset(slist,instr->result->val.sval,instr->result->scope_id));
                                break;
                            }
                        case TYPE_IDENTIFIER:{
                            if(get_offset(slist,instr->arg1->val.sval,instr->arg1->scope_id)){
                                fprintf(fp,"    mov rax, QWORD [rbp - %d]\n"
                                           "    mov QWORD [rbp - %d], rax\n",get_offset(slist,instr->arg1->val.sval,instr->arg1->scope_id),get_offset(slist,instr->result->val.sval,instr->result->scope_id));
                            }else if(get_fromGlobal(fp,slist,instr,instr->arg1->val.sval)){
                            }else{
                                fprintf(stderr,"%s %d Identifier not found, got `%s`\n",__FILE__,__LINE__,instr->arg1->val.sval);
                                exit(1);
                            }
                            break;
                        }
                        default:{
                            break;
                        }
                    }
                }else{
                    fprintf(fp,"    mov QWORD [rbp - %d], %d\n",get_offset(slist,instr->result->val.sval,instr->result->scope_id),0);
                    break;
                }
                break;
            }


            case TAC_ASSIGN: {
                if(get_offset(slist,instr->result->val.sval,instr->result->scope_id)){
                    switch(instr->arg1->type){
                        case TYPE_INT: {
                            fprintf(fp,"    mov QWORD [rbp - %d], %d\n",get_offset(slist,instr->result->val.sval,instr->result->scope_id),instr->arg1->val.ival);
                            break;
                        }
                        case TYPE_FLOAT: {
                            fprintf(fp,"    mov rax, %s\n"
                                       "    movq xmm0, rax\n"
                                       "    movsd QWORD [rbp - %d], xmm0\n",double_to_hex(instr->arg1->val.fval), get_offset(slist,instr->result->val.sval,instr->result->scope_id));
                            break;
                        }
                        case TYPE_CHAR: {
                            fprintf(fp,"    mov QWORD [rbp - %d], \'%c\'",get_offset(slist,instr->result->val.sval,instr->result->scope_id),instr->arg1->val.cval);
                            break;
                        }
                        case TYPE_BOOL: {
                            fprintf(fp,"    mov QWORD [rbp - %d], %d\n",get_offset(slist,instr->result->val.sval,instr->result->scope_id),instr->arg1->val.bval == true ? 1: 0);
                            break;
                        }
                        case TYPE_REF : {
                            fprintf(fp,"    mov rax, QWORD [rbp - %d]\n"
                                       "    mov QWORD [rbp - %d], rax\n",get_offset(slist,instr->arg1->val.sval,instr->arg1->scope_id),get_offset(slist,instr->result->val.sval,instr->result->scope_id));
                            break;
                        }
                        case TYPE_PTR : {
                            fprintf(fp,"    mov rax, QWORD [rbp - %d]\n"
                                       "    mov QWORD [rbp - %d], rax\n",get_offset(slist,instr->arg1->val.sval,instr->arg1->scope_id),get_offset(slist,instr->result->val.sval,instr->result->scope_id));
                            break;
                        }
                        case TYPE_IDENTIFIER: {
                            if(get_offset(slist,instr->arg1->val.sval,instr->arg1->scope_id)){
                                fprintf(fp,"    mov rax, QWORD [rbp - %d]\n"
                                           "    mov QWORD [rbp - %d], rax\n",get_offset(slist,instr->arg1->val.sval,instr->arg1->scope_id),get_offset(slist,instr->result->val.sval,instr->result->scope_id));
                            }else if(check_in_global(instr->arg1->val.sval,slist)){
                                char label[64];
                                mangleGlobal(label,instr->arg1->val.sval);
                                fprintf(fp,"    mov rax, [%s]\n"
                                           "    mov QWORD [rbp - %d], rax\n", label,get_offset(slist,instr->result->val.sval,instr->result->scope_id));

                            }else{
                                fprintf(stderr,"Identifier not found, got `%s`\n",instr->arg1->val.sval);
                                exit(1);
                            }
                            break;
                        }
                        default:
                            break;
                    }
                }else if(check_in_global(instr->result->val.sval,slist)){
                    char cmp_label[64];
                    mangleGlobal(cmp_label,instr->result->val.sval);
                    SymbolTable* gtable = slist->tables[0];
                    for(int i = 0;i< gtable->symbol_count; i++){
                        char label[64]; 
                        mangleGlobal(label, gtable->entries[i]->name);
                        if(strcmp(label,cmp_label) == 0){
                            switch(instr->arg1->type){
                                case TYPE_INT:
                                    fprintf(fp,"    mov QWORD [%s], %d\n",label,instr->arg1->val.ival);
                                    break;
                                case TYPE_FLOAT:
                                    fprintf(fp,"    mov rax, %s\n"
                                               "    movq xmm0, rax\n"
                                               "    movsd QWORD [%s], xmm0\n",double_to_hex(instr->arg1->val.fval),label);
                                    break;
                                case TYPE_CHAR:
                                    fprintf(fp,"    mov QWORD [%s], \'%c\'\n",label,instr->arg1->val.cval);
                                    break;
                                case TYPE_BOOL:
                                    fprintf(fp,"    mov QWORD [%s], %d\n",label,instr->arg1->val.bval == true? 1 : 0);
                                    break;
                                case TYPE_REF:
                                    fprintf(fp,"    mov rax, QWORD [rbp - %d]\n"
                                               "    mov QWORD [%s], rax\n",get_offset(slist,instr->arg1->val.sval,instr->arg1->scope_id),label);
                                    break;
                                case TYPE_PTR:
                                    fprintf(fp,"    mov rax, QWORD [rbp - %d]\n"
                                               "    mov QWORD [%s],rax\n",get_offset(slist,instr->arg1->val.sval,instr->arg1->scope_id),label);
                                    break;
                                case TYPE_IDENTIFIER:
                                    if(get_offset(slist,instr->arg1->val.sval,instr->arg1->scope_id)){
                                        fprintf(fp,"    mov rax, QWORD [rbp - %d]\n"
                                                   "    mov QWORD [%s], rax\n",get_offset(slist,instr->arg1->val.sval,instr->arg1->scope_id),label);
                                        break;
                                    }else if(check_in_global(instr->arg1->val.sval,slist)){
                                        char cmp_label[64];
                                        mangleGlobal(cmp_label,instr->arg1->val.sval);
                                        fprintf(fp,"    mov rax, [%s]\n"
                                                   "    mov QWORD [%s], rax\n",cmp_label,label);
                                        break;
                                    }else{
                                        fprintf(stderr,"Unknown identifer, got `%s`\n",instr->arg1->val.sval);
                                        exit(1);
                                    }
                                case TYPE_STRING:
                                    fprintf(stderr,"Strings cannot be re assigned\n");
                                    exit(1);                              
                                default:
                                    fprintf(stderr, "Globals can only be int, float, string, char and bool");
                                    exit(1);

                            }
                        }
                    }
                }else{
                    fprintf(stderr,"Identifier not found, got `%s`\n",instr->result->val.sval);
                    exit(1);
                }
                break;
            }

            case TAC_ADDR_OF:{
                if(get_offset(slist,instr->arg1->val.sval,instr->arg1->scope_id)){
                    fprintf(fp,"    lea rax, QWORD [rbp - %d]\n"
                               "    mov QWORD [rbp - %d], rax\n",get_offset(slist,instr->arg1->val.sval,instr->arg1->scope_id),get_offset(slist,instr->result->val.sval,instr->result->scope_id));
                }else if(check_in_global(instr->arg1->val.sval,slist)){
                    char label[64];
                    mangleGlobal(label,instr->arg1->val.sval);
                    fprintf(fp, "    mov rax, %s\n"
                                "    mov QWORD [rbp - %d], rax\n", label,get_offset(slist,instr->result->val.sval,instr->result->scope_id));
                }else{
                    fprintf(stderr,"Identifier not found, got `%s`\n",instr->arg1->val.sval);
                    exit(1);
                }
                break;
            }

            case TAC_LOAD_PTR: {
                if(get_offset(slist,instr->arg1->val.sval,instr->arg1->scope_id)){
                    fprintf(fp,"    mov rax, QWORD [rbp - %d]\n"
                               "    mov rax, QWORD [rax]\n"
                               "    mov QWORD [rbp - %d], rax\n",get_offset(slist,instr->arg1->val.sval,instr->arg1->scope_id),get_offset(slist,instr->result->val.sval,instr->result->scope_id));
                }else if(check_in_global(instr->arg1->val.sval,slist)){
                    fprintf(stderr,"Cannot dereference global variables, Globals can be : int, float, char, string, bool\n");
                    exit(1);
                }else{
                    fprintf(stderr,"Identifier not found, got `%s`\n",instr->arg1->val.sval);
                    exit(1);
                }
                break;
            }

            case TAC_LABEL:{
                fprintf(fp,"    .%s:\n",instr->label);
                break;
            }

            case TAC_NOP: {
                break;
            }

            case TAC_GOTO: {
                fprintf(fp,"    jmp .%s\n",instr->label);
                break;
            }

            case TAC_IFGOTO: {
                if(strcmp(instr->relop->operator_str,"!=")==0){
                    if(instr->arg1->type == TYPE_IDENTIFIER){
                        fprintf(fp,"    mov rax, QWORD [rbp - %d]\n"
                                   "    cmp rax, %d\n"
                                   "    jne .%s\n",get_offset(slist,instr->arg1->val.sval,instr->arg1->scope_id),instr->arg2->val.ival,instr->label);
                    }else if(instr->arg1->type == TYPE_INT){
                        fprintf(fp,"    mov rax, %d\n"
                                   "    cmp rax, %d\n"
                                   "    jne .%s\n",instr->arg1->val.ival,instr->arg2->val.ival,instr->label);
                    }else if(instr->arg1->type == TYPE_BOOL){
                        fprintf(fp,"    mov rax, %d\n"
                                   "    cmp rax, %d\n"
                                   "    jne .%s\n",instr->arg1->val.bval == true ? 1 : 0,instr->arg2->val.ival,instr->label);
                    }
                }else if(strcmp(instr->relop->operator_str,"==") == 0){
                    //TODO will potentially error out in switch since arg1 can be int, char or an identifier
                    if(instr->arg2->type == TYPE_CHAR){
                        fprintf(fp,"    mov rax, QWORD [rbp - %d]\n"
                                   "    cmp rax, \'%c\'\n"
                                   "    je .%s\n",get_offset(slist,instr->arg1->val.sval,instr->arg1->scope_id),instr->arg2->val.cval,instr->label);
                    }else if(instr->arg2->type == TYPE_INT){
                        fprintf(fp,"    mov rax, QWORD [rbp - %d]\n"
                                   "    cmp rax, %d\n"
                                   "    je .%s\n",get_offset(slist,instr->arg1->val.sval,instr->arg1->scope_id),instr->arg2->val.ival,instr->label);
                    }
                }
                break;
            }

            case TAC_CALL: {
                fprintf(fp,"    call %s\n"
                           "    mov QWORD [rbp - %d],rax\n",instr->arg1->val.sval,get_offset(slist,instr->result->val.sval,instr->result->scope_id));
                break;
            }

            case TAC_UNOP: {
                if(strcmp(instr->relop->operator_str,"!") == 0){
                    if(get_offset(slist,instr->arg1->val.sval,instr->arg1->scope_id)){
                        switch(instr->arg1->acquired_type){
                            case TYPE_STRING:
                                fprintf(stderr,"Cannot perform logical not on string\n");
                                exit(1);
                                break;
                            case TYPE_INT:
                                fprintf(stderr,"Cannot perform logical not on integer\n");
                                exit(1);
                                break;
                            case TYPE_FLOAT:
                                fprintf(stderr,"Cannot perform logical not on float\n");
                                exit(1);
                                break;
                            case TYPE_CHAR:
                                fprintf(stderr,"Cannot perform logical not on char\n");
                                exit(1);
                            case TYPE_PARAM:
                            case TYPE_IDENTIFIER:
                                fprintf(stderr,"Performing logical not on identifier\n");
                                fprintf(fp,"    mov rax, [rbp - %d]\n"
                                           "    xor rax, 1\n"
                                           "    mov [rbp - %d], rax\n", get_offset(slist,instr->arg1->val.sval,instr->arg1->scope_id),get_offset(slist,instr->result->val.sval,instr->result->scope_id));
                                break;
                            case TYPE_PTR:
                                fprintf(stderr,"Performing logical not on dereference\n");
                                fprintf(fp,"    mov rax, [rbp - %d]\n"
                                           "    xor rax, 1\n"
                                           "    mov [rbp - %d], rax\n", get_offset(slist,instr->arg1->val.sval,instr->arg1->scope_id),get_offset(slist,instr->result->val.sval,instr->result->scope_id));
                                break;
                            case TYPE_BOOL:
                                fprintf(fp,"    mov rax, [rbp - %d]\n"
                                           "    xor rax, 1\n"
                                           "    mov [rbp - %d], rax\n", get_offset(slist,instr->arg1->val.sval,instr->arg1->scope_id),get_offset(slist,instr->result->val.sval,instr->result->scope_id));
                                break;
                            case TYPE_REF:
                                fprintf(stderr,"Cannot perform logical not on reference\n");
                                exit(1);
                            default:
                                fprintf(stderr,"Unary ops for this type not implemented `%d`\n",instr->arg1->acquired_type);
                                exit(1);
                        }
                    }else if(check_in_global(instr->arg1->val.sval,slist)){
                        switch(instr->arg1->acquired_type){
                            case TYPE_STRING:
                                fprintf(stderr,"Cannot perform logical not on string\n");
                                exit(1);
                                break;
                            case TYPE_INT:
                                fprintf(stderr,"Cannot perform logical not on integer\n");
                                exit(1);
                                break;
                            case TYPE_FLOAT:
                                fprintf(stderr,"Cannot perform logical not on floats\n");
                                exit(1);
                                break;
                            case TYPE_CHAR:
                                fprintf(stderr,"Cannot perform logical not on char\n");
                                exit(1);
                                break;
                            case TYPE_BOOL:{
                                char label[64];
                                mangleGlobal(label,instr->arg1->val.sval);
                                fprintf(fp,"    mov rax, [%s]\n"
                                           "    xor rax, 1\n"
                                           "    mov [rbp - %d],rax\n",label,get_offset(slist,instr->result->val.sval,instr->result->scope_id));
                                break;
                            }
                            case TYPE_PARAM:
                            case TYPE_IDENTIFIER:{
                                char label[64];
                                mangleGlobal(label,instr->arg1->val.sval);
                                fprintf(stderr,"Performing logical not on identifier\n");
                                fprintf(fp,"    mov rax, [%s]\n"
                                           "    xor rax, 1\n"
                                           "    mov [rbp - %d],rax\n",label,get_offset(slist,instr->result->val.sval,instr->result->scope_id));
                                break;
                            }
                            default:
                                fprintf(stderr,"Unary ops for this type not implemented `%d`\n",instr->arg1->acquired_type);
                                exit(1);
                        }
                    }else{
                        fprintf(stderr,"%s %d Identifier not found\n",__FILE__,__LINE__);
                        exit(1);
                    }
                }else if(strcmp(instr->relop->operator_str,"-") == 0){
                    if(get_offset(slist,instr->arg1->val.sval,instr->arg1->scope_id)){
                        switch(instr->arg1->acquired_type){
                            case TYPE_STRING:
                                fprintf(stderr,"Cannot perform unary ops on string\n");
                                exit(1);
                            case TYPE_INT:
                                fprintf(fp,"    mov rax,[rbp - %d]\n"
                                           "    neg rax\n"
                                           "    mov [rbp - %d],rax\n",get_offset(slist,instr->arg1->val.sval,instr->arg1->scope_id),get_offset(slist,instr->result->val.sval,instr->result->scope_id));
                                break;
                            case TYPE_CHAR:
                                fprintf(fp,"    mov rax, [rbp - %d]\n"
                                           "    neg rax\n"
                                           "    mov [rbp - %d],rax\n",get_offset(slist,instr->arg1->val.sval,instr->arg1->scope_id),get_offset(slist,instr->result->val.sval,instr->result->scope_id));
                                break;
                            case TYPE_FLOAT:
                                fprintf(fp,"    mov rax, 0xBFF0000000000000\n"
                                           "    movq    xmm1, rax\n"
                                           "    movsd   xmm0, QWORD [rbp-%d]\n"
                                           "    mulsd   xmm0, xmm1\n"
                                           "    movsd [rbp - %d],xmm0\n",get_offset(slist,instr->arg1->val.sval,instr->arg1->scope_id),get_offset(slist,instr->result->val.sval,instr->result->scope_id));
                                break;
                            case TYPE_BOOL:
                                fprintf(stderr,"Cannot perform negation on boolean\n");
                                exit(1);
                            case TYPE_REF:
                                fprintf(stderr,"Cannot perform negation on reference\n");
                                exit(1);
                            case TYPE_PTR:
                                fprintf(stderr,"Performing negation on dereference\n");
                                fprintf(fp,"    mov rax, [rbp - %d]\n"
                                           "    neg rax\n"
                                           "    mov [rbp - %d],rax\n",get_offset(slist,instr->arg1->val.sval,instr->arg1->scope_id),get_offset(slist,instr->result->val.sval,instr->result->scope_id));
                                break;
                            case TYPE_PARAM:
                            case TYPE_IDENTIFIER:
                                fprintf(stderr,"Performing negation on identifier\n");
                                fprintf(fp,"    mov rax, [rbp - %d]\n"
                                           "    neg rax\n"
                                           "    mov [rbp - %d],rax\n",get_offset(slist,instr->arg1->val.sval,instr->arg1->scope_id),get_offset(slist,instr->result->val.sval,instr->result->scope_id));
                                break;
                            default:
                                fprintf(stderr,"Unary ops for this type not implemented `%d`\n",instr->arg1->acquired_type);
                                exit(1);
                        }
                    }else if(check_in_global(instr->arg1->val.sval,slist)){
                        switch(instr->arg1->acquired_type){
                            case TYPE_STRING:
                                fprintf(stderr, "Cannot perform unary ops on string\n");
                                exit(1);
                                break;
                            case TYPE_BOOL:
                                fprintf(stderr,"Cannot perform negation on bool\n");
                                exit(1);
                                break;
                            case TYPE_REF:
                                fprintf(stderr,"Cannot perform negation on reference\n");
                                exit(1);
                                break;
                            case TYPE_INT:{
                                char label[64];
                                mangleGlobal(label,instr->arg1->val.sval);
                                fprintf(fp,"    mov rax, [%s]\n"
                                           "    neg rax\n"
                                           "    mov [rbp - %d],rax\n",label,get_offset(slist,instr->result->val.sval,instr->result->scope_id));
                                break;
                            }
                            case TYPE_CHAR: {
                                char label[64];
                                mangleGlobal(label,instr->arg1->val.sval);
                                fprintf(fp,"    mov rax, [%s]\n"
                                           "    neg rax\n"
                                           "    mov [rbp - %d], rax\n",label,get_offset(slist,instr->result->val.sval,instr->result->scope_id));
                                break;
                            }
                            case TYPE_FLOAT:{
                                char label[64];
                                mangleGlobal(label,instr->arg1->val.sval);
                                fprintf(fp,"    mov rax,0xBFF0000000000000\n"
                                           "    movq xmm1, rax\n"
                                           "    movsd xmm0, QWORD [%s]\n"
                                           "    mulsd xmm0,xmm1\n"
                                           "    movsd [rbp - %d],xmm0\n",label,get_offset(slist,instr->result->val.sval,instr->result->scope_id));
                                break;
                            }
                            case TYPE_PARAM:
                            case TYPE_IDENTIFIER:{
                                char label[64];
                                mangleGlobal(label,instr->arg1->val.sval);
                                fprintf(stderr,"Performing negation on identifier\n");
                                fprintf(fp,"    mov rax, [%s]\n"
                                           "    neg rax\n"
                                           "    mov [rbp - %d],rax\n",label,get_offset(slist,instr->result->val.sval,instr->result->scope_id));
                                break;
                            }
                            default:{
                                fprintf(stderr,"%s %d Negation for this type not implemented `%d`\n",__FILE__,__LINE__,instr->arg1->acquired_type);
                                break;
                            }

                        }
                    }else{
                        fprintf(stderr,"%s %d Identifier not found\n",__FILE__,__LINE__);
                        exit(1);
                    }
                }else if(strcmp(instr->relop->operator_str,"++") == 0){
                    if(get_offset(slist,instr->arg1->val.sval,instr->arg1->scope_id)){
                        switch(instr->arg1->acquired_type){
                            case TYPE_INT:
                                fprintf(fp,"    mov rax, [rbp - %d]\n"
                                           "    inc rax\n"
                                           "    mov [rbp - %d],rax\n",get_offset(slist,instr->arg1->val.sval,instr->arg1->scope_id),get_offset(slist,instr->result->val.sval,instr->result->scope_id));
                                break;
                            case TYPE_CHAR:
                                fprintf(fp,"    mov rax, [rbp - %d]\n"
                                           "    inc rax\n"
                                           "    mov [rbp - %d],rax\n",get_offset(slist,instr->arg1->val.sval,instr->arg1->scope_id),get_offset(slist,instr->result->val.sval,instr->result->scope_id));
                                break;
                            case TYPE_BOOL:
                                fprintf(stderr,"Cannot perform increment unary on boolean\n");
                                exit(1);
                            case TYPE_STRING:
                                fprintf(stderr,"Cannot perform increment unary on string\n");
                                exit(1);
                            case TYPE_REF:
                                fprintf(fp,"    mov rax, [rbp - %d]\n"
                                           "    inc rax\n"
                                           "    mov [rbp - %d],rax\n",get_offset(slist,instr->arg1->val.sval,instr->arg1->scope_id),get_offset(slist,instr->result->val.sval,instr->result->scope_id));
                                break;
                            case TYPE_PTR:
                                fprintf(fp,"    mov rax, [rbp - %d]\n"
                                           "    inc rax\n"
                                           "    mov [rbp - %d],rax\n",get_offset(slist,instr->arg1->val.sval,instr->arg1->scope_id),get_offset(slist,instr->result->val.sval,instr->result->scope_id));
                                break;
                            case TYPE_PARAM:
                            case TYPE_IDENTIFIER:
                                fprintf(stderr,"Performing increment on identifier\n");
                                fprintf(fp,"    mov rax, [rbp - %d]\n"
                                           "    inc rax\n"
                                           "    mov [rbp - %d],rax\n",get_offset(slist,instr->arg1->val.sval,instr->arg1->scope_id),get_offset(slist,instr->result->val.sval,instr->result->scope_id));
                                break;
                            case TYPE_FLOAT:
                                fprintf(fp,
                                    "    movsd xmm0, QWORD [rbp-%d]\n"
                                    "    mov    rax, 0x3ff0000000000000\n"
                                    "    movq   xmm1, rax\n"
                                    "    addsd  xmm0, xmm1\n"
                                    "    movsd  QWORD [rbp-%d], xmm0\n",get_offset(slist, instr->arg1->val.sval,instr->arg1->scope_id),get_offset(slist, instr->result->val.sval,instr->result->scope_id));
                                break;               
                            default:
                                fprintf(stderr,"Unary ops for this type not implemented, got `%d`\n",instr->arg1->acquired_type);
                                exit(1);             
                        }
                    }else if(check_in_global(instr->arg1->val.sval,slist)){
                        switch(instr->arg1->acquired_type){
                            case TYPE_BOOL:{
                                fprintf(stderr,"Cannot perform increment on boolean\n");
                                exit(1);
                            }
                            case TYPE_STRING: {
                                fprintf(stderr, "Cannot perform increment on string\n");
                                exit(1);
                            }
                            case TYPE_INT:{
                                char label[64];
                                mangleGlobal(label,instr->arg1->val.sval);
                                fprintf(fp,"    mov rax, [%s]\n"
                                           "    inc rax\n"
                                           "    mov [rbp - %d],rax\n",label,get_offset(slist,instr->result->val.sval,instr->result->scope_id));
                                break;
                            }
                            case TYPE_CHAR:{
                                char label[64];
                                mangleGlobal(label,instr->arg1->val.sval);
                                fprintf(fp,"    mov rax, [%s]\n"
                                           "    inc rax\n"
                                           "    mov [rbp - %d],rax\n",label,get_offset(slist,instr->result->val.sval,instr->result->scope_id));
                                break;
                            }
                            case TYPE_FLOAT:{
                                char label[64];
                                mangleGlobal(label,instr->arg1->val.sval);
                                fprintf(fp,
                                "    movsd xmm0, QWORD [%s]\n"
                                "    mov rax,0x3ff0000000000000\n"
                                "    movq xmm1,rax\n"
                                "    addsd xmm0,xmm1\n"
                                "    movsd QWORD [rbp - %d],xmm0\n",label,get_offset(slist,instr->result->val.sval,instr->result->scope_id));
                                break;
                            }
                            case TYPE_PARAM:
                            case TYPE_IDENTIFIER:{
                                char label[64];
                                mangleGlobal(label,instr->arg1->val.sval);
                                fprintf(stderr,"Performing increment on indentifier\n");
                                fprintf(fp,"    mov rax, [%s]\n"
                                           "    inc rax\n"
                                           "    mov [rbp - %d],rax\n",label,get_offset(slist,instr->result->val.sval,instr->result->scope_id));
                                break;
                            }
                            default:{
                                fprintf(stderr,"%s %d Unary ops for this type not implemented %d",__FILE__,__LINE__,instr->arg1->acquired_type);
                                break;
                            }
                        }                            
                    }else{
                        fprintf(stderr,"%s %d Identifier not found `%s`\n",__FILE__,__LINE__,instr->arg1->val.sval);
                        exit(1);
                    }
                }else if(strcmp(instr->relop->operator_str,"--") == 0){
                    if(get_offset(slist,instr->arg1->val.sval,instr->arg1->scope_id)){
                        switch(instr->arg1->acquired_type){
                            case TYPE_INT:
                                fprintf(fp,"    mov rax, [rbp - %d]\n"
                                           "    dec rax\n"
                                           "    mov [rbp - %d],rax\n",get_offset(slist,instr->arg1->val.sval,instr->arg1->scope_id),get_offset(slist,instr->result->val.sval,instr->result->scope_id));
                                break;
                            case TYPE_CHAR:
                                fprintf(fp,"    mov rax, [rbp - %d]\n"
                                           "    dec rax\n"
                                           "    mov [rbp - %d],rax",get_offset(slist,instr->arg1->val.sval,instr->arg1->scope_id),get_offset(slist,instr->result->val.sval,instr->result->scope_id));
                                break;
                            case TYPE_BOOL:
                                fprintf(stderr,"Cannot perform increment unary on boolean\n");
                                exit(1);
                            case TYPE_STRING:
                                fprintf(stderr,"Cannot perform increment unary on string\n");
                                exit(1);
                            case TYPE_REF:
                                fprintf(fp,"    mov rax, [rbp - %d]\n"
                                           "    dec rax\n"
                                           "    mov [rbp - %d],rax\n",get_offset(slist,instr->arg1->val.sval,instr->arg1->scope_id),get_offset(slist,instr->result->val.sval,instr->result->scope_id));
                                break;
                            case TYPE_PTR:
                                fprintf(fp,"    mov rax, [rbp - %d]\n"
                                           "    dec rax\n"
                                           "    mov [rbp - %d],rax\n",get_offset(slist,instr->arg1->val.sval,instr->arg1->scope_id),get_offset(slist,instr->result->val.sval,instr->result->scope_id));
                                break;
                            case TYPE_PARAM:
                            case TYPE_IDENTIFIER:
                                fprintf(stderr,"Performing increment on identifier");
                                fprintf(fp,"    mov rax, [rbp - %d]\n"
                                           "    dec rax\n"
                                           "    mov [rbp - %d],rax\n",get_offset(slist,instr->arg1->val.sval,instr->arg1->scope_id),get_offset(slist,instr->result->val.sval,instr->result->scope_id));
                                break;
                            case TYPE_FLOAT:
                                fprintf(fp,
                                    "    movsd xmm0, QWORD [rbp-%d]\n"
                                    "    mov    rax, 0x3ff0000000000000\n"
                                    "    movq   xmm1, rax\n"
                                    "    subsd  xmm0, xmm1\n"
                                    "    movsd  QWORD [rbp-%d], xmm0\n",get_offset(slist, instr->arg1->val.sval,instr->arg1->scope_id),get_offset(slist, instr->result->val.sval,instr->result->scope_id));
                                break;               
                            default:
                                fprintf(stderr,"Unary ops for this type not implemented\n");
                                exit(1);             
                        }
                    }else if(check_in_global(instr->arg1->val.sval,slist)){
                        switch(instr->arg1->acquired_type){
                            case TYPE_BOOL:{
                                fprintf(stderr,"Cannot perform decrement on boolean\n");
                                exit(1);
                            }
                            case TYPE_STRING: {
                                fprintf(stderr, "Cannot perform decrement on string\n");
                                exit(1);
                            }
                            case TYPE_INT:{
                                char label[64];
                                mangleGlobal(label,instr->arg1->val.sval);
                                fprintf(fp,"    mov rax, [%s]\n"
                                           "    dec rax\n"
                                           "    mov [rbp - %d],rax\n",label,get_offset(slist,instr->result->val.sval,instr->result->scope_id));
                                break;
                            }
                            case TYPE_CHAR:{
                                char label[64];
                                mangleGlobal(label,instr->arg1->val.sval);
                                fprintf(fp,"    mov rax, [%s]\n"
                                           "    dec rax\n"
                                           "    mov [rbp - %d],rax\n",label,get_offset(slist,instr->result->val.sval,instr->result->scope_id));
                                break;
                            }
                            case TYPE_FLOAT:{
                                char label[64];
                                mangleGlobal(label,instr->arg1->val.sval);
                                fprintf(fp,
                                "    movsd xmm0, QWORD [%s]\n"
                                "    mov rax,0x3ff0000000000000\n"
                                "    movq xmm1,rax\n"
                                "    subsd xmm0,xmm1\n"
                                "    movsd QWORD [rbp - %d],xmm0\n",label,get_offset(slist,instr->result->val.sval,instr->result->scope_id));
                                break;
                            }
                            case TYPE_PARAM:
                            case TYPE_IDENTIFIER:{
                                char label[64];
                                mangleGlobal(label,instr->arg1->val.sval);
                                fprintf(stderr,"Performing increment on indentifier\n");
                                fprintf(fp,"    mov rax, [%s]\n"
                                           "    dec rax\n"
                                           "    mov [rbp - %d],rax\n",label,get_offset(slist,instr->result->val.sval,instr->result->scope_id));
                                break;
                            }
                            default:{
                                fprintf(stderr,"%s %d Unary ops for this type not implemented %d",__FILE__,__LINE__,instr->arg1->acquired_type);
                                break;
                            }
                        }
                    }else{
                        fprintf(stderr,"%s %d Identifier not found `%s`\n",__FILE__,__LINE__,instr->arg1->val.sval);
                        exit(1);
                    }
                }
                else{
                    fprintf(stderr,"Unary ops not implemented\n");
                    exit(1);
                }
                break;
            }          
            default:
                break;
        }
        instr = instr->next;
    }
    list->head = instr;
    emitFuncFooter(fp);
}

static void emitMain(FILE* fp, SymbolTable* table, SymbolTableList* slist,TACList* list){
    emitMainHeader(fp,table->scope_name,table->total_offset);
    TACInstr* instr = list->head;
    int arg_call_norm_count = 0;
    int arg_call_float_count = 0;
    while(instr->op != TAC_MAIN_END){
        switch(instr->op){
            case TAC_ASSIGNDECL:{
                if(instr->arg1){
                    switch(instr->arg1->type){
                        case TYPE_INT:{
                            fprintf(fp,"    mov QWORD [rbp - %d], %d\n",get_offset(slist,instr->result->val.sval,instr->result->scope_id),instr->arg1->val.ival);
                            break;
                        }
                        case TYPE_FLOAT:{
                            fprintf(fp,"    mov rax, %s\n"
                                       "    movq xmm0, rax\n"
                                       "    movsd QWORD [rbp - %d], xmm0\n",double_to_hex(instr->arg1->val.fval), get_offset(slist,instr->result->val.sval,instr->result->scope_id));
                            break;
                        }
                        case TYPE_CHAR:{
                            fprintf(fp,"    mov QWORD [rbp - %d], \'%c\'\n",get_offset(slist,instr->result->val.sval,instr->result->scope_id),instr->arg1->val.cval);
                            break;
                        }
                        case TYPE_BOOL:{
                            fprintf(fp,"    mov QWORD [rbp - %d], %d\n",get_offset(slist,instr->result->val.sval,instr->result->scope_id),instr->arg1->val.bval == true ? 1 : 0);
                            break;
                        }
                        case TYPE_STRING:{
                            char* tmp_str = instr->arg1->val.sval;
                            int tmp_offset = get_offset(slist,instr->result->val.sval,instr->result->scope_id);
                            fprintf(fp,
                            "    lea rax, [rbp - %d]\n"
                            "    mov QWORD [rbp - %d], rax\n",tmp_offset-8,tmp_offset);
                            tmp_offset -= 8;
                            int i = 0;
                            char tmp_char = tmp_str[i];
                            while(tmp_char != '\0'){
                                if(tmp_char == '\\'){
                                    if(tmp_str[i+1] == '\0'){
                                        fprintf(stderr,"Cannot use single backslash in string, use `\\\\`\n");
                                        exit(1);
                                    }
                                    if(tmp_str[i+1] == 'n'){
                                        fprintf(fp,"    mov byte [rbp - %d], 0x0A\n",tmp_offset);
                                        i+=2;
                                        tmp_char = tmp_str[i];
                                        tmp_offset-=1;
                                    }else if(tmp_str[i+1] == 't'){
                                        fprintf(fp,"    mov byte [rbp - %d], 0x09\n",tmp_offset);
                                        i+=2;
                                        tmp_char = tmp_str[i];
                                        tmp_offset-=1;
                                    }else if(tmp_str[i+1] == 'r'){
                                        fprintf(fp,"    mov byte [rbp - %d], 0x0D\n",tmp_offset);
                                        i+=2;
                                        tmp_char = tmp_str[i];
                                        tmp_offset-=1;
                                    }else if(tmp_str[i+1] == '"'){
                                        fprintf(fp,"    mov byte [rbp - %d], 0x22\n",tmp_offset);
                                        i+=2;
                                        tmp_char = tmp_str[i];
                                        tmp_offset-=1;
                                    }else if(tmp_str[i+1] == '\''){
                                        fprintf(fp,"    mov byte [rbp - %d], 0x27\n",tmp_offset);
                                        i+=2;
                                        tmp_char = tmp_str[i];
                                        tmp_offset-=1;
                                    }else if(tmp_str[i+1] == '\\'){
                                        fprintf(fp,"    mov byte [rbp - %d], 0x5C\n",tmp_offset);
                                        i+=2;
                                        tmp_char = tmp_str[i];
                                        tmp_offset-=1;
                                    }else{
                                        fprintf(stderr,"Cannot use single backslash in a string, use `\\\\`\n");
                                        exit(1);
                                    }
                                }else{
                                    fprintf(fp,"    mov byte [rbp - %d], \'%c\'\n",tmp_offset,tmp_char);
                                    i++;
                                    tmp_char = tmp_str[i];
                                    tmp_offset-=1;
                                }
                            }
                            fprintf(fp,"    mov byte [rbp - %d], %d\n",tmp_offset,0);
                            break;
                        }
                        case TYPE_REF:{
                                fprintf(fp,"    mov rax, QWORD [rbp - %d]\n"
                                           "    mov QWORD [rbp - %d], rax\n",get_offset(slist,instr->arg1->val.sval,instr->arg1->scope_id),get_offset(slist,instr->result->val.sval,instr->result->scope_id));
                                break;
                            }
                        case TYPE_PTR:{
                                fprintf(fp,"    mov rax, QWORD [rbp - %d]\n"
                                           "    mov QWORD [rbp - %d], rax\n",get_offset(slist,instr->arg1->val.sval,instr->arg1->scope_id),get_offset(slist,instr->result->val.sval,instr->result->scope_id));
                                break;
                            }
                        case TYPE_IDENTIFIER:{
                            if(get_offset(slist,instr->arg1->val.sval,instr->arg1->scope_id)){
                                fprintf(fp,"    mov rax, QWORD [rbp - %d]\n"
                                           "    mov QWORD [rbp - %d], rax\n",get_offset(slist,instr->arg1->val.sval,instr->arg1->scope_id),get_offset(slist,instr->result->val.sval,instr->result->scope_id));
                            }else if(get_fromGlobal(fp,slist,instr,instr->arg1->val.sval)){
                            }else{
                                fprintf(stderr,"%s %d Identifier not found, got `%s`\n",__FILE__,__LINE__,instr->arg1->val.sval);
                                exit(1);
                            }
                            break;
                        }
                        default:{
                            break;
                        }
                    }
                }else{
                    fprintf(fp,"    mov QWORD [rbp - %d], %d\n",get_offset(slist,instr->result->val.sval,instr->result->scope_id),0);
                    break;
                }
                break;
            }

            case TAC_ASSIGN: {
                if(get_offset(slist,instr->result->val.sval,instr->result->scope_id)){
                    switch(instr->arg1->type){
                        case TYPE_INT: {
                            fprintf(fp,"    mov QWORD [rbp - %d], %d\n",get_offset(slist,instr->result->val.sval,instr->result->scope_id),instr->arg1->val.ival);
                            break;
                        }
                        case TYPE_FLOAT: {
                            fprintf(fp,"    mov rax, %s\n"
                                       "    movq xmm0, rax\n"
                                       "    movsd QWORD [rbp - %d], xmm0\n",double_to_hex(instr->arg1->val.fval), get_offset(slist,instr->result->val.sval,instr->result->scope_id));
                            break;
                        }
                        case TYPE_CHAR: {
                            fprintf(fp,"    mov QWORD [rbp - %d], \'%c\'",get_offset(slist,instr->result->val.sval,instr->result->scope_id),instr->arg1->val.cval);
                            break;
                        }
                        case TYPE_BOOL: {
                            fprintf(fp,"    mov QWORD [rbp - %d], %d\n",get_offset(slist,instr->result->val.sval,instr->result->scope_id),instr->arg1->val.bval == true ? 1: 0);
                            break;
                        }
                        case TYPE_REF : {
                            fprintf(fp,"    mov rax, QWORD [rbp - %d]\n"
                                       "    mov QWORD [rbp - %d], rax\n",get_offset(slist,instr->arg1->val.sval,instr->arg1->scope_id),get_offset(slist,instr->result->val.sval,instr->result->scope_id));
                            break;
                        }
                        case TYPE_PTR : {
                            fprintf(fp,"    mov rax, QWORD [rbp - %d]\n"
                                       "    mov QWORD [rbp - %d], rax\n",get_offset(slist,instr->arg1->val.sval,instr->arg1->scope_id),get_offset(slist,instr->result->val.sval,instr->result->scope_id));
                            break;
                        }
                        case TYPE_IDENTIFIER: {
                            if(get_offset(slist,instr->arg1->val.sval,instr->arg1->scope_id)){
                                fprintf(fp,"    mov rax, QWORD [rbp - %d]\n"
                                           "    mov QWORD [rbp - %d], rax\n",get_offset(slist,instr->arg1->val.sval,instr->arg1->scope_id),get_offset(slist,instr->result->val.sval,instr->result->scope_id));
                            }else if(check_in_global(instr->arg1->val.sval,slist)){
                                char label[64];
                                mangleGlobal(label,instr->arg1->val.sval);
                                fprintf(fp,"    mov rax, [%s]\n"
                                           "    mov QWORD [rbp - %d], rax\n", label,get_offset(slist,instr->result->val.sval,instr->result->scope_id));

                            }else{
                                fprintf(stderr,"Identifier not found, got `%s`\n",instr->arg1->val.sval);
                                exit(1);
                            }
                            break;
                        }
                        default:
                            break;
                    }
                }else if(check_in_global(instr->result->val.sval,slist)){
                    char cmp_label[64];
                    mangleGlobal(cmp_label,instr->result->val.sval);
                    SymbolTable* gtable = slist->tables[0];
                    for(int i = 0;i< gtable->symbol_count; i++){
                        char label[64]; 
                        mangleGlobal(label, gtable->entries[i]->name);
                        if(strcmp(label,cmp_label) == 0){
                            switch(instr->arg1->type){
                                case TYPE_INT:
                                    fprintf(fp,"    mov QWORD [%s], %d\n",label,instr->arg1->val.ival);
                                    break;
                                case TYPE_FLOAT:
                                    fprintf(fp,"    mov rax, %s\n"
                                               "    movq xmm0, rax\n"
                                               "    movsd QWORD [%s], xmm0\n",double_to_hex(instr->arg1->val.fval),label);
                                    break;
                                case TYPE_CHAR:
                                    fprintf(fp,"    mov QWORD [%s], \'%c\'\n",label,instr->arg1->val.cval);
                                    break;
                                case TYPE_BOOL:
                                    fprintf(fp,"    mov QWORD [%s], %d\n",label,instr->arg1->val.bval == true? 1 : 0);
                                    break;
                                case TYPE_REF:
                                    fprintf(fp,"    mov rax, QWORD [rbp - %d]\n"
                                               "    mov QWORD [%s], rax\n",get_offset(slist,instr->arg1->val.sval,instr->arg1->scope_id),label);
                                    break;
                                case TYPE_PTR:
                                    fprintf(fp,"    mov rax, QWORD [rbp - %d]\n"
                                               "    mov QWORD [%s],rax\n",get_offset(slist,instr->arg1->val.sval,instr->arg1->scope_id),label);
                                    break;
                                case TYPE_IDENTIFIER:
                                    if(get_offset(slist,instr->arg1->val.sval,instr->arg1->scope_id)){
                                        fprintf(fp,"    mov rax, QWORD [rbp - %d]\n"
                                                   "    mov QWORD [%s], rax\n",get_offset(slist,instr->arg1->val.sval,instr->arg1->scope_id),label);
                                        break;
                                    }else if(check_in_global(instr->arg1->val.sval,slist)){
                                        char cmp_label[64];
                                        mangleGlobal(cmp_label,instr->arg1->val.sval);
                                        fprintf(fp,"    mov rax, [%s]\n"
                                                   "    mov QWORD [%s], rax\n",cmp_label,label);
                                        break;
                                    }else{
                                        fprintf(stderr,"Unknown identifer, got `%s`\n",instr->arg1->val.sval);
                                        exit(1);
                                    }
                                case TYPE_STRING:
                                    fprintf(stderr,"Strings cannot be re assigned\n");
                                    exit(1);                              
                                default:
                                    fprintf(stderr, "Globals can only be int, float, string, char and bool");
                                    exit(1);

                            }
                        }
                    }
                }else{
                    fprintf(stderr,"Identifier not found, got `%s`\n",instr->result->val.sval);
                    exit(1);
                }
                break;
            }

            case TAC_ADDR_OF:{
                if(get_offset(slist,instr->arg1->val.sval,instr->arg1->scope_id)){
                    fprintf(fp,"    lea rax, QWORD [rbp - %d]\n"
                               "    mov QWORD [rbp - %d], rax\n",get_offset(slist,instr->arg1->val.sval,instr->arg1->scope_id),get_offset(slist,instr->result->val.sval,instr->result->scope_id));
                }else if(check_in_global(instr->arg1->val.sval,slist)){
                    char label[64];
                    mangleGlobal(label,instr->arg1->val.sval);
                    fprintf(fp, "    mov rax, %s\n"
                                "    mov QWORD [rbp - %d], rax\n", label,get_offset(slist,instr->result->val.sval,instr->result->scope_id));
                }else{
                    fprintf(stderr,"Identifier not found, got `%s`\n",instr->arg1->val.sval);
                    exit(1);
                }
                break;
            }

            case TAC_LOAD_PTR: {
                if(get_offset(slist,instr->arg1->val.sval,instr->arg1->scope_id)){
                    fprintf(fp,"    mov rax, QWORD [rbp - %d]\n"
                               "    mov rax, QWORD [rax]\n"
                               "    mov QWORD [rbp - %d], rax\n",get_offset(slist,instr->arg1->val.sval,instr->arg1->scope_id),get_offset(slist,instr->result->val.sval,instr->result->scope_id));
                }else if(check_in_global(instr->arg1->val.sval,slist)){
                    fprintf(stderr,"Cannot dereference global variables, Globals can be : int, float, char, string, bool\n");
                    exit(1);
                }else{
                    fprintf(stderr,"Identifier not found, got `%s`\n",instr->arg1->val.sval);
                    exit(1);
                }
                break;
            }

            case TAC_LABEL:{
                fprintf(fp,"    .%s:\n",instr->label);
                break;
            }

            case TAC_NOP: {
                break;
            }

            case TAC_GOTO: {
                fprintf(fp,"    jmp .%s\n",instr->label);
                break;
            }

            case TAC_IFGOTO: {
                if(strcmp(instr->relop->operator_str,"!=")==0){
                    if(instr->arg1->type == TYPE_IDENTIFIER){
                        fprintf(fp,"    mov rax, QWORD [rbp - %d]\n"
                                   "    cmp rax, %d\n"
                                   "    jne .%s\n",get_offset(slist,instr->arg1->val.sval,instr->arg1->scope_id),instr->arg2->val.ival,instr->label);
                    }else if(instr->arg1->type == TYPE_INT){
                        fprintf(fp,"    mov rax, %d\n"
                                   "    cmp rax, %d\n"
                                   "    jne .%s\n",instr->arg1->val.ival,instr->arg2->val.ival,instr->label);
                    }else if(instr->arg1->type == TYPE_BOOL){
                        fprintf(fp,"    mov rax, %d\n"
                                   "    cmp rax, %d\n"
                                   "    jne .%s\n",instr->arg1->val.bval == true ? 1 : 0,instr->arg2->val.ival,instr->label);
                    }
                }else if(strcmp(instr->relop->operator_str,"==") == 0){
                    //TODO will potentially error out in switch since arg1 can be int, char or an identifier
                    if(instr->arg2->type == TYPE_CHAR){
                        fprintf(fp,"    mov rax, QWORD [rbp - %d]\n"
                                   "    cmp rax, \'%c\'\n"
                                   "    je .%s\n",get_offset(slist,instr->arg1->val.sval,instr->arg1->scope_id),instr->arg2->val.cval,instr->label);
                    }else if(instr->arg2->type == TYPE_INT){
                        fprintf(fp,"    mov rax, QWORD [rbp - %d]\n"
                                   "    cmp rax, %d\n"
                                   "    je .%s\n",get_offset(slist,instr->arg1->val.sval,instr->arg1->scope_id),instr->arg2->val.ival,instr->label);
                    }
                }
                break;
            }

            case TAC_CALL: {
                if(arg_call_float_count > 0){
                    fprintf(fp,"    mov rax, %d\n",arg_call_float_count);
                }else{
                    fprintf(fp,"    xor rax,rax\n");
                }
                arg_call_norm_count = 0;
                arg_call_float_count = 0;
                fprintf(fp,"    call %s\n"
                           "    mov QWORD [rbp - %d],rax\n",instr->arg1->val.sval,get_offset(slist,instr->result->val.sval,instr->result->scope_id));
                break;
            }

            case TAC_UNOP: {
                if(strcmp(instr->relop->operator_str,"!") == 0){
                    if(get_offset(slist,instr->arg1->val.sval,instr->arg1->scope_id)){
                        switch(instr->arg1->acquired_type){
                            case TYPE_STRING:
                                fprintf(stderr,"Cannot perform logical not on string\n");
                                exit(1);
                                break;
                            case TYPE_INT:
                                fprintf(stderr,"Cannot perform logical not on integer\n");
                                exit(1);
                                break;
                            case TYPE_FLOAT:
                                fprintf(stderr,"Cannot perform logical not on float\n");
                                exit(1);
                                break;
                            case TYPE_CHAR:
                                fprintf(stderr,"Cannot perform logical not on char\n");
                                exit(1);
                            case TYPE_IDENTIFIER:
                                fprintf(stderr,"Performing logical not on identifier\n");
                                fprintf(fp,"    mov rax, [rbp - %d]\n"
                                           "    xor rax, 1\n"
                                           "    mov [rbp - %d], rax\n", get_offset(slist,instr->arg1->val.sval,instr->arg1->scope_id),get_offset(slist,instr->result->val.sval,instr->result->scope_id));
                                break;
                            case TYPE_PTR:
                                fprintf(stderr,"Performing logical not on dereference\n");
                                fprintf(fp,"    mov rax, [rbp - %d]\n"
                                           "    xor rax, 1\n"
                                           "    mov [rbp - %d], rax\n", get_offset(slist,instr->arg1->val.sval,instr->arg1->scope_id),get_offset(slist,instr->result->val.sval,instr->result->scope_id));
                                break;
                            case TYPE_BOOL:
                                fprintf(fp,"    mov rax, [rbp - %d]\n"
                                           "    xor rax, 1\n"
                                           "    mov [rbp - %d], rax\n", get_offset(slist,instr->arg1->val.sval,instr->arg1->scope_id),get_offset(slist,instr->result->val.sval,instr->result->scope_id));
                                break;
                            case TYPE_REF:
                                fprintf(stderr,"Cannot perform logical not on reference\n");
                                exit(1);
                            default:
                                fprintf(stderr,"Unary ops for this type not implemented `%d`\n",instr->arg1->acquired_type);
                                exit(1);
                        }
                    }else if(check_in_global(instr->arg1->val.sval,slist)){
                        switch(instr->arg1->acquired_type){
                            case TYPE_STRING:
                                fprintf(stderr,"Cannot perform logical not on string\n");
                                exit(1);
                                break;
                            case TYPE_INT:
                                fprintf(stderr,"Cannot perform logical not on integer\n");
                                exit(1);
                                break;
                            case TYPE_FLOAT:
                                fprintf(stderr,"Cannot perform logical not on floats\n");
                                exit(1);
                                break;
                            case TYPE_CHAR:
                                fprintf(stderr,"Cannot perform logical not on char\n");
                                exit(1);
                                break;
                            case TYPE_BOOL:{
                                char label[64];
                                mangleGlobal(label,instr->arg1->val.sval);
                                fprintf(fp,"    mov rax, [%s]\n"
                                           "    xor rax, 1\n"
                                           "    mov [rbp - %d],rax\n",label,get_offset(slist,instr->result->val.sval,instr->result->scope_id));
                                break;
                            }
                            case TYPE_IDENTIFIER:{
                                char label[64];
                                mangleGlobal(label,instr->arg1->val.sval);
                                fprintf(stderr,"Performing logical not on identifier\n");
                                fprintf(fp,"    mov rax, [%s]\n"
                                           "    xor rax, 1\n"
                                           "    mov [rbp - %d],rax\n",label,get_offset(slist,instr->result->val.sval,instr->result->scope_id));
                                break;
                            }
                            default:
                                fprintf(stderr,"Unary ops for this type not implemented `%d`\n",instr->arg1->acquired_type);
                                exit(1);
                        }
                    }else{
                        fprintf(stderr,"%s %d Identifier not found\n",__FILE__,__LINE__);
                        exit(1);
                    }
                }else if(strcmp(instr->relop->operator_str,"-") == 0){
                    if(get_offset(slist,instr->arg1->val.sval,instr->arg1->scope_id)){
                        switch(instr->arg1->acquired_type){
                            case TYPE_STRING:
                                fprintf(stderr,"Cannot perform unary ops on string\n");
                                exit(1);
                            case TYPE_INT:
                                fprintf(fp,"    mov rax,[rbp - %d]\n"
                                           "    neg rax\n"
                                           "    mov [rbp - %d],rax\n",get_offset(slist,instr->arg1->val.sval,instr->arg1->scope_id),get_offset(slist,instr->result->val.sval,instr->result->scope_id));
                                break;
                            case TYPE_CHAR:
                                fprintf(fp,"    mov rax, [rbp - %d]\n"
                                           "    neg rax\n"
                                           "    mov [rbp - %d],rax\n",get_offset(slist,instr->arg1->val.sval,instr->arg1->scope_id),get_offset(slist,instr->result->val.sval,instr->result->scope_id));
                                break;
                            case TYPE_FLOAT:
                                fprintf(fp,"    mov rax, 0xBFF0000000000000\n"
                                           "    movq    xmm1, rax\n"
                                           "    movsd   xmm0, QWORD [rbp-%d]\n"
                                           "    mulsd   xmm0, xmm1\n"
                                           "    movsd [rbp - %d],xmm0\n",get_offset(slist,instr->arg1->val.sval,instr->arg1->scope_id),get_offset(slist,instr->result->val.sval,instr->result->scope_id));
                                break;
                            case TYPE_BOOL:
                                fprintf(stderr,"Cannot perform negation on boolean\n");
                                exit(1);
                            case TYPE_REF:
                                fprintf(stderr,"Cannot perform negation on reference\n");
                                exit(1);
                            case TYPE_PTR:
                                fprintf(stderr,"Performing negation on dereference\n");
                                fprintf(fp,"    mov rax, [rbp - %d]\n"
                                           "    neg rax\n"
                                           "    mov [rbp - %d],rax\n",get_offset(slist,instr->arg1->val.sval,instr->arg1->scope_id),get_offset(slist,instr->result->val.sval,instr->result->scope_id));
                                break;
                            case TYPE_IDENTIFIER:
                                fprintf(stderr,"Performing negation on identifier\n");
                                fprintf(fp,"    mov rax, [rbp - %d]\n"
                                           "    neg rax\n"
                                           "    mov [rbp - %d],rax\n",get_offset(slist,instr->arg1->val.sval,instr->arg1->scope_id),get_offset(slist,instr->result->val.sval,instr->result->scope_id));
                                break;
                            default:
                                fprintf(stderr,"Unary ops for this type not implemented `%d`\n",instr->arg1->acquired_type);
                                exit(1);
                        }
                    }else if(check_in_global(instr->arg1->val.sval,slist)){
                        switch(instr->arg1->acquired_type){
                            case TYPE_STRING:
                                fprintf(stderr, "Cannot perform unary ops on string\n");
                                exit(1);
                                break;
                            case TYPE_BOOL:
                                fprintf(stderr,"Cannot perform negation on bool\n");
                                exit(1);
                                break;
                            case TYPE_REF:
                                fprintf(stderr,"Cannot perform negation on reference\n");
                                exit(1);
                                break;
                            case TYPE_INT:{
                                char label[64];
                                mangleGlobal(label,instr->arg1->val.sval);
                                fprintf(fp,"    mov rax, [%s]\n"
                                           "    neg rax\n"
                                           "    mov [rbp - %d],rax\n",label,get_offset(slist,instr->result->val.sval,instr->result->scope_id));
                                break;
                            }
                            case TYPE_CHAR: {
                                char label[64];
                                mangleGlobal(label,instr->arg1->val.sval);
                                fprintf(fp,"    mov rax, [%s]\n"
                                           "    neg rax\n"
                                           "    mov [rbp - %d], rax\n",label,get_offset(slist,instr->result->val.sval,instr->result->scope_id));
                                break;
                            }
                            case TYPE_FLOAT:{
                                char label[64];
                                mangleGlobal(label,instr->arg1->val.sval);
                                fprintf(fp,"    mov rax,0xBFF0000000000000\n"
                                           "    movq xmm1, rax\n"
                                           "    movsd xmm0, QWORD [%s]\n"
                                           "    mulsd xmm0,xmm1\n"
                                           "    movsd [rbp - %d],xmm0\n",label,get_offset(slist,instr->result->val.sval,instr->result->scope_id));
                                break;
                            }
                            case TYPE_IDENTIFIER:{
                                char label[64];
                                mangleGlobal(label,instr->arg1->val.sval);
                                fprintf(stderr,"Performing negation on identifier\n");
                                fprintf(fp,"    mov rax, [%s]\n"
                                           "    neg rax\n"
                                           "    mov [rbp - %d],rax\n",label,get_offset(slist,instr->result->val.sval,instr->result->scope_id));
                                break;
                            }
                            default:{
                                fprintf(stderr,"%s %d Negation for this type not implemented `%d`\n",__FILE__,__LINE__,instr->arg1->acquired_type);
                                break;
                            }

                        }
                    }else{
                        fprintf(stderr,"%s %d Identifier not found\n",__FILE__,__LINE__);
                        exit(1);
                    }
                }else if(strcmp(instr->relop->operator_str,"++") == 0){
                    if(get_offset(slist,instr->arg1->val.sval,instr->arg1->scope_id)){
                        switch(instr->arg1->acquired_type){
                            case TYPE_INT:
                                fprintf(fp,"    mov rax, [rbp - %d]\n"
                                           "    inc rax\n"
                                           "    mov [rbp - %d],rax\n",get_offset(slist,instr->arg1->val.sval,instr->arg1->scope_id),get_offset(slist,instr->result->val.sval,instr->result->scope_id));
                                break;
                            case TYPE_CHAR:
                                fprintf(fp,"    mov rax, [rbp - %d]\n"
                                           "    inc rax\n"
                                           "    mov [rbp - %d],rax\n",get_offset(slist,instr->arg1->val.sval,instr->arg1->scope_id),get_offset(slist,instr->result->val.sval,instr->result->scope_id));
                                break;
                            case TYPE_BOOL:
                                fprintf(stderr,"Cannot perform increment unary on boolean\n");
                                exit(1);
                            case TYPE_STRING:
                                fprintf(stderr,"Cannot perform increment unary on string\n");
                                exit(1);
                            case TYPE_REF:
                                fprintf(fp,"    mov rax, [rbp - %d]\n"
                                           "    inc rax\n"
                                           "    mov [rbp - %d],rax\n",get_offset(slist,instr->arg1->val.sval,instr->arg1->scope_id),get_offset(slist,instr->result->val.sval,instr->result->scope_id));
                                break;
                            case TYPE_PTR:
                                fprintf(fp,"    mov rax, [rbp - %d]\n"
                                           "    inc rax\n"
                                           "    mov [rbp - %d],rax\n",get_offset(slist,instr->arg1->val.sval,instr->arg1->scope_id),get_offset(slist,instr->result->val.sval,instr->result->scope_id));
                                break;
                            case TYPE_IDENTIFIER:
                                fprintf(stderr,"Performing increment on identifier\n");
                                fprintf(fp,"    mov rax, [rbp - %d]\n"
                                           "    inc rax\n"
                                           "    mov [rbp - %d],rax\n",get_offset(slist,instr->arg1->val.sval,instr->arg1->scope_id),get_offset(slist,instr->result->val.sval,instr->result->scope_id));
                                break;
                            case TYPE_FLOAT:
                                fprintf(fp,
                                    "    movsd xmm0, QWORD [rbp-%d]\n"
                                    "    mov    rax, 0x3ff0000000000000\n"
                                    "    movq   xmm1, rax\n"
                                    "    addsd  xmm0, xmm1\n"
                                    "    movsd  QWORD [rbp-%d], xmm0\n",get_offset(slist, instr->arg1->val.sval,instr->arg1->scope_id),get_offset(slist, instr->result->val.sval,instr->result->scope_id));
                                break;               
                            default:
                                fprintf(stderr,"Unary ops for this type not implemented\n");
                                exit(1);             
                        }
                    }else if(check_in_global(instr->arg1->val.sval,slist)){
                        switch(instr->arg1->acquired_type){
                            case TYPE_BOOL:{
                                fprintf(stderr,"Cannot perform increment on boolean\n");
                                exit(1);
                            }
                            case TYPE_STRING: {
                                fprintf(stderr, "Cannot perform increment on string\n");
                                exit(1);
                            }
                            case TYPE_INT:{
                                char label[64];
                                mangleGlobal(label,instr->arg1->val.sval);
                                fprintf(fp,"    mov rax, [%s]\n"
                                           "    inc rax\n"
                                           "    mov [rbp - %d],rax\n",label,get_offset(slist,instr->result->val.sval,instr->result->scope_id));
                                break;
                            }
                            case TYPE_CHAR:{
                                char label[64];
                                mangleGlobal(label,instr->arg1->val.sval);
                                fprintf(fp,"    mov rax, [%s]\n"
                                           "    inc rax\n"
                                           "    mov [rbp - %d],rax\n",label,get_offset(slist,instr->result->val.sval,instr->result->scope_id));
                                break;
                            }
                            case TYPE_FLOAT:{
                                char label[64];
                                mangleGlobal(label,instr->arg1->val.sval);
                                fprintf(fp,
                                "    movsd xmm0, QWORD [%s]\n"
                                "    mov rax,0x3ff0000000000000\n"
                                "    movq xmm1,rax\n"
                                "    addsd xmm0,xmm1\n"
                                "    movsd QWORD [rbp - %d],xmm0\n",label,get_offset(slist,instr->result->val.sval,instr->result->scope_id));
                                break;
                            }
                            case TYPE_IDENTIFIER:{
                                char label[64];
                                mangleGlobal(label,instr->arg1->val.sval);
                                fprintf(stderr,"Performing increment on indentifier\n");
                                fprintf(fp,"    mov rax, [%s]\n"
                                           "    inc rax\n"
                                           "    mov [rbp - %d],rax\n",label,get_offset(slist,instr->result->val.sval,instr->result->scope_id));
                                break;
                            }
                            default:{
                                fprintf(stderr,"%s %d Unary ops for this type not implemented %d",__FILE__,__LINE__,instr->arg1->acquired_type);
                                break;
                            }
                        }                            
                    }else{
                        fprintf(stderr,"%s %d Identifier not found `%s`\n",__FILE__,__LINE__,instr->arg1->val.sval);
                        exit(1);
                    }
                }else if(strcmp(instr->relop->operator_str,"--") == 0){
                    if(get_offset(slist,instr->arg1->val.sval,instr->arg1->scope_id)){
                        switch(instr->arg1->acquired_type){
                            case TYPE_INT:
                                fprintf(fp,"    mov rax, [rbp - %d]\n"
                                           "    dec rax\n"
                                           "    mov [rbp - %d],rax\n",get_offset(slist,instr->arg1->val.sval,instr->arg1->scope_id),get_offset(slist,instr->result->val.sval,instr->result->scope_id));
                                break;
                            case TYPE_CHAR:
                                fprintf(fp,"    mov rax, [rbp - %d]\n"
                                           "    dec rax\n"
                                           "    mov [rbp - %d],rax",get_offset(slist,instr->arg1->val.sval,instr->arg1->scope_id),get_offset(slist,instr->result->val.sval,instr->result->scope_id));
                                break;
                            case TYPE_BOOL:
                                fprintf(stderr,"Cannot perform increment unary on boolean\n");
                                exit(1);
                            case TYPE_STRING:
                                fprintf(stderr,"Cannot perform increment unary on string\n");
                                exit(1);
                            case TYPE_REF:
                                fprintf(fp,"    mov rax, [rbp - %d]\n"
                                           "    dec rax\n"
                                           "    mov [rbp - %d],rax\n",get_offset(slist,instr->arg1->val.sval,instr->arg1->scope_id),get_offset(slist,instr->result->val.sval,instr->result->scope_id));
                                break;
                            case TYPE_PTR:
                                fprintf(fp,"    mov rax, [rbp - %d]\n"
                                           "    dec rax\n"
                                           "    mov [rbp - %d],rax\n",get_offset(slist,instr->arg1->val.sval,instr->arg1->scope_id),get_offset(slist,instr->result->val.sval,instr->result->scope_id));
                                break;
                            case TYPE_IDENTIFIER:
                                fprintf(stderr,"Performing increment on identifier");
                                fprintf(fp,"    mov rax, [rbp - %d]\n"
                                           "    dec rax\n"
                                           "    mov [rbp - %d],rax\n",get_offset(slist,instr->arg1->val.sval,instr->arg1->scope_id),get_offset(slist,instr->result->val.sval,instr->result->scope_id));
                                break;
                            case TYPE_FLOAT:
                                fprintf(fp,
                                    "    movsd xmm0, QWORD [rbp-%d]\n"
                                    "    mov    rax, 0x3ff0000000000000\n"
                                    "    movq   xmm1, rax\n"
                                    "    subsd  xmm0, xmm1\n"
                                    "    movsd  QWORD [rbp-%d], xmm0\n",get_offset(slist, instr->arg1->val.sval,instr->arg1->scope_id),get_offset(slist, instr->result->val.sval,instr->result->scope_id));
                                break;               
                            default:
                                fprintf(stderr,"Unary ops for this type not implemented\n");
                                exit(1);             
                        }
                    }else if(check_in_global(instr->arg1->val.sval,slist)){
                        switch(instr->arg1->acquired_type){
                            case TYPE_BOOL:{
                                fprintf(stderr,"Cannot perform decrement on boolean\n");
                                exit(1);
                            }
                            case TYPE_STRING: {
                                fprintf(stderr, "Cannot perform decrement on string\n");
                                exit(1);
                            }
                            case TYPE_INT:{
                                char label[64];
                                mangleGlobal(label,instr->arg1->val.sval);
                                fprintf(fp,"    mov rax, [%s]\n"
                                           "    dec rax\n"
                                           "    mov [rbp - %d],rax\n",label,get_offset(slist,instr->result->val.sval,instr->result->scope_id));
                                break;
                            }
                            case TYPE_CHAR:{
                                char label[64];
                                mangleGlobal(label,instr->arg1->val.sval);
                                fprintf(fp,"    mov rax, [%s]\n"
                                           "    dec rax\n"
                                           "    mov [rbp - %d],rax\n",label,get_offset(slist,instr->result->val.sval,instr->result->scope_id));
                                break;
                            }
                            case TYPE_FLOAT:{
                                char label[64];
                                mangleGlobal(label,instr->arg1->val.sval);
                                fprintf(fp,
                                "    movsd xmm0, QWORD [%s]\n"
                                "    mov rax,0x3ff0000000000000\n"
                                "    movq xmm1,rax\n"
                                "    subsd xmm0,xmm1\n"
                                "    movsd QWORD [rbp - %d],xmm0\n",label,get_offset(slist,instr->result->val.sval,instr->result->scope_id));
                                break;
                            }
                            case TYPE_IDENTIFIER:{
                                char label[64];
                                mangleGlobal(label,instr->arg1->val.sval);
                                fprintf(stderr,"Performing increment on indentifier\n");
                                fprintf(fp,"    mov rax, [%s]\n"
                                           "    dec rax\n"
                                           "    mov [rbp - %d],rax\n",label,get_offset(slist,instr->result->val.sval,instr->result->scope_id));
                                break;
                            }
                            default:{
                                fprintf(stderr,"%s %d Unary ops for this type not implemented %d",__FILE__,__LINE__,instr->arg1->acquired_type);
                                break;
                            }
                        }
                    }else{
                        fprintf(stderr,"%s %d Identifier not found `%s`\n",__FILE__,__LINE__,instr->arg1->val.sval);
                        exit(1);
                    }
                }
                else{
                    fprintf(stderr,"Unary ops not implemented\n");
                    exit(1);
                }
                break;
            }          

            case TAC_ARG: {
                switch(instr->arg1->acquired_type){
                    case TYPE_INT:
                    case TYPE_CHAR:
                    case TYPE_STRING:
                    case TYPE_PTR:
                    case TYPE_REF:
                    case TYPE_IDENTIFIER:
                        switch(arg_call_norm_count){
                            case 0:
                                fprintf(fp,"    mov rdi, QWORD [rbp - %d]\n",get_offset(slist,instr->arg1->val.sval,instr->arg1->scope_id));
                                arg_call_norm_count++;
                                break;
                            case 1:
                                fprintf(fp,"    mov rsi, QWORD [rbp - %d]\n",get_offset(slist,instr->arg1->val.sval,instr->arg1->scope_id));
                                arg_call_norm_count++;
                                break;
                            case 2:
                                fprintf(fp,"    mov rdx, QWORD [rbp - %d]\n",get_offset(slist,instr->arg1->val.sval,instr->arg1->scope_id));
                                arg_call_norm_count++;
                                break;
                            case 3:
                                fprintf(fp,"    mov rcx, QWORD [rbp - %d]\n",get_offset(slist,instr->arg1->val.sval,instr->arg1->scope_id));
                                arg_call_norm_count++;
                                break;
                            case 4:
                                fprintf(fp,"    mov r8, QWORD [rbp - %d]\n",get_offset(slist,instr->arg1->val.sval,instr->arg1->scope_id));
                                arg_call_norm_count++;
                                break;
                            case 5:
                                fprintf(fp,"    mov r9, QWORD [rbp - %d]\n",get_offset(slist,instr->arg1->val.sval,instr->arg1->scope_id));
                                arg_call_norm_count++;
                                break;
                            default:
                                fprintf(stderr,"Cannot have more that 6 non-float arguments in a function\n");
                                exit(1);
                                break;
                        }
                        break;
                    case TYPE_FLOAT:
                        switch(arg_call_float_count){
                            case 0:
                                fprintf(fp,"    movq xmm0, QWORD [rbp - %d]\n",get_offset(slist,instr->arg1->val.sval,instr->arg1->scope_id));
                                arg_call_float_count++;
                                break;
                            case 1:
                                fprintf(fp,"    movq xmm1, QWORD [rbp - %d]\n",get_offset(slist,instr->arg1->val.sval,instr->arg1->scope_id));
                                arg_call_float_count++;
                                break;
                            case 2:
                                fprintf(fp,"    movq xmm2, QWORD [rbp - %d]\n",get_offset(slist,instr->arg1->val.sval,instr->arg1->scope_id));
                                arg_call_float_count++;
                                break;
                            case 3:
                                fprintf(fp,"    movq xmm3, QWORD [rbp - %d]\n",get_offset(slist,instr->arg1->val.sval,instr->arg1->scope_id));
                                arg_call_float_count++;
                                break;
                            case 4:
                                fprintf(fp,"    movq xmm4, QWORD [rbp - %d]\n",get_offset(slist,instr->arg1->val.sval,instr->arg1->scope_id));
                                arg_call_float_count++;
                                break;
                            case 5:
                                fprintf(fp,"    movq xmm5, QWORD [rbp - %d]\n",get_offset(slist,instr->arg1->val.sval,instr->arg1->scope_id));
                                arg_call_float_count++;
                                break;
                            case 6:
                                fprintf(fp,"    movq xmm6, QWORD [rbp - %d]\n",get_offset(slist,instr->arg1->val.sval,instr->arg1->scope_id));
                                arg_call_float_count++;
                                break;
                            case 7:
                                fprintf(fp,"    movq xmm7, QWORD [rbp - %d]\n",get_offset(slist,instr->arg1->val.sval,instr->arg1->scope_id));
                                arg_call_float_count++;
                                break;
                            default:
                                fprintf(stderr,"Cannot have more than 8 float arguments\n");
                                exit(1);
                                break;
                        }
                        break;
                    default:
                        fprintf(stderr,"Arg for current type not implemented, got `%d`\n",instr->arg1->acquired_type);
                        exit(1);
                        break;
                }
                break;
            }
            default:
                break;
        }
        instr = instr->next;

    }
    fputc('\n',fp);
    list->head = instr;
    emitMainFooter(fp);
}


static void emitFuncHeader(FILE *fp, char* table_name,int frameSize)
{
    fprintf(fp,
        "%s:\n"
        "    push rbp\n"
        "    mov  rbp, rsp\n"
        "    sub  rsp, %d\n",table_name, frameSize);
}


static void emitFuncFooter(FILE *fp)
{
    fputs(
        "    leave\n"
        "    ret\n\n", fp);
}

static void emitMainHeader(FILE *fp, char* table_name,int frameSize)
{
    fprintf(fp,
        "%s:\n"
        "    push rbp\n"
        "    mov  rbp, rsp\n"
        "    sub  rsp, %d\n",table_name, frameSize);
}

static void emitMainFooter(FILE *fp)
{
    fputs(
        "    xor rax, rax\n"
        "    leave\n"
        "    ret\n\n", fp);
}

char* double_to_hex(float value){
    static char buf[19];

    union { double d; uint64_t u; } conv = { .d = value };
    snprintf(buf, sizeof buf, "0x%016llx", (unsigned long long)conv.u);
    return buf;               
}