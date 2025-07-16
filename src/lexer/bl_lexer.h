#ifndef INCLUDE_BL_LEXER_H
#define INCLUDE_BL_LEXER_H

#include "bl_tokenizer.h"
#include "bl_langkeywords.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define STRBUF_SZ 256

//REF Define max amount of your custom keywords here
#define MAX_KEYWORDS_LEN 3
// #define BL_POSTPROCESS_TEST

static inline bl_token* bl_postprocess_token_list(bl_token* arr,bl_arena* arena);
static inline bl_token* bl_postprocess_identifiers(bl_token* arr,bl_token* temp_arr,bl_arena* arena);
static inline bl_token* bhaulang_lexer(char* filename,bl_arena* arena);
static inline void reduce_identifiers(bl_token* arr, bl_token* temp_arr,bl_arena* arena);


#ifdef BL_POSTPROCESS_TEST


int main(int argc, char** argv){
    if(argc != 2){
        fprintf(stderr, "Usage : ./prog <input_file>\n");
        exit(1);
    }
    bl_arena* arena = (bl_arena*)malloc(sizeof(bl_arena));
    arena_init(arena);

    bl_token* arr = bhaulang_lexer(argv[argc-1],arena);
    bl_token_list_print(arr,(size_t)dynarray_length(arr));

    return 0;
}

#endif

static inline bl_token* bhaulang_lexer(char* filename,bl_arena* arena){
    bl_token* arr = dynarray_create_arena(bl_token,arena);
    arr = bl_tokenize_file(filename,arena);
    arr = bl_postprocess_token_list(arr,arena);
    return arr;
}


static inline bl_token* bl_postprocess_token_list(bl_token* arr,bl_arena *arena){

    bl_token* temp_arr = bl_token_list_filter(arena,arr,dynarray_length(arr),BL_IDENTIFIER);
    bl_token* new_arr = bl_postprocess_identifiers(arr,temp_arr,arena);

    return new_arr;
}

static inline bl_token* bl_postprocess_identifiers(bl_token* arr,bl_token* temp_arr,bl_arena* arena){

    reduce_identifiers(arr,temp_arr,arena);

    bl_token* cleaned_arr = dynarray_create_arena(bl_token,arena);

    for(int i = 0; i < (int)dynarray_length(arr); i++){
        if(arr[i].token != -1){
            dynarray_push(cleaned_arr,arr[i],bl_token);
        }
    }

    dynarray_destroy(arr);
    return cleaned_arr;
}

void reduce_identifiers(bl_token *arr, bl_token *temp_arr,bl_arena *arena)
{
    int i = 0;
    int kw = 0;
    while (i < (int)dynarray_length(temp_arr))
    {
        int keyword_len = MAX_KEYWORDS_LEN;
        char **bufs = (char **)arena_alloc(arena,keyword_len * sizeof(char *));
        while (keyword_len > 0)
        {
            if(i+keyword_len > (int)dynarray_length(temp_arr)){
                while(i+keyword_len > (int)dynarray_length(temp_arr)){
                    keyword_len--;
                    }
                }
            

            for (int j = 0; j < keyword_len; j++)
            {
                bufs[j] = (char *)arena_alloc(arena,STRBUF_SZ);
            }

            char string_buf[256] = {0};
            if ((temp_arr[i].token != -1))
            {
                if ((i) <= (int)dynarray_length(temp_arr))
                {
                    char **strings = (char **)arena_alloc(arena,keyword_len * sizeof(char *));
                    for (int j = 0; j < keyword_len; j++)
                    {
                        strings[j] = bl_token_get_str(temp_arr[i + j], bufs[j]);
                    }
                    for (int j = 0; j < keyword_len; j++)
                    {
                        strncat(string_buf, strings[j], STRBUF_SZ - strlen(string_buf) - 1);
                        if (j < (keyword_len - 1))
                        {
                            strncat(string_buf, " ", STRBUF_SZ - strlen(string_buf) - 1);
                        }
                    }



                    kw = get_keyword_type(string_buf);
                    if (kw != -1)
                    {
                        temp_arr[i].token = kw;
                        temp_arr[i].where_lastchar = temp_arr[i + keyword_len - 1].where_lastchar;
                        for (int j = 1; j < keyword_len; j++)
                        {
                            temp_arr[i + j].token = -1;
                        }
                        for (int k = 0; k < (int)dynarray_length(arr); k++)
                        {
                            if ((temp_arr[i].loc.line_number == arr[k].loc.line_number) && (temp_arr[i].loc.line_offset == arr[k].loc.line_offset))
                            {
                                bl_token *ptr = &arr[k];
                                ptr->token = temp_arr[i].token;
                                int kw_length = 0;
                                for (int j = 1; j < keyword_len; j++)
                                {
                                    kw_length += (temp_arr[i + j].string_len + 1);
                                }
                                ptr->string_len = temp_arr[i].string_len + kw_length;
                                ptr->where_lastchar = temp_arr[i].where_lastchar;
                                ptr->loc.line_offset = temp_arr[i + keyword_len - 1].loc.line_offset;
                                ptr->loc.line_number = temp_arr[i + keyword_len - 1].loc.line_number;

                                for (int j = 1; j < keyword_len; j++)
                                {
                                    ptr = &arr[k + j];
                                    ptr->token = -1;
                                }
                            }
                        }
                    }
                }
                else
                {
                    if ((i + 1) < (int)dynarray_length(temp_arr))
                    {
                        char **strings = (char **)arena_alloc(arena,2 * sizeof(char *));
                        for (int j = 0; j < 2; j++)
                        {
                            strings[j] = bl_token_get_str(temp_arr[i + j], bufs[j]);
                        }

                        for (int j = 0; j < 2; j++)
                        {
                            strncat(string_buf, strings[j], STRBUF_SZ - strlen(string_buf) - 1);
                            if (j < 1)
                            {
                                strncat(string_buf, " ", STRBUF_SZ - strlen(string_buf) - 1);
                            }
                        }


                        int kw = get_keyword_type(string_buf);
                        if (kw != -1)
                        {
                            temp_arr[i].token = kw;
                            temp_arr[i].where_lastchar = temp_arr[i + 1].where_lastchar;

                            temp_arr[i + 1].token = -1;

                            for (int j = 0; j < (int)dynarray_length(arr); j++)
                            {
                                if ((temp_arr[i].loc.line_number == arr[j].loc.line_number) && (temp_arr[i].loc.line_offset == arr[j].loc.line_offset))
                                {
                                    bl_token *ptr = &arr[j];
                                    ptr->token = temp_arr[i].token;
                                    ptr->string_len = temp_arr[i].string_len + temp_arr[i + 1].string_len + 1;
                                    ptr->where_lastchar = temp_arr[i + 1].where_lastchar;
                                    ptr->loc.line_offset = temp_arr[i + 1].loc.line_offset;
                                    ptr->loc.line_number = temp_arr[i + 1].loc.line_number;

                                    ptr = &arr[j + 1];
                                    ptr->token = -1;
                                }
                            }
                        }
                    }
                    break;
                }
            }
            keyword_len--;
        }// while (keyword_len > 0) end
        i++;
    } // while (i < (size_t)dynarray_length(temp_arr)) end;

}


#endif //INCLUDE_BL_LEXER_Hn