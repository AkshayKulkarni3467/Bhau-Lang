#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "bl_codegen.h"
#include "bl_custom_loader.h"

/*
WARN language does not support function overloading :0
WARN Cannot perform function-in-function call, since the register allocation resets when a function is completely called; check src/codegen/bl_codegen.h for more
WARN if using dynarray_create_arena(..) from src/common/bl_dynarray.h, allocate a proper chunk of arena in src/common/bl_arena.h in which the entire dynarray can fit
WARN Need modify src/keywords/bl_langkeywords.h if KEYWORD_TYPES is modified in src/lexer/bl_tokenizer; Currently, BL_EOF is 303
WARN Maximum text file size is set to 256 KB, can be updated in src/lexer/bl_tokenizer.h:line:26
WARN Postfix operations and escape characters not implemented
WARN variable length is limited to 64 characters, can be updated in src/codegen/bl_codegen.h
WARN using `system` in bl_compiler.c, exploitable command :)
REF  The files found under src care header only files, and can be tested by defining BL_<FILENAME>_TEST, and changing the extension to <filename>.c
*/


void cleanup_cache();
void run_or_exit(const char* cmd);

int main(int argc, char** argv){

    if (argc < 2) {
        fprintf(stderr, "Usage:\n");
        fprintf(stderr, "  blc [-asm] <source.bl> [--keywords=path.json]\n");
        return 1;
    }

    int generate_asm_only = 0;
    char* input_file = NULL;
    char* custom_keywords_path = NULL;

    mkdir("__blcache__", 0777);

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-asm") == 0) {
            generate_asm_only = 1;
        } else if (strncmp(argv[i], "--keywords=", 11) == 0) {
            custom_keywords_path = argv[i] + 11;
        } else {
            input_file = argv[i];
        }
    }

    if (!input_file) {
        cleanup_cache();
        fprintf(stderr, "Error: No input file provided\n");
        return 1;
    }
    
    if(custom_keywords_path){
        load_custom_keywords(custom_keywords_path);
    }

    bhaulang_compiler(input_file,"__blcache__/out.asm");

    char* slash = strrchr(input_file, '/');
    char* base = slash ? slash + 1 : input_file;

    char* temp = strdup(base);
    char* dot = strrchr(temp, '.');
    if (dot) *dot = '\0';

    char cmd_out[512];
    if (generate_asm_only) {
        char outname[256];
        snprintf(outname, sizeof(outname), "%s.asm", temp);
        snprintf(cmd_out, sizeof(cmd_out), "cp __blcache__/out.asm \"%s\"", outname);
        run_or_exit(cmd_out);
        cleanup_cache();
        return 0;
    }
    run_or_exit("nasm -f elf64 -o __blcache__/out.o __blcache__/out.asm");

    char execname[256];
    snprintf(execname, sizeof(execname), "%s", temp);
    snprintf(cmd_out, sizeof(cmd_out), "gcc -no-pie -ggdb -o \"%s\" __blcache__/out.o", execname);
    run_or_exit(cmd_out);

    free(temp);
    cleanup_cache();
    return 0;
}

void cleanup_cache(){
    system("rm -rf __blcache__");
}

void run_or_exit(const char* cmd) {
    int code = system(cmd);
    if (code != 0) {
        fprintf(stderr, "Command failed: %s\n", cmd);
        cleanup_cache();
        exit(1);
    }
}