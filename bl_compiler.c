#include "bl_codegen.h"
#include "bl_custom_loader.h"


int main(int argc, char** argv){
    char* input_file = NULL;
    char* output_asm = NULL;
    char* custom_keywords_path = NULL;

    if(argc < 3){
        fprintf(stderr, "Usage : ./<prog> <input.bl> <output.asm> --keywords <json file>\n");
        exit(1);
    }

    for(int i = 1; i < argc; ++i){
        if(i == 1){
            input_file = argv[i];
        }
        if(i == 2){
            output_asm = argv[i];
        }
        if(strcmp(argv[i], "--keywords") == 0 && i + 1 < argc){
            custom_keywords_path = argv[i + 1];
            i++; 
        }
    }

    
    if(custom_keywords_path){
        load_custom_keywords(custom_keywords_path);
    }
    bhaulang_compiler(input_file,output_asm);
    return 0;
}