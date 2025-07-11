#include "bl_ir.h"

static void mangleGlobal(char *out, const char *name);
// static void mangleLocal (char *out, const char* func_name, const char *name);


static void emitProlog(FILE *fp);
static void emitGlobals(FILE *fp, SymbolTableList* slist,bl_arena* arena);
static void emitFuncHeader(FILE *fp, char* table_name,int frameSize);
static void emitFuncFooter(FILE *fp);

void generateAssembly(const char* outfile, SymbolTableList* slist, TACList* list,bl_arena* arena);

int main(){
    char* filename = "src/codegen/one.bl";
    bl_arena* arena = (bl_arena*)malloc(sizeof(bl_arena));
    arena_init(arena);

    bl_ir* ir = bhaulang_ir(filename,arena);

    generateAssembly("src/codegen/out.asm",ir->slist,ir->list,arena);
}


static void mangleGlobal(char *out, const char *name){ 
    sprintf(out,"global_%s",name); 
}
// static void mangleLocal (char *out, const char* func_name, const char *name){ 
//     sprintf(out,"%s_%s",func_name,  name); 
// }


static void emitProlog(FILE *fp)
{
    fputs("SECTION .text\n"
            "   global  main\n", fp);
}

static void emitEpilog(FILE* fp){
    fputs(
        "SECTION .bss\n"
        "SECTION .note.GNU-stack\n", fp);
}

void generateAssembly(const char* outfile, SymbolTableList* slist, TACList* list,bl_arena* arena){
    FILE *fp = fopen(outfile,"w");
    if (!fp) {fprintf(stderr,"Cannot open build file\n"); exit(1);}
    (void)list;
    emitGlobals(fp,slist,arena);
    emitProlog(fp);
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
        char label[64];  
        mangleGlobal(label, table->entries[i]->name);
        fprintf(fp,"%-20s %s ", label, "dq");
        switch(table->entries[i]->type){
            case TYPE_INT : fprintf(fp,"%d",table->entries[i]->value.ival); break;
            case TYPE_FLOAT : fprintf(fp, "%.16f", table->entries[i]->value.fval); break;
            case TYPE_CHAR : fprintf(fp,"\'%c\'",table->entries[i]->value.cval); break;
            case TYPE_BOOL : fprintf(fp, "%d", table->entries[i]->value.bval == true ? 1:0); break;
            case TYPE_STRING : fprintf(fp,"\"%s\",0",table->entries[i]->value.sval); break;
            default: break;
        }
        fputc('\n',fp);
    }
    fputc('\n',fp);
}


static void emitFuncHeader(FILE *fp, char* table_name,int frameSize)
{
    fprintf(fp,
        "   %s:\n"
        "       push rbp\n"
        "       mov  rbp, rsp\n"
        "       sub  rsp, %d\n",table_name, frameSize);
}

static void emitFuncFooter(FILE *fp)
{
    fputs(
        "       xor rax, rax\n"
        "       leave\n"
        "       ret\n\n", fp);
}


