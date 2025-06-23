// #ifndef INCLUDE_BL_LEXER_H
// #define INCLUDE_BL_LEXER_H

#define BHAU_LANG
// maybe bhai lang, bro lang later

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dynarray.h"

/*for debugging*/
// #define BL_IDENTIFIERS
// #define BL_OPERATORS
// #define BL_SYMBOLS
/*---------------------*/

enum KEYWORD_TYPES {
   #ifndef BL_IDENTIFIERS
   BL_IDENTIFIER = 256,
   BL_EOF,
   BL_INT,
   BL_FLOAT,
   BL_STRING,
   BL_UNIMPLEMENTED,
   #endif

   #ifndef BL_OPERATORS
   BL_SEMICOLON,//symbol
   BL_EQUAL,//symbol
   BL_ISEQUALCOND,//symbol
   BL_LPAREN,//symbol
   BL_RPAREN,//symbol
   BL_LBRACE,//symbol
   BL_RBRACE,//symbol
   BL_LBRACK,//symbol
   BL_RBRACK,//symbol
   BL_COMMA,//symbol
   BL_NOT,//symbol
   BL_LESSTHAN,//symbol
   BL_GRTTHAN,//symbol
   BL_NOTEQ,//symbol
   BL_LESSEQ,//symbol
   BL_GRTEQ,//symbol
   BL_LOGAND,//symbol
   BL_LOGOR,//symbol
   #endif

   #ifndef BL_SYMBOLS
   BL_ADDBINOP,
   BL_SUBBINOP,
   BL_MULTBINOP,
   BL_DIVBINOP,
   BL_ADDEQ,
   BL_SUBEQ,
   BL_MULTEQ,
   BL_DIVEQ,
   BL_INC,
   BL_DEC,
   BL_LSHIFT,
   BL_RSHIFT,
   BL_AND,
   BL_OR,
   BL_XOR,
   BL_ANDEQ,
   BL_OREQ,
   BL_XOREQ,
   #endif
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

int is_whitespace(char character){
   return (character == ' ') || (character == '\n') || (character == '\r');
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
   int count = 1;
   int number = 1;
   char character;
   do{
      character = l->input_stream[l->parse_point - l->input_stream + number];
      while(is_whitespace(character)){
         character = l->input_stream[l->parse_point - l->input_stream + ++number];
      }
      count++;
      number++;
   }while(count <= num);
   return character;
}

//todo implement a reverse peek function

char bl_peek_prev_token(bl_lexer *l,int num){
   int count = 1;
   int number = 1;
   char character;
   do{
      character = l->input_stream[l->parse_point - l->input_stream - number];
      while(is_whitespace(character)){
         character = l->input_stream[l->parse_point - l->input_stream - ++number];
      }
      count++;
      number++;
      printf("%c ",character);
      printf("\n");
   }while(count<=num);
   return character;
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
   else if(!(*character)){
      tok->where_firstchar = lexer->parse_point;
      lexer->parse_point++;
      tok->where_lastchar = lexer->parse_point;
      character = &(lexer->input_stream[lexer->parse_point - lexer->input_stream]);
      tok->token = BL_EOF;
      tok->real_number = 0;
      tok->int_number = 0;
      tok->string = lexer->parse_point;
   }
   else if(*character == '+')
   {
      tok->where_firstchar = lexer->parse_point;
      char suff = bl_peek_token(lexer,1);
      if(suff == '='){
         lexer->parse_point+=2;
         tok->where_lastchar = lexer->parse_point;
         character = &(lexer->input_stream[lexer->parse_point - lexer->input_stream]);
         tok->token = BL_ADDEQ;
         tok->real_number = 0;
         tok->int_number = 0;
         tok->string = lexer->parse_point;
      }
      else if(suff == '+'){
         lexer->parse_point+=2;
         tok->where_lastchar = lexer->parse_point;
         character = &(lexer->input_stream[lexer->parse_point - lexer->input_stream]);
         tok->token = BL_INC;
         tok->real_number = 0;
         tok->int_number = 0;
         tok->string = lexer->parse_point;
      }
      else{
         lexer->parse_point++;
         tok->where_lastchar = lexer->parse_point;
         character = &(lexer->input_stream[lexer->parse_point - lexer->input_stream]);
         tok->token = BL_ADDBINOP;
         tok->real_number = 0;
         tok->int_number = 0;
         tok->string = lexer->parse_point;
      }
   }
   else if(*character == '-')
   {
      tok->where_firstchar = lexer->parse_point;
      char suff = bl_peek_token(lexer,1);
      if(suff == '='){
         lexer->parse_point+=2;
         tok->where_lastchar = lexer->parse_point;
         character = &(lexer->input_stream[lexer->parse_point - lexer->input_stream]);
         tok->token = BL_SUBEQ;
         tok->real_number = 0;
         tok->int_number = 0;
         tok->string = lexer->parse_point;
      }
      else if(suff == '-'){
         lexer->parse_point+=2;
         tok->where_lastchar = lexer->parse_point;
         character = &(lexer->input_stream[lexer->parse_point - lexer->input_stream]);
         tok->token = BL_DEC;
         tok->real_number = 0;
         tok->int_number = 0;
         tok->string = lexer->parse_point;
      }
      else{
         lexer->parse_point++;
         tok->where_lastchar = lexer->parse_point;
         character = &(lexer->input_stream[lexer->parse_point - lexer->input_stream]);
         tok->token = BL_SUBBINOP;
         tok->real_number = 0;
         tok->int_number = 0;
         tok->string = lexer->parse_point;
      }
   }
   else if(*character == '*')
   {
      tok->where_firstchar = lexer->parse_point;
      char suff = bl_peek_token(lexer,1);
      if(suff == '='){
         lexer->parse_point+=2;
         tok->where_lastchar = lexer->parse_point;
         character = &(lexer->input_stream[lexer->parse_point - lexer->input_stream]);
         tok->token = BL_MULTEQ;
         tok->real_number = 0;
         tok->int_number = 0;
         tok->string = lexer->parse_point;
      }else{
         lexer->parse_point++;
         tok->where_lastchar = lexer->parse_point;
         character = &(lexer->input_stream[lexer->parse_point - lexer->input_stream]);
         tok->token = BL_MULTBINOP;
         tok->real_number = 0;
         tok->int_number = 0;
         tok->string = lexer->parse_point;
      }
   }
   else if(*character == '/')
   {
      tok->where_firstchar = lexer->parse_point;
      char suff = bl_peek_token(lexer,1);
      if(suff == '='){
         lexer->parse_point+=2;
         tok->where_lastchar = lexer->parse_point;
         character = &(lexer->input_stream[lexer->parse_point - lexer->input_stream]);
         tok->token = BL_DIVEQ;
         tok->real_number = 0;
         tok->int_number = 0;
         tok->string = lexer->parse_point;
      }else{
         lexer->parse_point++;
         tok->where_lastchar = lexer->parse_point;
         character = &(lexer->input_stream[lexer->parse_point - lexer->input_stream]);
         tok->token = BL_DIVBINOP;
         tok->real_number = 0;
         tok->int_number = 0;
         tok->string = lexer->parse_point;
      }
   }else if(*character == '!'){
      char suff = bl_peek_token(lexer,1);
      tok->where_firstchar = lexer->parse_point;
      if(suff == '='){
         lexer->parse_point +=2;
         tok->where_lastchar = lexer->parse_point;
         character = &(lexer->input_stream[lexer->parse_point - lexer->input_stream]);
         tok->token = BL_NOTEQ;
         tok->real_number = 0;
         tok->int_number = 0;
         tok->string = lexer->parse_point;
      }else{
         lexer->parse_point++;
         tok->where_lastchar = lexer->parse_point;
         character = &(lexer->input_stream[lexer->parse_point - lexer->input_stream]);
         tok->token = BL_NOT;
         tok->real_number = 0;
         tok->int_number = 0;
         tok->string = lexer->parse_point;
      }
   }else if(*character == '<'){
      char suff = bl_peek_token(lexer,1);
      tok->where_firstchar = lexer->parse_point;
      if(suff == '='){
         lexer->parse_point +=2;
         tok->where_lastchar = lexer->parse_point;
         character = &(lexer->input_stream[lexer->parse_point - lexer->input_stream]);
         tok->token = BL_LESSEQ;
         tok->real_number = 0;
         tok->int_number = 0;
         tok->string = lexer->parse_point;
      }else if(suff == '<'){
         lexer->parse_point +=2;
         tok->where_lastchar = lexer->parse_point;
         character = &(lexer->input_stream[lexer->parse_point - lexer->input_stream]);
         tok->token = BL_LSHIFT;
         tok->real_number = 0;
         tok->int_number = 0;
         tok->string = lexer->parse_point;
      }else{
         lexer->parse_point++;
         tok->where_lastchar = lexer->parse_point;
         character = &(lexer->input_stream[lexer->parse_point - lexer->input_stream]);
         tok->token = BL_LESSTHAN;
         tok->real_number = 0;
         tok->int_number = 0;
         tok->string = lexer->parse_point;
      }
   }else if(*character == '>'){
      char suff = bl_peek_token(lexer,1);
      tok->where_firstchar = lexer->parse_point;
      if(suff == '='){
         lexer->parse_point +=2;
         tok->where_lastchar = lexer->parse_point;
         character = &(lexer->input_stream[lexer->parse_point - lexer->input_stream]);
         tok->token = BL_GRTEQ;
         tok->real_number = 0;
         tok->int_number = 0;
         tok->string = lexer->parse_point;
      }else if(suff == '>'){
         lexer->parse_point +=2;
         tok->where_lastchar = lexer->parse_point;
         character = &(lexer->input_stream[lexer->parse_point - lexer->input_stream]);
         tok->token = BL_RSHIFT;
         tok->real_number = 0;
         tok->int_number = 0;
         tok->string = lexer->parse_point;
      }else{
         lexer->parse_point++;
         tok->where_lastchar = lexer->parse_point;
         character = &(lexer->input_stream[lexer->parse_point - lexer->input_stream]);
         tok->token = BL_GRTTHAN;
         tok->real_number = 0;
         tok->int_number = 0;
         tok->string = lexer->parse_point;
      }
   }else if(*character == '|'){
      char suff = bl_peek_token(lexer,1);
      tok->where_firstchar = lexer->parse_point;
      if(suff == '='){
         lexer->parse_point +=2;
         tok->where_lastchar = lexer->parse_point;
         character = &(lexer->input_stream[lexer->parse_point - lexer->input_stream]);
         tok->token = BL_OREQ;
         tok->real_number = 0;
         tok->int_number = 0;
         tok->string = lexer->parse_point;
      }else if(suff == '|'){
         lexer->parse_point +=2;
         tok->where_lastchar = lexer->parse_point;
         character = &(lexer->input_stream[lexer->parse_point - lexer->input_stream]);
         tok->token = BL_LOGOR;
         tok->real_number = 0;
         tok->int_number = 0;
         tok->string = lexer->parse_point;
      }else{
         lexer->parse_point++;
         tok->where_lastchar = lexer->parse_point;
         character = &(lexer->input_stream[lexer->parse_point - lexer->input_stream]);
         tok->token = BL_OR;
         tok->real_number = 0;
         tok->int_number = 0;
         tok->string = lexer->parse_point;
      }
   }else if(*character == '&'){
      char suff = bl_peek_token(lexer,1);
      tok->where_firstchar = lexer->parse_point;
      if(suff == '='){
         lexer->parse_point +=2;
         tok->where_lastchar = lexer->parse_point;
         character = &(lexer->input_stream[lexer->parse_point - lexer->input_stream]);
         tok->token = BL_ANDEQ;
         tok->real_number = 0;
         tok->int_number = 0;
         tok->string = lexer->parse_point;
      }else if(suff == '&'){
         lexer->parse_point +=2;
         tok->where_lastchar = lexer->parse_point;
         character = &(lexer->input_stream[lexer->parse_point - lexer->input_stream]);
         tok->token = BL_LOGAND;
         tok->real_number = 0;
         tok->int_number = 0;
         tok->string = lexer->parse_point;
      }else{
         lexer->parse_point++;
         tok->where_lastchar = lexer->parse_point;
         character = &(lexer->input_stream[lexer->parse_point - lexer->input_stream]);
         tok->token = BL_AND;
         tok->real_number = 0;
         tok->int_number = 0;
         tok->string = lexer->parse_point;
      }
   }else if(*character == '^'){
      char suff = bl_peek_token(lexer,1);
      tok->where_firstchar = lexer->parse_point;
      if(suff == '='){
         lexer->parse_point +=2;
         tok->where_lastchar = lexer->parse_point;
         character = &(lexer->input_stream[lexer->parse_point - lexer->input_stream]);
         tok->token = BL_XOREQ;
         tok->real_number = 0;
         tok->int_number = 0;
         tok->string = lexer->parse_point;
      }else{
         lexer->parse_point++;
         tok->where_lastchar = lexer->parse_point;
         character = &(lexer->input_stream[lexer->parse_point - lexer->input_stream]);
         tok->token = BL_XOR;
         tok->real_number = 0;
         tok->int_number = 0;
         tok->string = lexer->parse_point;
      }
   }
   else
   {
      tok->where_firstchar = lexer->parse_point;
      lexer->parse_point++;
      tok->where_lastchar = lexer->parse_point;
      character = &(lexer->input_stream[lexer->parse_point - lexer->input_stream]);
      tok->token = BL_UNIMPLEMENTED;
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


char *print_keyword(enum KEYWORD_TYPES var){
   if(var == BL_IDENTIFIER){
      return "BL_IDENTIFIER";
   }else if(var == BL_EOF){
      return "BL_EOF";
   }else if(var == BL_SEMICOLON){
      return "BL_SEMICOLON";
   }else if(var == BL_EQUAL){
      return "BL_EQUAL";
   }else if(var == BL_ISEQUALCOND){
      return "BL_ISEQUALCOND";
   }else if(var == BL_INT){
      return "BL_INT";
   }else if(var == BL_FLOAT){
      return "BL_FLOAT";
   }else if(var == BL_UNIMPLEMENTED){
      return "BL_UNIMPLEMENTED";
   }else if(var == BL_ADDBINOP){
      return "BL_ADDBINOP";
   }else if(var == BL_SUBBINOP){
      return "BL_SUBBINOP";
   }else if(var == BL_MULTBINOP){
      return "BL_MULTBINOP";
   }else if(var == BL_DIVBINOP){
      return "BL_DIVBINOP";
   }else if(var == BL_ADDEQ){
      return "BL_ADDEQ";
   }else if(var == BL_SUBEQ){
      return "BL_SUBEQ";
   }else if(var == BL_MULTEQ){
      return "BL_MULTEQ";
   }else if(var == BL_DIVEQ){
      return "BL_DIVEQ";
   }else if(var == BL_INC){
      return "BL_INC";
   }else if(var == BL_DEC){
      return "BL_DEC";
   }else if(var == BL_LPAREN){
      return "BL_LPAREN";
   }else if(var == BL_RPAREN){
      return "BL_RPAREN";
   }else if(var == BL_LBRACE){
      return "BL_LBRACE";
   }else if(var == BL_RBRACE){
      return "BL_RBRACE";
   }else if(var == BL_LBRACK){
      return "BL_LBRACK";
   }else if(var == BL_RBRACK){
      return "BL_RBRACK";
   }else if(var == BL_COMMA){
      return "BL_COMMA";
   }else if(var == BL_STRING){
      return "BL_STRING";
   }else if(var == BL_LESSTHAN){
      return "BL_LESSTHAN";
   }else if(var == BL_GRTTHAN){
      return "BL_GRTTHAN";
   }else if(var == BL_NOT){
      return "BL_NOT";
   }else if(var == BL_LESSEQ){
      return "BL_LESSEQ";
   }else if(var == BL_GRTEQ){
      return "BL_GRTEQ";
   }else if(var == BL_NOTEQ){
      return "BL_NOTEQ";
   }else if(var == BL_LSHIFT){
      return "BL_LSHIFT";
   }else if(var == BL_RSHIFT){
      return "BL_RSHIFT";
   }else if(var == BL_AND){
      return "BL_AND";
   }else if(var == BL_LOGAND){
      return "BL_LOGAND";
   }else if(var == BL_ANDEQ){
      return "BL_ANDEQ";
   }else if(var == BL_OR){
      return "BL_OR";
   }else if(var == BL_LOGOR){
      return "BL_LOGOR";
   }else if(var == BL_OREQ){
      return "BL_OREQ";
   }else if(var == BL_XOR){
      return "BL_XOR";
   }else if(var == BL_XOREQ){
      return "BL_XOREQ";
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
   if((tok.token != BL_UNIMPLEMENTED)){
      printf(",        %s          KEYWORD",print_keyword(tok.token));
      printf("\n");
   }else{
      printf(", ----  %s           KEYWORD",print_keyword(tok.token));
      printf("\n");
   }

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