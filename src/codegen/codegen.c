#include "bl_ir.h"

static void mangleGlobal(char *out, const char *name);
// static void mangleLocal (char *out, const char* func_name, const char *name);


static void emitProlog(FILE *fp, SymbolTableList* slist,bl_arena* arena);
static void emitExterns(FILE* fp,SymbolTableList* slist,bl_arena* arena);
static void emitUndeclared(FILE* fp, SymbolTableList* slist, bl_arena* arena);
static void emitGlobals(FILE *fp, SymbolTableList* slist,bl_arena* arena);
static void emitFuncHeader(FILE *fp, char* table_name,int frameSize);
static void emitFuncFooter(FILE *fp);

void generateAssembly(const char* outfile, SymbolTableList* slist, TACList* list,bl_arena* arena);

int main(){
    char* filename = "src/codegen/one.bl";
    bl_arena* arena = (bl_arena*)malloc(sizeof(bl_arena));
    arena_init(arena);

    bl_ir* ir = bhaulang_ir(filename,arena);
    print_all_symbol_tables(ir->slist);
    tac_print(ir->list,arena);

    generateAssembly("src/codegen/out.asm",ir->slist,ir->list,arena);
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
    for(int i = 0;i<slist->table_count; i++){
        if(strcmp(slist->tables[i]->scope_name,"global") != 0){
            emitFuncHeader(fp,slist->tables[i]->scope_name,slist->tables[i]->total_offset);
            //TODO 
            emitFuncFooter(fp);
        }
    }
    emitEpilog(fp);
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
        "    xor rax, rax\n"
        "    leave\n"
        "    ret\n\n", fp);
}


