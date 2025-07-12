#include "bl_ir.h"

static void mangleGlobal(char *out, const char *name);
static int get_offset(SymbolTable* table,char* name);
static SymbolTable* symbol_table_values(SymbolTableList* slist, char* table_name,bl_arena* arena);
char* double_to_hex(float value);
static bool check_in_global(char* name,SymbolTableList* slist,bl_arena* arena);
// static void mangleLocal (char *out, const char* func_name, const char *name);


static void emitProlog(FILE *fp, SymbolTableList* slist,bl_arena* arena);
static void emitExterns(FILE* fp,SymbolTableList* slist,bl_arena* arena);
static void emitUndeclared(FILE* fp, SymbolTableList* slist, bl_arena* arena);
static void emitGlobals(FILE *fp, SymbolTableList* slist,bl_arena* arena);
static void emitFunction(FILE* fp,SymbolTable* table,TACList* instr);
static void emitMain(FILE* fp, SymbolTable* table, SymbolTableList* slist,TACList* instr,bl_arena* arena);
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
    print_all_symbol_tables(ir->slist);
    tac_print(ir->list,arena);

    generateAssembly("src/codegen/out.asm",ir->slist,ir->list,arena);
    arena_stats(arena);
}


static void mangleGlobal(char *out, const char *name){ 
    sprintf(out,"global_%s",name); 
}
// static void mangleLocal (char *out, const char* func_name, const char *name){ 
//     sprintf(out,"%s_%s",func_name,  name); 
// }


static void emitProlog(FILE *fp, SymbolTableList* slist,bl_arena* arena)
{
    fputs("SECTION .text\n" 
          "global  main\n", fp);
    emitExterns(fp,slist,arena);
}

static void emitEpilog(FILE* fp){
    fputs("SECTION .note.GNU-stack\n", fp);
}

void generateAssembly(const char* outfile, SymbolTableList* slist, TACList* list,bl_arena* arena){
    FILE *fp = fopen(outfile,"w");
    if (!fp) {fprintf(stderr,"Cannot open build file\n"); exit(1);}
    (void)list;
    emitGlobals(fp,slist,arena);
    emitUndeclared(fp,slist,arena);
    emitProlog(fp,slist,arena);
    for (TACInstr* instr = list->head; instr; instr = instr->next){
        if(instr->op == TAC_FUNC_BEGIN || instr->op == TAC_MAIN_BEGIN){
            switch(instr->op){
                case TAC_FUNC_BEGIN:{
                    SymbolTable* table = symbol_table_values(slist,instr->label,arena);
                    list->head = instr->next;
                    emitFunction(fp,table,list);
                    break;
                }
                case TAC_MAIN_BEGIN:{
                    SymbolTable* table = symbol_table_values(slist,instr->label,arena);
                    list->head = instr;
                    emitMain(fp,table,slist,list,arena);
                    break;
                }
                default:
                    break;
            }
        }
    }
    emitEpilog(fp);
}

static bool check_in_global(char* name,SymbolTableList* slist,bl_arena* arena){
    char cmp_label[64];
    mangleGlobal(cmp_label,name);
    SymbolTable* gtable = (SymbolTable*)arena_alloc(arena,sizeof(SymbolTable));
    for(int i = 0; i< slist->table_count; i++){
        if(strcmp(slist->tables[i]->scope_name,"global") == 0){
            gtable = slist->tables[i];
        }
    }
    for(int i = 0;i< gtable->symbol_count; i++){
        char label[64]; 
        mangleGlobal(label, gtable->entries[i]->name);
        if(strcmp(label,cmp_label) == 0){
            return 1;
        }
    }
    return 0;
}

//WARN currently not in use due to constant propagation
static bool get_fromGlobal(FILE* fp,SymbolTableList* slist,SymbolTable* table,TACInstr* instr,char* name,bl_arena* arena){
    char cmp_label[64];
    mangleGlobal(cmp_label,name);
    SymbolTable* gtable = (SymbolTable*)arena_alloc(arena,sizeof(SymbolTable));
    for(int i = 0; i< slist->table_count; i++){
        if(strcmp(slist->tables[i]->scope_name,"global") == 0){
            gtable = slist->tables[i];
        }
    }
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
                               "    mov QWORD [rbp - %d], rax\n", label,get_offset(table,instr->result->val.sval));
                    return 1;
                case TYPE_STRING:
                    fprintf(fp,"    mov rax, %s\n"
                               "    mov QWORD [rbp - %d], rax\n",label,get_offset(table,instr->result->val.sval));
                    return 1;
                
                default:
                    fprintf(stderr, "Globals can only be int, float, string, char and bool");
                    exit(1);

            }
        }
    }
    return 0;
}

static void emitGlobals(FILE *fp, SymbolTableList* slist,bl_arena* arena){
    fputs("SECTION .data\n", fp);
    SymbolTable* table = (SymbolTable*)arena_alloc(arena,sizeof(SymbolTable));
    for(int i = 0; i< slist->table_count; i++){
        if(strcmp(slist->tables[i]->scope_name,"global") == 0){
            table = slist->tables[i];
        }
    }
    for(int i = 0;i<table->symbol_count;i++){
        //WARN variable length is limited to 64 characters

        switch(table->entries[i]->type){
            case TYPE_INT : {
                char label[64];  
                mangleGlobal(label, table->entries[i]->name);
                fprintf(fp,"%-20s %s ", label, "dq");
                fprintf(fp,"%d",table->entries[i]->value.ival);
                fputc('\n',fp);
                break;
            }
            case TYPE_FLOAT : {
                char label[64];  
                mangleGlobal(label, table->entries[i]->name);
                fprintf(fp,"%-20s %s ", label, "dq");
                fprintf(fp,"%.16f",table->entries[i]->value.fval);
                fputc('\n',fp);
                break;
            }            
            case TYPE_CHAR : {
                char label[64];  
                mangleGlobal(label, table->entries[i]->name);
                fprintf(fp,"%-20s %s ", label, "dq");
                fprintf(fp,"\'%c\'",table->entries[i]->value.cval);
                fputc('\n',fp);
                break;
            }            
            case TYPE_STRING : {
                char label[64];  
                mangleGlobal(label, table->entries[i]->name);
                fprintf(fp,"%-20s %s ", label, "dq");
                fprintf(fp,"\"%s\",0",table->entries[i]->value.sval);
                fputc('\n',fp);
                break;
            }            
            case TYPE_BOOL : {
                char label[64];  
                mangleGlobal(label, table->entries[i]->name);
                fprintf(fp,"%-20s %s ", label, "dq");
                fprintf(fp,"%d",table->entries[i]->value.bval == true ? 1 : 0);
                fputc('\n',fp);
                break;
            }            
            default: 
                break;
        }
    }
    fputc('\n',fp);
}

static void emitExterns(FILE* fp,SymbolTableList* slist,bl_arena* arena){
    SymbolTable* table = (SymbolTable*)arena_alloc(arena,sizeof(SymbolTable));
    for(int i = 0; i< slist->table_count; i++){
        if(strcmp(slist->tables[i]->scope_name,"global") == 0){
            table = slist->tables[i];
        }
    }
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

static void emitUndeclared(FILE* fp, SymbolTableList* slist, bl_arena* arena){
    SymbolTable* table = (SymbolTable*)arena_alloc(arena,sizeof(SymbolTable));
    for(int i = 0; i< slist->table_count; i++){
        if(strcmp(slist->tables[i]->scope_name,"global") == 0){
            table = slist->tables[i];
        }
    }
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


static int get_offset(SymbolTable* table,char* name){
    for(int i = 0;i<table->symbol_count;i++){
        if(strcmp(table->entries[i]->name, name) == 0){
            return table->entries[i]->offset;
        }
    }
    return 0;
}




static SymbolTable* symbol_table_values(SymbolTableList* slist, char* table_name,bl_arena* arena){
    SymbolTable* table = (SymbolTable*)arena_alloc(arena,sizeof(SymbolTable));
    for(int i = 0; i< slist->table_count;i++){
        if(strcmp(slist->tables[i]->scope_name,table_name) == 0){
            table = slist->tables[i];
        }
    }
    return table;
}



static void emitFunction(FILE* fp, SymbolTable* table, TACList* list){
    emitFuncHeader(fp,table->scope_name,table->total_offset);
    //TODO define function body
    TACInstr* instr = list->head;
    while(instr->op != TAC_FUNC_END){
        instr = instr->next;
    }
    list->head = instr;
    emitFuncFooter(fp);
}

static void emitMain(FILE* fp, SymbolTable* table, SymbolTableList* slist,TACList* list,bl_arena* arena){
    emitMainHeader(fp,table->scope_name,table->total_offset);
    TACInstr* instr = list->head;
    while(instr->op != TAC_MAIN_END){
        switch(instr->op){
            case TAC_ASSIGNDECL:{
                if(instr->arg1){
                    switch(instr->arg1->type){
                        case TYPE_INT:{
                            fprintf(fp,"    mov QWORD [rbp - %d], %d\n",get_offset(table,instr->result->val.sval),instr->arg1->val.ival);
                            break;
                        }
                        case TYPE_FLOAT:{
                            fprintf(fp,"    mov rax, %s\n"
                                       "    movq xmm0, rax\n"
                                       "    movsd QWORD [rbp - %d], xmm0\n",double_to_hex(instr->arg1->val.fval), get_offset(table,instr->result->val.sval));
                            break;
                        }
                        case TYPE_CHAR:{
                            fprintf(fp,"    mov QWORD [rbp - %d], \'%c\'\n",get_offset(table,instr->result->val.sval),instr->arg1->val.cval);
                            break;
                        }
                        case TYPE_BOOL:{
                            fprintf(fp,"    mov QWORD [rbp - %d], %d\n",get_offset(table,instr->result->val.sval),instr->arg1->val.bval == true ? 1 : 0);
                            break;
                        }
                        case TYPE_STRING:{
                            char* tmp_str = instr->arg1->val.sval;
                            int tmp_offset = get_offset(table,instr->result->val.sval);
                            int i = 0;
                            char tmp_char = tmp_str[i];
                            while(tmp_char != '\0'){
                                //TODO if \, check next character (n,r,t,",',\) and merge them into one character
                                if(tmp_char == '\\'){
                                    fprintf(fp,"    mov byte [rbp - %d], 0x0A\n",tmp_offset);
                                    i++;
                                    tmp_char = tmp_str[i];
                                    tmp_offset-=1;
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
                                           "    mov QWORD [rbp - %d], rax\n",get_offset(table,instr->arg1->val.sval),get_offset(table,instr->result->val.sval));
                                break;
                            }
                        case TYPE_PTR:{
                                fprintf(fp,"    mov rax, QWORD [rbp - %d]\n"
                                           "    mov QWORD [rbp - %d], rax\n",get_offset(table,instr->arg1->val.sval),get_offset(table,instr->result->val.sval));
                                break;
                            }
                        case TYPE_IDENTIFIER:{
                            if(get_offset(table,instr->arg1->val.sval)){
                                fprintf(fp,"    mov rax, QWORD [rbp - %d]\n"
                                           "    mov QWORD [rbp - %d], rax\n",get_offset(table,instr->arg1->val.sval),get_offset(table,instr->result->val.sval));
                            }else if(get_fromGlobal(fp,slist,table,instr,instr->arg1->val.sval,arena)){

                            }else{
                                fprintf(stderr,"Identifier not found\n");
                                exit(1);
                            }
                            break;
                        }
                        default:{
                            break;
                        }
                    }
                }else{
                    fprintf(fp,"    mov QWORD [rbp - %d], %d\n",get_offset(table,instr->result->val.sval),0);
                    break;
                }
                break;
            }

            case TAC_ASSIGN: {
                if(get_offset(table,instr->result->val.sval)){
                    switch(instr->arg1->type){
                        case TYPE_INT: {
                            fprintf(fp,"    mov QWORD [rbp - %d], %d\n",get_offset(table,instr->result->val.sval),instr->arg1->val.ival);
                            break;
                        }
                        case TYPE_FLOAT: {
                            fprintf(fp,"    mov rax, %s\n"
                                       "    movq xmm0, rax\n"
                                       "    movsd QWORD [rbp - %d], xmm0\n",double_to_hex(instr->arg1->val.fval), get_offset(table,instr->result->val.sval));
                            break;
                        }
                        case TYPE_CHAR: {
                            fprintf(fp,"    mov QWORD [rbp - %d], \'%c\'",get_offset(table,instr->result->val.sval),instr->arg1->val.cval);
                            break;
                        }
                        case TYPE_BOOL: {
                            fprintf(fp,"    mov QWORD [rbp - %d], %d\n",get_offset(table,instr->result->val.sval),instr->arg1->val.bval == true ? 1: 0);
                            break;
                        }
                        case TYPE_REF : {
                            fprintf(fp,"    mov rax, QWORD [rbp - %d]\n"
                                       "    mov QWORD [rbp - %d], rax\n",get_offset(table,instr->arg1->val.sval),get_offset(table,instr->result->val.sval));
                            break;
                        }
                        case TYPE_PTR : {
                            fprintf(fp,"    mov rax, QWORD [rbp - %d]\n"
                                       "    mov QWORD [rbp - %d], rax\n",get_offset(table,instr->arg1->val.sval),get_offset(table,instr->result->val.sval));
                            break;
                        }
                        case TYPE_IDENTIFIER: {
                            if(get_offset(table,instr->arg1->val.sval)){
                                fprintf(fp,"    mov rax, QWORD [rbp - %d]\n"
                                           "    mov QWORD [rbp - %d], rax\n",get_offset(table,instr->arg1->val.sval),get_offset(table,instr->result->val.sval));
                            }else if(check_in_global(instr->arg1->val.sval,slist,arena)){
                                char label[64];
                                mangleGlobal(label,instr->arg1->val.sval);
                                fprintf(fp,"    mov rax, [%s]\n"
                                           "    mov QWORD [rbp - %d], rax\n", label,get_offset(table,instr->result->val.sval));

                            }else{
                                fprintf(stderr,"Identifier not found, got `%s`\n",instr->arg1->val.sval);
                                exit(1);
                            }
                            break;
                        }
                        default:
                            break;
                    }
                }else if(check_in_global(instr->result->val.sval,slist,arena)){
                    char cmp_label[64];
                    mangleGlobal(cmp_label,instr->result->val.sval);
                    SymbolTable* gtable = (SymbolTable*)arena_alloc(arena,sizeof(SymbolTable));
                    for(int i = 0; i< slist->table_count; i++){
                        if(strcmp(slist->tables[i]->scope_name,"global") == 0){
                            gtable = slist->tables[i];
                        }
                    }
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
                                               "    mov QWORD [%s], rax\n",get_offset(table,instr->arg1->val.sval),label);
                                    break;
                                case TYPE_PTR:
                                    fprintf(fp,"    mov rax, QWORD [rbp - %d]\n"
                                               "    mov QWORD [%s],rax\n",get_offset(table,instr->arg1->val.sval),label);
                                    break;
                                case TYPE_IDENTIFIER:
                                    if(get_offset(table,instr->arg1->val.sval)){
                                        fprintf(fp,"    mov rax, QWORD [rbp - %d]\n"
                                                   "    mov QWORD [%s], rax\n",get_offset(table,instr->arg1->val.sval),label);
                                        break;
                                    }else if(check_in_global(instr->arg1->val.sval,slist,arena)){
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
                if(get_offset(table,instr->arg1->val.sval)){
                    fprintf(fp,"    lea rax, QWORD [rbp - %d]\n"
                               "    mov QWORD [rbp - %d], rax\n",get_offset(table,instr->arg1->val.sval),get_offset(table,instr->result->val.sval));
                }else if(check_in_global(instr->arg1->val.sval,slist,arena)){

                    char label[64];
                    mangleGlobal(label,instr->arg1->val.sval);
                    fprintf(fp, "    mov rax, %s\n"
                                "    mov QWORD [rbp - %d], rax\n", label,get_offset(table,instr->result->val.sval));
                }else{
                    fprintf(stderr,"Identifier not found, got `%s`\n",instr->arg1->val.sval);
                    exit(1);
                }
                break;
            }

            case TAC_LOAD_PTR: {
                if(get_offset(table,instr->arg1->val.sval)){
                    fprintf(fp,"    mov rax, QWORD [rbp - %d]\n"
                               "    mov rax, QWORD [rax]\n"
                               "    mov QWORD [rbp - %d], rax\n",get_offset(table,instr->arg1->val.sval),get_offset(table,instr->result->val.sval));
                }else if(check_in_global(instr->arg1->val.sval,slist,arena)){
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
                    printf("hello\n");
                    if(instr->arg1->type == TYPE_IDENTIFIER){
                        fprintf(fp,"    mov rax, QWORD [rbp - %d]\n"
                                   "    cmp rax, %d\n"
                                   "    jne .%s\n",get_offset(table,instr->arg1->val.sval),instr->arg2->val.ival,instr->label);
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
                    if(instr->arg2->type == TYPE_CHAR){
                        fprintf(fp,"    mov rax, QWORD [rbp - %d]\n"
                                   "    cmp rax, \'%c\'\n"
                                   "    je .%s\n",get_offset(table,instr->arg1->val.sval),instr->arg2->val.cval,instr->label);
                    }else if(instr->arg2->type == TYPE_INT){
                        fprintf(fp,"    mov rax, QWORD [rbp - %d]\n"
                                   "    cmp rax, %d\n"
                                   "    je .%s\n",get_offset(table,instr->arg1->val.sval),instr->arg2->val.ival,instr->label);
                    }
                }
                break;
            }

            case TAC_CALL: {
                fprintf(fp,"    call %s\n"
                           "    mov QWORD [rbp - %d],rax\n",instr->arg1->val.sval,get_offset(table,instr->result->val.sval));
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