#include "bl_codegen.h"


int main(int argc, char** argv){
    if(argc != 3){
        fprintf(stderr, "Usage : ./<prog> <input bhaulang file> <output asm>\n");
        exit(1);
    }else{
        bhaulang_compiler(argv[argc-2],argv[argc-1]);
    }
    return 0;
}