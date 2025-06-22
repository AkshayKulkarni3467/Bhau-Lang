// #ifndef INCLUDE_BL_LEXER_H
// #define INCLUDE_BL_LEXER_H

#define BHAU_LANG
// maybe bhai lang, bro lang later

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dynarray.h"

enum KEYWORD_TYPES {
   BL_IDENTIFIER = 0,
   BL_EOF,
   BL_SEMICOLON,
   BL_EQUAL,
   BL_ISEQUALCOND,
   BL_INT,
   BL_FLOAT,
   BL_LPAREN,
   BL_RPAREN,
   BL_LBRACE,
   BL_RBRACE,
   BL_LBRACK,
   BL_RBRACK,
   BL_COMMA,
   BL_STRING,
};


typedef struct
{
   char *where_firstchar;
   char *where_lastchar;
   long token;
   double real_number;
   long   int_number;
   char *string;
   int string_len;
} bl_token;

typedef struct
{
   char *input_stream;
   char *eof;
   char *parse_point;
   char *string_storage;
   int   string_storage_len;
} bl_lexer;

typedef struct
{
   int line_number;
   int line_offset;
} bl_location;

int is_alpha(char c) {
    return (c >= 'A' && c <= 'Z') ||
           (c >= 'a' && c <= 'z');
}

int is_alnum_or_underscore_or_dollar(char c) {
    return is_alpha(c) || (c >= '0' && c <= '9') || c == '_' || c == '$';
}
/*
Initializes the lexer
*/
void bl_lexer_init(bl_lexer *lexer, const char *input_stream, const char *input_stream_end, char *string_store, int store_length){
   lexer->input_stream = (char *)input_stream;
   lexer->parse_point = (char *)input_stream;
   lexer->eof = (char *)input_stream_end;
   lexer->string_storage = string_store;
   lexer->string_storage_len = store_length;
}


char bl_peek_token(bl_lexer *l,int num){
   return l->input_stream[l->parse_point - l->input_stream + num];
}

bl_token *bl_tokenize(bl_lexer *lexer){
   char* character = &(lexer->input_stream[lexer->parse_point - lexer->input_stream]);
   bl_token *tok = malloc(sizeof(bl_token));
   if (*character && *character && (is_alpha(*character) || *character == '_'))
   {
      tok->where_firstchar = lexer->parse_point;
      tok->string = lexer->parse_point;
      lexer->parse_point+=1;
      while(*character && is_alnum_or_underscore_or_dollar(*character)){
         character = &(lexer->input_stream[lexer->parse_point - lexer->input_stream]);
         lexer->parse_point+=1;

      }
      lexer->parse_point-=1;
      tok->token = BL_IDENTIFIER;
      tok->real_number = 0;
      tok->int_number = 0;
      tok->where_lastchar = lexer->parse_point;
   }else if
   (*character && (*character >= '0' && *character <= '9'))
   {
      tok->where_firstchar = lexer->parse_point;
      tok->string = tok->where_firstchar;
      while(*character && (
         (*character >= '0' && *character <= '9')
      )){
         character = &(lexer->input_stream[lexer->parse_point - lexer->input_stream]);
         lexer->parse_point+=1;
      }
      lexer->parse_point-=1;
      if(*(lexer->parse_point) == '.'){
         lexer->parse_point+=1;
         character = &(lexer->input_stream[lexer->parse_point - lexer->input_stream]);
         while(*character && (*character >= '0' && *character <= '9')){
            character = &(lexer->input_stream[lexer->parse_point - lexer->input_stream]);
            lexer->parse_point+=1;
         }
         lexer->parse_point-=1;
         tok->where_lastchar = lexer->parse_point;
         tok->token = BL_FLOAT;
         tok->int_number = 0;
         tok->real_number = 0;
         tok->string = tok->where_firstchar;

      }else{
         tok->where_lastchar = lexer->parse_point;
         printf("%c",*(tok->where_lastchar));
         tok->token = BL_INT;
         tok->int_number = 0;
         tok->real_number = 0;  
      }      
   }else if 
   (*character && *character == '"')
   {
      tok->where_firstchar = lexer->parse_point;  // points to opening quote
      lexer->parse_point++;  // skip the opening quote
      char *start = lexer->parse_point;

      // Collect until closing quote or EOF
      while (lexer->parse_point < lexer->eof && *lexer->parse_point != '"') {
         character = &(lexer->input_stream[lexer->parse_point - lexer->input_stream]);
         lexer->parse_point++;
      }
      lexer->parse_point+=1;
      tok->where_lastchar = lexer->parse_point;
      tok->int_number = 0;
      tok->real_number = 0;
      tok->string = tok->where_firstchar;
      tok->token = BL_STRING;
   }else if
   (*character && *character == '\'')
   {
      tok->where_firstchar = lexer->parse_point;
      lexer->parse_point+=3;
      character = &(lexer->input_stream[lexer->parse_point - lexer->input_stream]);
      tok->int_number = 0;
      tok->real_number = 0;
      tok->where_lastchar = lexer->parse_point;
      tok->string = tok->where_firstchar;
   }
   else if 
   (*character && *character == ';')
   {
      tok->where_firstchar = lexer->parse_point;
      lexer->parse_point+=1;
      character = &(lexer->input_stream[lexer->parse_point - lexer->input_stream]);
      tok->where_lastchar = lexer->parse_point;
      tok->token = BL_SEMICOLON;
      tok->string = tok->where_firstchar;
      tok->int_number = 0;
      tok->real_number = 0;
   }
   else if(*character && *character == '{')
   {
      tok->where_firstchar = lexer->parse_point;
      lexer->parse_point+=1;
      character = &(lexer->input_stream[lexer->parse_point - lexer->input_stream]);
      tok->where_lastchar = lexer->parse_point;
      tok->token = BL_LBRACE;
      tok->string = tok->where_firstchar;
      tok->int_number = 0;
      tok->real_number = 0;
   }
   else if(*character && *character == '}')
   {
      tok->where_firstchar = lexer->parse_point;
      lexer->parse_point+=1;
      character = &(lexer->input_stream[lexer->parse_point - lexer->input_stream]);
      tok->where_lastchar = lexer->parse_point;
      tok->token = BL_RBRACE;
      tok->string = tok->where_firstchar;
      tok->int_number = 0;
      tok->real_number = 0;
   }
   else if(*character && *character == '[')
   {
      tok->where_firstchar = lexer->parse_point;
      lexer->parse_point+=1;
      character = &(lexer->input_stream[lexer->parse_point - lexer->input_stream]);
      tok->where_lastchar = lexer->parse_point;
      tok->token = BL_LBRACK;
      tok->string = tok->where_firstchar;
      tok->int_number = 0;
      tok->real_number = 0;
   }
   else if(*character && *character == ']')
   {
      tok->where_firstchar = lexer->parse_point;
      lexer->parse_point+=1;
      character = &(lexer->input_stream[lexer->parse_point - lexer->input_stream]);
      tok->where_lastchar = lexer->parse_point;
      tok->token = BL_RBRACK;
      tok->string = tok->where_firstchar;
      tok->int_number = 0;
      tok->real_number = 0;
   }
   else if(*character && *character == '(')
   {
      tok->where_firstchar = lexer->parse_point;
      lexer->parse_point+=1;
      character = &(lexer->input_stream[lexer->parse_point - lexer->input_stream]);
      tok->where_lastchar = lexer->parse_point;
      tok->token = BL_LPAREN;
      tok->string = tok->where_firstchar;
      tok->int_number = 0;
      tok->real_number = 0;
   }
   else if(*character && *character == ')')
   {
      tok->where_firstchar = lexer->parse_point;
      lexer->parse_point+=1;
      character = &(lexer->input_stream[lexer->parse_point - lexer->input_stream]);
      tok->where_lastchar = lexer->parse_point;
      tok->token = BL_RPAREN;
      tok->string = tok->where_firstchar;
      tok->int_number = 0;
      tok->real_number = 0;
   }
   else if(*character && *character == ',')
   {
      tok->where_firstchar = lexer->parse_point;
      lexer->parse_point+=1;
      character = &(lexer->input_stream[lexer->parse_point - lexer->input_stream]);
      tok->where_lastchar = lexer->parse_point;
      tok->token = BL_COMMA;
      tok->string = tok->where_firstchar;
      tok->int_number = 0;
      tok->real_number = 0;
   }
   else if (*character && *character == '=')
   {
      char suff = bl_peek_token(lexer,1);
      if(suff != '=')
      {
         tok->where_firstchar = lexer->parse_point;
         lexer->parse_point+=1;
         character = &(lexer->input_stream[lexer->parse_point - lexer->input_stream]);
         tok->where_lastchar = lexer->parse_point;
         tok->token = BL_EQUAL;
         tok->string = tok->where_firstchar;
         tok->int_number = 0;
         tok->real_number = 0;
      }
      else
      {
         tok->where_firstchar = lexer->parse_point;
         lexer->parse_point+=2;
         character = &(lexer->input_stream[lexer->parse_point - lexer->input_stream]);
         tok->where_lastchar = lexer->parse_point;
         tok->token = BL_ISEQUALCOND;
         tok->string = tok->where_firstchar;
         tok->int_number = 0;
         tok->real_number = 0;
      }

   }
   else
   {
      tok->where_firstchar = lexer->parse_point;
      tok->where_lastchar = lexer->parse_point;
      character = &(lexer->input_stream[lexer->parse_point - lexer->input_stream]);
      tok->token = BL_EOF;
      tok->real_number = 0;
      tok->int_number = 0;
      tok->string = lexer->parse_point;
   }
   
   char* val = tok->where_firstchar;

   return tok;

}

void bl_remove_whitespace(bl_lexer *l){
   while(l->input_stream[l->parse_point - l->input_stream] == ' ' || l->input_stream[l->parse_point - l->input_stream] == '\n' || l->input_stream[l->parse_point - l->input_stream] == '\r'){
      l->parse_point++;
   }
}

void bl_next_step(bl_lexer *l){
   bl_remove_whitespace(l);

}

char *print_keyword(int num){
   if(num == 0){
      return "BL_IDENTIFIER";
   }else if(num == 1){
      return "BL_EOF";
   }else if(num == 2){
      return "BL_SEMICOLON";
   }else if(num == 3){
      return "BL_EQUAL";
   }else if(num == 4){
      return "BL_ISEQUALCOND";
   }else if(num == 5){
      return "BL_INT";
   }else if(num ==6){
      return "BL_FLOAT";
   }else{
      return "NOT_IMPLEMENTED";
   }
}

void print_token(bl_token* da, int i){
   bl_token tok = da[i];
   char *start = tok.where_firstchar;
   while(start < tok.where_lastchar){
      printf("%c",*start);
      start++;
   }
   printf(",        %s          KEYWORD",print_keyword((int)tok.token));
   printf("\n");

}

int main(){

   FILE *f = fopen("one.bl", "rb");
   char *text = (char*)malloc(1 << 20);
   int len = f ? fread(text, 1, 1<<20, f) : -1;

   bl_lexer l;
   bl_token *da = dynarray_create(bl_token);
   bl_token *tok;

   if (len < 0) {
      fprintf(stderr, "Error opening file\n");
      return 1;
   }
   fclose(f);

   char* string_store = (char *)malloc(1<<20);
   int string_store_len = 1<<20;
   bl_lexer_init(&l,text,text+len,string_store, string_store_len);
   do{
      tok = bl_tokenize(&l);
      bl_next_step(&l);
      dynarray_push(da,*tok);
   }while(tok->token != (long)BL_EOF);

   for(int i = 0; i < dynarray_length(da);i++){ 
      print_token(da,i);
      // printf("%d , %p\n",i,da[i].where_firstchar);
   }

}


// #endif