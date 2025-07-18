#ifndef BL_KEYWORDS_CUSTOM_LOADER_H
#define BL_KEYWORDS_CUSTOM_LOADER_H

#include "bl_langkeywords.h"

// #define BL_CUSTOM_LOADER_TEST

extern char* keywords_arr[20];

const char* keys_in_order[20] = {
    "assign", 
    "if", 
    "elseif", 
    "else", 
    "while", 
    "func", 
    "return",
    "entry", 
    "exit", 
    "switch", 
    "case", 
    "break", 
    "continue", 
    "default",
    "true", 
    "false", 
    "extern", 
    "main", 
    "ptr", 
    "ref"
};



char* trim(char* str);
char* extract_string(const char** p);

void load_custom_keywords(char* json_path);

#ifdef BL_CUSTOM_LOADER_TEST

int main(int argc, char** argv){

    if(argc < 2){
        fprintf("Usage : ./prog <input-json-file>\n");
        exit(1);
    }

    load_custom_keywords(argv[argc-1]);
    return 0;
}

#endif



char* trim(char* str) {
    while (isspace((unsigned char)*str)) str++;
    if (*str == 0) return str;

    char* end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) end--;

    *(end + 1) = '\0';
    return str;
}

char* extract_string(const char** p) {
    while (**p && **p != '\"') (*p)++;
    if (**p != '\"') return NULL;

    (*p)++; 
    const char* start = *p;

    while (**p && **p != '\"') (*p)++;
    if (**p != '\"') return NULL;

    int len = *p - start;
    char* out = malloc(len + 1);
    strncpy(out, start, len);
    out[len] = '\0';

    (*p)++; 
    return out;
}

void load_custom_keywords(char* json_path){
    printf("%s\n",json_path);
    FILE* f = fopen(json_path, "r");
    if (!f) {
        fprintf(stderr, "Failed to open custom keyword file: %s\n", json_path);
        exit(1);
    }
    fseek(f, 0, SEEK_END);
    long len = ftell(f);
    fseek(f, 0, SEEK_SET);

    char* json = malloc(len + 1);
    fread(json, 1, len, f);
    json[len] = '\0';
    fclose(f);

    const char* p = json;

    while (*p) {
        char* key = extract_string(&p);
        if (!key) break;

        while (*p && *p != ':') p++;
        if (*p == ':') p++;

        char* value = extract_string(&p);
    
        if (!value) {
            free(key);
            break;
        }

        #ifdef BL_CUSTOM_LOADER_TEST

        printf("%s : %s\n",key,value);

        #endif

        for (int i = 0; i < 20; i++) {
            if (strcmp(keys_in_order[i], value) == 0) {
                keywords_arr[i] = key;
                free(value); 
                key = NULL;
                break;
            }
        }

        if (key) free(key);
        
    }
}

#endif 