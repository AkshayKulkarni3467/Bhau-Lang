#ifndef INCLUDE_BL_LEXER_H
#define INCLUDE_BL_LEXER_H

#include "bl_tokenizer.h"
#include "bl_langkeywords.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define STRBUF_SZ (1 << 6)
// #define BL_POSTPROCESS_TEST

static inline bl_token* bl_postprocess_token_list(bl_token* arr);
static inline bl_token* bl_postprocess_identifiers(bl_token* arr,bl_token* temp_arr);
static inline bl_token* bhaulang_lexer(char* filename,bl_arena* arena);


#ifdef BL_POSTPROCESS_TEST

int main(){
    bl_arena* arena = (bl_arena*)malloc(sizeof(bl_arena));
    arena_init(arena);

    bl_token* arr = bhaulang_lexer("src/lexer/one.bl",arena);
    bl_token_list_print(arr,(size_t)dynarray_length(arr));

    return 0;
}

#endif

static inline bl_token* bhaulang_lexer(char* filename,bl_arena* arena){
    bl_token* arr = dynarray_create(bl_token);
    arr = bl_tokenize_file(filename,arena);
    arr = bl_postprocess_token_list(arr);
    return arr;
}


static inline bl_token* bl_postprocess_token_list(bl_token* arr){

    bl_token* temp_arr = bl_token_list_filter(arr,dynarray_length(arr),BL_IDENTIFIER);
    bl_token* new_arr = bl_postprocess_identifiers(arr,temp_arr);

    return new_arr;
}

static inline bl_token* bl_postprocess_identifiers(bl_token* arr,bl_token* temp_arr){

    int i = 0;
    int kw = 0;

    char *buf1 = malloc(STRBUF_SZ);
    char *buf2 = malloc(STRBUF_SZ);
    char *buf3 = malloc(STRBUF_SZ);
    char *string_buf = malloc(STRBUF_SZ);

    while(i < (size_t)dynarray_length(temp_arr)){
        
        if(temp_arr[i].token != -1){

            buf1 = (char *)malloc(sizeof(1<<6));
            buf2 = (char *)malloc(sizeof(1<<6));
            buf3 = (char *)malloc(sizeof(1<<6));

            string_buf = (char *)malloc(sizeof(1<<6));

            if((i+2) <= ((int)dynarray_length(temp_arr)-1)){
                char* string1 = bl_token_get_str(temp_arr[i],buf1);
                char* string2 = bl_token_get_str(temp_arr[i+1],buf2);
                char* string3 = bl_token_get_str(temp_arr[i+2],buf3);

                
                snprintf(string_buf,1<<6,"%.*s %.*s %.*s",
                    (int)strlen(string1),string1,
                    (int)strlen(string2),string2,
                    (int)strlen(string3),string3);
                
                
                kw = get_keyword_type(string_buf);

              
                if(kw != -1){
                    temp_arr[i].token = kw;
                    temp_arr[i].where_lastchar = temp_arr[i+2].where_lastchar;

                    temp_arr[i+1].token = -1;
                    temp_arr[i+2].token = -1;

                    for(int j = 0; j<dynarray_length(arr);j++){
                        if((temp_arr[i].loc.line_number == arr[j].loc.line_number) && (temp_arr[i].loc.line_offset == arr[j].loc.line_offset)){
                            bl_token *ptr = &arr[j];
                            ptr->token = temp_arr[i].token;
                            ptr->string_len = temp_arr[i].string_len + temp_arr[i+1].string_len +temp_arr[i+2].string_len + 2;
                            ptr->where_lastchar = temp_arr[i].where_lastchar;
                            ptr->loc.line_offset = temp_arr[i+2].loc.line_offset;
                            ptr->loc.line_number = temp_arr[i+2].loc.line_number;

                            ptr = &arr[j+1];
                            ptr->token = -1;

                            ptr = &arr[j+2];
                            ptr->token = -1;
                        }
                    }


                }else{
                    snprintf(string_buf,1<<6,"%.*s %.*s",
                        (int)strlen(string1),string1,
                        (int)strlen(string2),string2);


                    kw = get_keyword_type(string_buf);

                    
                    if(kw != -1){
                        temp_arr[i].token = kw;
                        temp_arr[i].where_lastchar = temp_arr[i+1].where_lastchar;
                        temp_arr[i+1].token = -1;

                        for(int j = 0; j<dynarray_length(arr);j++){
                            if((temp_arr[i].loc.line_number == arr[j].loc.line_number) && (temp_arr[i].loc.line_offset == arr[j].loc.line_offset)){
                                bl_token *ptr = &arr[j];
                                ptr->token = temp_arr[i].token;
                                ptr->string_len = temp_arr[i].string_len + temp_arr[i+1].string_len + 1;
                                ptr->where_lastchar = temp_arr[i].where_lastchar;
                                ptr->loc.line_offset = temp_arr[i+1].loc.line_offset;
                                ptr->loc.line_number = temp_arr[i+1].loc.line_number;

                                ptr = &arr[j+1];
                                ptr->token = -1;
                            }
                        }
                    }
                }
            }else{
                if ((i+1) < dynarray_length(temp_arr)) {
                    char* string1 = bl_token_get_str(temp_arr[i],buf1);
                    char* string2 = bl_token_get_str(temp_arr[i+1],buf2);

                    snprintf(string_buf,1<<6,"%.*s %.*s",
                        (int)strlen(string1),string1,
                        (int)strlen(string2),string2);
                    
                    int kw = get_keyword_type(string_buf);
                    if(kw != -1){
                        temp_arr[i].token = kw;
                        temp_arr[i].where_lastchar = temp_arr[i+1].where_lastchar;


                        temp_arr[i+1].token = -1;

                        for(int j = 0; j<dynarray_length(arr);j++){
                            if((temp_arr[i].loc.line_number == arr[j].loc.line_number) && (temp_arr[i].loc.line_offset == arr[j].loc.line_offset)){
                                bl_token *ptr = &arr[j];
                                ptr->token = temp_arr[i].token;
                                ptr->string_len = temp_arr[i].string_len + temp_arr[i+1].string_len + 1;
                                ptr->where_lastchar = temp_arr[i+1].where_lastchar;
                                ptr->loc.line_offset = temp_arr[i+1].loc.line_offset;
                                ptr->loc.line_number = temp_arr[i+1].loc.line_number;

                                ptr = &arr[j+1];
                                ptr->token = -1;
                            }
                        }
                    }

                    break;
                }
            } 
        }
        i++;
    }
    free(buf1);
    free(buf2);
    free(buf3);
    free(string_buf);

    bl_token* cleaned_arr = dynarray_create(bl_token);

    for(int i = 0; i < dynarray_length(arr); i++){
        if(arr[i].token != -1){
            dynarray_push(cleaned_arr,arr[i],bl_token);
        }
    }

    dynarray_destroy(arr);
    return cleaned_arr;
}

#endif //INCLUDE_BL_LEXER_H