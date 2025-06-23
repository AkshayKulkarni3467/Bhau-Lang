#ifndef INCLUDE_BL_LEXER_H
#define INCLUDE_BL_LEXER_H


/*-----------------------------------------------------------------Includes*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dynarray.h"
/*-------------------------------------------------------------------------*/


/*------------------------------------------------------------------Defines*/

#define BHAU_LANG
// #define BL_LEXER_SELF_TEST   // ---------------Undefine for self testing
// maybe bhai lang, bro lang later

/*-----------------------------------------------for debugging*/
#define BL_IDENTIFIERS
#define BL_OPERATORS
#define BL_SYMBOLS

/*--------------------------------------------------------------------------*/




/*------------------------------------------------------Structures and Enums*/
enum KEYWORD_TYPES {
   #ifdef BL_IDENTIFIERS
   BL_IDENTIFIER = 256,
   BL_INT,
   BL_FLOAT,
   BL_STRING,
   BL_CHAR,
   #endif //BL_IDENTIFIERS

   #ifdef BL_SYMBOLS
   BL_SEMICOLON,
   BL_LPAREN,
   BL_RPAREN,
   BL_LBRACE,
   BL_RBRACE,
   BL_LBRACK,
   BL_RBRACK,
   BL_COMMA,
   #endif //BL_SYMBOLS

   #ifdef BL_OPERATORS
   BL_EQUAL,
   BL_ISEQUALCOND,
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
   BL_NOT,
   BL_LESSTHAN,
   BL_GRTTHAN,
   BL_NOTEQ,
   BL_LESSEQ,
   BL_GRTEQ,
   BL_LOGAND,
   BL_LOGOR,
   #endif //BL_OPERATORS

   BL_UNIMPLEMENTED,
   BL_EOF,

};


typedef struct
{
   char *input_stream;
   char *eof;
   char *parse_point;
   char *string_storage;
   int   string_storage_len;
   int current_line;
   int current_column;
} bl_lexer;

typedef struct
{
   int line_number;
   int line_offset;
} bl_location;

typedef struct
{
   char *where_firstchar;
   char *where_lastchar;
   long token;
   double real_number;
   long   int_number;
   char *string;
   int string_len;
   bl_location loc;
} bl_token;

/*-------------------------------------------------------------------------*/



/*--------------------------------------------------------Helper functions*/
static int is_alpha(char c);
static int is_digit(char c);
static int is_alnum(char c);
static int is_whitespace(char c);

static int token_size(bl_token *t);
static char bl_peek_token(bl_lexer *l,int num);
static char bl_peek_prev_token(bl_lexer *l,int num);

static void bl_forward(bl_lexer *lexer);
static void bl_backward(bl_lexer *lexer);
static void bl_remove_whitespace(bl_lexer *l);
static void bl_next_step(bl_lexer *l);

char *print_keyword(enum KEYWORD_TYPES var);
void print_token(bl_token* da, int i);


/*---------------------------------------------------------Init functions*/
void bl_lexer_init(bl_lexer *lexer, const char *input_stream, const char *input_stream_end, char *string_store, int store_length);


/*------------------------------------------------------Tokenize function*/
bl_token *bl_tokenize(bl_lexer *lexer){
   char* character = &(lexer->input_stream[lexer->parse_point - lexer->input_stream]);
   bl_token *tok = malloc(sizeof(bl_token));

  #ifdef BL_IDENTIFIERS

   if (*character && *character && (is_alpha(*character) || *character == '_'))
   {
      tok->where_firstchar = lexer->parse_point;
      tok->string = lexer->parse_point;
      bl_forward(lexer);
      while(*character && (is_alnum(*character) || *character == '_' || *character == '$')){
         character = &(lexer->input_stream[lexer->parse_point - lexer->input_stream]);
         bl_forward(lexer);

      }
      bl_backward(lexer);
      tok->token = BL_IDENTIFIER;
      tok->real_number = 0;
      tok->int_number = 0;
      tok->where_lastchar = lexer->parse_point;
      tok->string_len = token_size(tok);
      tok->loc.line_number = lexer->current_line;
      tok->loc.line_offset = lexer->current_column;
   }
   /*DIGITS*/
   else if
   (*character && (*character >= '0' && *character <= '9'))
   {
      char buf[64];
      tok->where_firstchar = lexer->parse_point;
      tok->string = tok->where_firstchar;
      while(*character && (
         (*character >= '0' && *character <= '9')
      )){
         character = &(lexer->input_stream[lexer->parse_point - lexer->input_stream]);
         bl_forward(lexer);
      }
      bl_backward(lexer);
      if(*(lexer->parse_point) == '.'){
         bl_forward(lexer);
         character = &(lexer->input_stream[lexer->parse_point - lexer->input_stream]);
         while(*character && (*character >= '0' && *character <= '9')){
            character = &(lexer->input_stream[lexer->parse_point - lexer->input_stream]);
            bl_forward(lexer);
         }
         bl_backward(lexer);
         tok->where_lastchar = lexer->parse_point;

         int len = token_size(tok);
         memcpy(buf, tok->where_firstchar, len);
         buf[len] = '\0';
         tok->real_number = strtod(buf, NULL);
         tok->token = BL_FLOAT;
         tok->int_number = 0;
         tok->string = tok->where_firstchar;
         tok->loc.line_number = lexer->current_line;
         tok->loc.line_offset = lexer->current_column;

      }else{
         tok->where_lastchar = lexer->parse_point;
         int len = token_size(tok);
         memcpy(buf, tok->where_firstchar, len);
         buf[len] = '\0';
         tok->int_number = strtol(buf, NULL, 10);
         tok->token = BL_INT;
         tok->real_number = 0;  
         tok->loc.line_number = lexer->current_line;
         tok->loc.line_offset = lexer->current_column;
      }      
   }
   /*STRINGS*/
   else if 
   (*character && *character == '"')
   {
      tok->where_firstchar = lexer->parse_point;  
      bl_forward(lexer);  
      char *start = lexer->parse_point;

      while (lexer->parse_point < lexer->eof && *lexer->parse_point != '"') {
         character = &(lexer->input_stream[lexer->parse_point - lexer->input_stream]);
         bl_forward(lexer);
      }
      int str_len = lexer->parse_point - start;
      if (lexer->parse_point < lexer->eof) {
         bl_forward(lexer); 
      }

      tok->where_lastchar = lexer->parse_point;
      tok->int_number = 0;
      tok->real_number = 0;
      tok->token = BL_STRING;
      tok->loc.line_number = lexer->current_line;
      tok->loc.line_offset = lexer->current_column;


      if (lexer->string_storage_len >= str_len + 1){
         memcpy(lexer->string_storage, start, str_len);
         lexer->string_storage[str_len] = '\0';
         tok->string = lexer->string_storage;
         tok->string_len = str_len;

         lexer->string_storage += str_len + 1;
         lexer->string_storage_len -= str_len + 1;
      }else{
         fprintf(stderr, "String storage buffer overflow\n");
         tok->string = NULL;
         tok->string_len = 0;
      }




   }
   /*CHARS*/
   else if
   (*character && *character == '\'')
   {
      tok->where_firstchar = lexer->parse_point;
      bl_forward(lexer);
      bl_forward(lexer);
      bl_forward(lexer);
      character = &(lexer->input_stream[lexer->parse_point - lexer->input_stream]);
      tok->int_number = 0;
      tok->real_number = 0;
      tok->where_lastchar = lexer->parse_point;
      tok->token = BL_CHAR;
      tok->string = tok->where_firstchar;
      tok->loc.line_number = lexer->current_line;
      tok->loc.line_offset = lexer->current_column;
   }
   else 
   
   #endif //BL_IDENTIFIERS
   
   #ifdef BL_SYMBOLS

   /*SEMICOLON*/
   if 
   (*character && *character == ';')
   {
      tok->where_firstchar = lexer->parse_point;
      bl_forward(lexer);
      character = &(lexer->input_stream[lexer->parse_point - lexer->input_stream]);
      tok->where_lastchar = lexer->parse_point;
      tok->token = BL_SEMICOLON;
      tok->string = tok->where_firstchar;
      tok->int_number = 0;
      tok->real_number = 0;
      tok->loc.line_number = lexer->current_line;
      tok->loc.line_offset = lexer->current_column;
   }
   /*RBRACE*/
   else if(*character && *character == '{')
   {
      tok->where_firstchar = lexer->parse_point;
      bl_forward(lexer);
      character = &(lexer->input_stream[lexer->parse_point - lexer->input_stream]);
      tok->where_lastchar = lexer->parse_point;
      tok->token = BL_LBRACE;
      tok->string = tok->where_firstchar;
      tok->int_number = 0;
      tok->real_number = 0;
      tok->loc.line_number = lexer->current_line;
      tok->loc.line_offset = lexer->current_column;
   }
   /*LBRACE*/
   else if(*character && *character == '}')
   {
      tok->where_firstchar = lexer->parse_point;
      bl_forward(lexer);
      character = &(lexer->input_stream[lexer->parse_point - lexer->input_stream]);
      tok->where_lastchar = lexer->parse_point;
      tok->token = BL_RBRACE;
      tok->string = tok->where_firstchar;
      tok->int_number = 0;
      tok->real_number = 0;
      tok->loc.line_number = lexer->current_line;
      tok->loc.line_offset = lexer->current_column;
   }
   /*LBRACK*/
   else if(*character && *character == '[')
   {
      tok->where_firstchar = lexer->parse_point;
      bl_forward(lexer);
      character = &(lexer->input_stream[lexer->parse_point - lexer->input_stream]);
      tok->where_lastchar = lexer->parse_point;
      tok->token = BL_LBRACK;
      tok->string = tok->where_firstchar;
      tok->int_number = 0;
      tok->real_number = 0;
      tok->loc.line_number = lexer->current_line;
      tok->loc.line_offset = lexer->current_column;
   }
   /*RBRAC*/
   else if(*character && *character == ']')
   {
      tok->where_firstchar = lexer->parse_point;
      bl_forward(lexer);
      character = &(lexer->input_stream[lexer->parse_point - lexer->input_stream]);
      tok->where_lastchar = lexer->parse_point;
      tok->token = BL_RBRACK;
      tok->string = tok->where_firstchar;
      tok->int_number = 0;
      tok->real_number = 0;
      tok->loc.line_number = lexer->current_line;
      tok->loc.line_offset = lexer->current_column;
   }
   /*LPAREN*/
   else if(*character && *character == '(')
   {
      tok->where_firstchar = lexer->parse_point;
      bl_forward(lexer);
      character = &(lexer->input_stream[lexer->parse_point - lexer->input_stream]);
      tok->where_lastchar = lexer->parse_point;
      tok->token = BL_LPAREN;
      tok->string = tok->where_firstchar;
      tok->int_number = 0;
      tok->real_number = 0;
      tok->loc.line_number = lexer->current_line;
      tok->loc.line_offset = lexer->current_column;
   }
   /*RPAREN*/
   else if(*character && *character == ')')
   {
      tok->where_firstchar = lexer->parse_point;
      bl_forward(lexer);
      character = &(lexer->input_stream[lexer->parse_point - lexer->input_stream]);
      tok->where_lastchar = lexer->parse_point;
      tok->token = BL_RPAREN;
      tok->string = tok->where_firstchar;
      tok->int_number = 0;
      tok->real_number = 0;
      tok->loc.line_number = lexer->current_line;
      tok->loc.line_offset = lexer->current_column;
   }
   /*COMMA*/
   else if(*character && *character == ',')
   {
      tok->where_firstchar = lexer->parse_point;
      bl_forward(lexer);
      character = &(lexer->input_stream[lexer->parse_point - lexer->input_stream]);
      tok->where_lastchar = lexer->parse_point;
      tok->token = BL_COMMA;
      tok->string = tok->where_firstchar;
      tok->int_number = 0;
      tok->real_number = 0;
      tok->loc.line_number = lexer->current_line;
      tok->loc.line_offset = lexer->current_column;
   }
   
   else 
   
   #endif //BL_SYMBOLS
   

   #ifdef BL_OPERATORS
   /*EQUAL, ISEQUAL*/
   if (*character && *character == '=')
   {
      char suff = bl_peek_token(lexer,1);
      if(suff != '=')
      {
         tok->where_firstchar = lexer->parse_point;
         bl_forward(lexer);
         character = &(lexer->input_stream[lexer->parse_point - lexer->input_stream]);
         tok->where_lastchar = lexer->parse_point;
         tok->token = BL_EQUAL;
         tok->string = tok->where_firstchar;
         tok->int_number = 0;
         tok->real_number = 0;
         tok->loc.line_number = lexer->current_line;
         tok->loc.line_offset = lexer->current_column;
      }
      else
      {
         tok->where_firstchar = lexer->parse_point;
         bl_forward(lexer);
         bl_forward(lexer);
         character = &(lexer->input_stream[lexer->parse_point - lexer->input_stream]);
         tok->where_lastchar = lexer->parse_point;
         tok->token = BL_ISEQUALCOND;
         tok->string = tok->where_firstchar;
         tok->int_number = 0;
         tok->real_number = 0;
         tok->loc.line_number = lexer->current_line;
         tok->loc.line_offset = lexer->current_column;
      }

   }
      /*NOT, NOTEQ*/
   else if(*character == '!'){
      char suff = bl_peek_token(lexer,1);
      tok->where_firstchar = lexer->parse_point;
      if(suff == '='){
         bl_forward(lexer);
         bl_forward(lexer);
         tok->where_lastchar = lexer->parse_point;
         character = &(lexer->input_stream[lexer->parse_point - lexer->input_stream]);
         tok->token = BL_NOTEQ;
         tok->real_number = 0;
         tok->int_number = 0;
         tok->string = lexer->parse_point;
         tok->loc.line_number = lexer->current_line;
         tok->loc.line_offset = lexer->current_column;
      }
      else{
         bl_forward(lexer);
         tok->where_lastchar = lexer->parse_point;
         character = &(lexer->input_stream[lexer->parse_point - lexer->input_stream]);
         tok->token = BL_NOT;
         tok->real_number = 0;
         tok->int_number = 0;
         tok->string = lexer->parse_point;
         tok->loc.line_number = lexer->current_line;
         tok->loc.line_offset = lexer->current_column;
      }
   }

   /*ADDBINOP, ADDEQ, INC*/
   else if(*character == '+')
   {
      tok->where_firstchar = lexer->parse_point;
      char suff = bl_peek_token(lexer,1);
      if(suff == '='){
         bl_forward(lexer);
         bl_forward(lexer);
         tok->where_lastchar = lexer->parse_point;
         character = &(lexer->input_stream[lexer->parse_point - lexer->input_stream]);
         tok->token = BL_ADDEQ;
         tok->real_number = 0;
         tok->int_number = 0;
         tok->string = lexer->parse_point;
         tok->loc.line_number = lexer->current_line;
         tok->loc.line_offset = lexer->current_column;
      }
      else if(suff == '+'){
         bl_forward(lexer);
         bl_forward(lexer);
         tok->where_lastchar = lexer->parse_point;
         character = &(lexer->input_stream[lexer->parse_point - lexer->input_stream]);
         tok->token = BL_INC;
         tok->real_number = 0;
         tok->int_number = 0;
         tok->string = lexer->parse_point;
         tok->loc.line_number = lexer->current_line;
         tok->loc.line_offset = lexer->current_column;
      }
      else{
         bl_forward(lexer);
         tok->where_lastchar = lexer->parse_point;
         character = &(lexer->input_stream[lexer->parse_point - lexer->input_stream]);
         tok->token = BL_ADDBINOP;
         tok->real_number = 0;
         tok->int_number = 0;
         tok->string = lexer->parse_point;
         tok->loc.line_number = lexer->current_line;
         tok->loc.line_offset = lexer->current_column;
      }
   }
   /*SUBBINOP, SUBEQ, DEC*/
   else if(*character == '-')
   {
      tok->where_firstchar = lexer->parse_point;
      char suff = bl_peek_token(lexer,1);
      if(suff == '='){
         bl_forward(lexer);
         bl_forward(lexer);
         tok->where_lastchar = lexer->parse_point;
         character = &(lexer->input_stream[lexer->parse_point - lexer->input_stream]);
         tok->token = BL_SUBEQ;
         tok->real_number = 0;
         tok->int_number = 0;
         tok->string = lexer->parse_point;
         tok->loc.line_number = lexer->current_line;
         tok->loc.line_offset = lexer->current_column;
      }
      else if(suff == '-'){
         bl_forward(lexer);
         bl_forward(lexer);
         tok->where_lastchar = lexer->parse_point;
         character = &(lexer->input_stream[lexer->parse_point - lexer->input_stream]);
         tok->token = BL_DEC;
         tok->real_number = 0;
         tok->int_number = 0;
         tok->string = lexer->parse_point;
         tok->loc.line_number = lexer->current_line;
         tok->loc.line_offset = lexer->current_column;
      }
      else{
         bl_forward(lexer);
         tok->where_lastchar = lexer->parse_point;
         character = &(lexer->input_stream[lexer->parse_point - lexer->input_stream]);
         tok->token = BL_SUBBINOP;
         tok->real_number = 0;
         tok->int_number = 0;
         tok->string = lexer->parse_point;
         tok->loc.line_number = lexer->current_line;
         tok->loc.line_offset = lexer->current_column;
      }
   }
   /*MULTBINOP, MULTEQ*/
   else if(*character == '*')
   {
      tok->where_firstchar = lexer->parse_point;
      char suff = bl_peek_token(lexer,1);
      if(suff == '='){
         bl_forward(lexer);
         bl_forward(lexer);
         tok->where_lastchar = lexer->parse_point;
         character = &(lexer->input_stream[lexer->parse_point - lexer->input_stream]);
         tok->token = BL_MULTEQ;
         tok->real_number = 0;
         tok->int_number = 0;
         tok->string = lexer->parse_point;
         tok->loc.line_number = lexer->current_line;
         tok->loc.line_offset = lexer->current_column;
      }else{
         bl_forward(lexer);
         tok->where_lastchar = lexer->parse_point;
         character = &(lexer->input_stream[lexer->parse_point - lexer->input_stream]);
         tok->token = BL_MULTBINOP;
         tok->real_number = 0;
         tok->int_number = 0;
         tok->string = lexer->parse_point;
         tok->loc.line_number = lexer->current_line;
         tok->loc.line_offset = lexer->current_column;
      }
   }
   /*DIVBINOP, DIVEQ*/
   else if(*character == '/')
   {
      tok->where_firstchar = lexer->parse_point;
      char suff = bl_peek_token(lexer,1);
      if(suff == '='){
         bl_forward(lexer);
         bl_forward(lexer);
         tok->where_lastchar = lexer->parse_point;
         character = &(lexer->input_stream[lexer->parse_point - lexer->input_stream]);
         tok->token = BL_DIVEQ;
         tok->real_number = 0;
         tok->int_number = 0;
         tok->string = lexer->parse_point;
         tok->loc.line_number = lexer->current_line;
         tok->loc.line_offset = lexer->current_column;
      }else{
         bl_forward(lexer);
         tok->where_lastchar = lexer->parse_point;
         character = &(lexer->input_stream[lexer->parse_point - lexer->input_stream]);
         tok->token = BL_DIVBINOP;
         tok->real_number = 0;
         tok->int_number = 0;
         tok->string = lexer->parse_point;
         tok->loc.line_number = lexer->current_line;
         tok->loc.line_offset = lexer->current_column;
      }
   }

   /*LESSTHAN, LESSTHANEQ, LSHIFT*/
   else if(*character == '<'){
      char suff = bl_peek_token(lexer,1);
      tok->where_firstchar = lexer->parse_point;
      if(suff == '='){
         bl_forward(lexer);
         bl_forward(lexer);
         tok->where_lastchar = lexer->parse_point;
         character = &(lexer->input_stream[lexer->parse_point - lexer->input_stream]);
         tok->token = BL_LESSEQ;
         tok->real_number = 0;
         tok->int_number = 0;
         tok->string = lexer->parse_point;
         tok->loc.line_number = lexer->current_line;
         tok->loc.line_offset = lexer->current_column;
      }else if(suff == '<'){
         bl_forward(lexer);
         bl_forward(lexer);
         tok->where_lastchar = lexer->parse_point;
         character = &(lexer->input_stream[lexer->parse_point - lexer->input_stream]);
         tok->token = BL_LSHIFT;
         tok->real_number = 0;
         tok->int_number = 0;
         tok->string = lexer->parse_point;
         tok->loc.line_number = lexer->current_line;
         tok->loc.line_offset = lexer->current_column;
      }else{
         bl_forward(lexer);
         tok->where_lastchar = lexer->parse_point;
         character = &(lexer->input_stream[lexer->parse_point - lexer->input_stream]);
         tok->token = BL_LESSTHAN;
         tok->real_number = 0;
         tok->int_number = 0;
         tok->string = lexer->parse_point;
         tok->loc.line_number = lexer->current_line;
         tok->loc.line_offset = lexer->current_column;
      }
   }
   /*GRTTHAN, GRTTHANEQ, RSHIFT*/
   else if(*character == '>'){
      char suff = bl_peek_token(lexer,1);
      tok->where_firstchar = lexer->parse_point;
      if(suff == '='){
         bl_forward(lexer);
         bl_forward(lexer);
         tok->where_lastchar = lexer->parse_point;
         character = &(lexer->input_stream[lexer->parse_point - lexer->input_stream]);
         tok->token = BL_GRTEQ;
         tok->real_number = 0;
         tok->int_number = 0;
         tok->string = lexer->parse_point;
         tok->loc.line_number = lexer->current_line;
         tok->loc.line_offset = lexer->current_column;
      }else if(suff == '>'){
         bl_forward(lexer);
         bl_forward(lexer);
         tok->where_lastchar = lexer->parse_point;
         character = &(lexer->input_stream[lexer->parse_point - lexer->input_stream]);
         tok->token = BL_RSHIFT;
         tok->real_number = 0;
         tok->int_number = 0;
         tok->string = lexer->parse_point;
         tok->loc.line_number = lexer->current_line;
         tok->loc.line_offset = lexer->current_column;
      }else{
         bl_forward(lexer);
         tok->where_lastchar = lexer->parse_point;
         character = &(lexer->input_stream[lexer->parse_point - lexer->input_stream]);
         tok->token = BL_GRTTHAN;
         tok->real_number = 0;
         tok->int_number = 0;
         tok->string = lexer->parse_point;
         tok->loc.line_number = lexer->current_line;
         tok->loc.line_offset = lexer->current_column;
      }
   }
   /*BITWISE OR, OREQ, LOGICAL OR*/
   else if(*character == '|'){
      char suff = bl_peek_token(lexer,1);
      tok->where_firstchar = lexer->parse_point;
      if(suff == '='){
         bl_forward(lexer);
         bl_forward(lexer);
         tok->where_lastchar = lexer->parse_point;
         character = &(lexer->input_stream[lexer->parse_point - lexer->input_stream]);
         tok->token = BL_OREQ;
         tok->real_number = 0;
         tok->int_number = 0;
         tok->string = lexer->parse_point;
         tok->loc.line_number = lexer->current_line;
         tok->loc.line_offset = lexer->current_column;
      }else if(suff == '|'){
         bl_forward(lexer);
         bl_forward(lexer);
         tok->where_lastchar = lexer->parse_point;
         character = &(lexer->input_stream[lexer->parse_point - lexer->input_stream]);
         tok->token = BL_LOGOR;
         tok->real_number = 0;
         tok->int_number = 0;
         tok->string = lexer->parse_point;
         tok->loc.line_number = lexer->current_line;
         tok->loc.line_offset = lexer->current_column;
      }else{
         bl_forward(lexer);
         tok->where_lastchar = lexer->parse_point;
         character = &(lexer->input_stream[lexer->parse_point - lexer->input_stream]);
         tok->token = BL_OR;
         tok->real_number = 0;
         tok->int_number = 0;
         tok->string = lexer->parse_point;
         tok->loc.line_number = lexer->current_line;
         tok->loc.line_offset = lexer->current_column;
      }
   }
   /*BITWISE AND, ANDEQ, LOGICAL AND*/
   else if(*character == '&'){
      char suff = bl_peek_token(lexer,1);
      tok->where_firstchar = lexer->parse_point;
      if(suff == '='){
         bl_forward(lexer);
         bl_forward(lexer);
         tok->where_lastchar = lexer->parse_point;
         character = &(lexer->input_stream[lexer->parse_point - lexer->input_stream]);
         tok->token = BL_ANDEQ;
         tok->real_number = 0;
         tok->int_number = 0;
         tok->string = lexer->parse_point;
         tok->loc.line_number = lexer->current_line;
         tok->loc.line_offset = lexer->current_column;
      }else if(suff == '&'){
         bl_forward(lexer);
         bl_forward(lexer);
         tok->where_lastchar = lexer->parse_point;
         character = &(lexer->input_stream[lexer->parse_point - lexer->input_stream]);
         tok->token = BL_LOGAND;
         tok->real_number = 0;
         tok->int_number = 0;
         tok->string = lexer->parse_point;
         tok->loc.line_number = lexer->current_line;
         tok->loc.line_offset = lexer->current_column;
      }else{
         bl_forward(lexer);
         tok->where_lastchar = lexer->parse_point;
         character = &(lexer->input_stream[lexer->parse_point - lexer->input_stream]);
         tok->token = BL_AND;
         tok->real_number = 0;
         tok->int_number = 0;
         tok->string = lexer->parse_point;
         tok->loc.line_number = lexer->current_line;
         tok->loc.line_offset = lexer->current_column;
      }
   }
   /*BITWISE XOR, XOREQ*/
   else if(*character == '^'){
      char suff = bl_peek_token(lexer,1);
      tok->where_firstchar = lexer->parse_point;
      if(suff == '='){
         bl_forward(lexer);
         bl_forward(lexer);
         tok->where_lastchar = lexer->parse_point;
         character = &(lexer->input_stream[lexer->parse_point - lexer->input_stream]);
         tok->token = BL_XOREQ;
         tok->real_number = 0;
         tok->int_number = 0;
         tok->string = lexer->parse_point;
         tok->loc.line_number = lexer->current_line;
         tok->loc.line_offset = lexer->current_column;
      }else{
         bl_forward(lexer);
         tok->where_lastchar = lexer->parse_point;
         character = &(lexer->input_stream[lexer->parse_point - lexer->input_stream]);
         tok->token = BL_XOR;
         tok->real_number = 0;
         tok->int_number = 0;
         tok->string = lexer->parse_point;
         tok->loc.line_number = lexer->current_line;
         tok->loc.line_offset = lexer->current_column;
      }
   }
   
   /*EOF*/
   else 
   
   #endif //BL_OPERATORS

   if(!(*character)){
      tok->where_firstchar = lexer->parse_point;
      bl_forward(lexer);
      tok->where_lastchar = lexer->parse_point;
      character = &(lexer->input_stream[lexer->parse_point - lexer->input_stream]);
      tok->token = BL_EOF;
      tok->real_number = 0;
      tok->int_number = 0;
      tok->string = lexer->parse_point;
      tok->loc.line_number = lexer->current_line;
      tok->loc.line_offset = lexer->current_column;
   }
   /*UNIMPLEMENTED TOKEN*/
   else
   {
      tok->where_firstchar = lexer->parse_point;
      bl_forward(lexer);
      tok->where_lastchar = lexer->parse_point;
      character = &(lexer->input_stream[lexer->parse_point - lexer->input_stream]);
      tok->token = BL_UNIMPLEMENTED;
      tok->real_number = 0;
      tok->int_number = 0;
      tok->string = lexer->parse_point;
      tok->loc.line_number = lexer->current_line;
      tok->loc.line_offset = lexer->current_column;
   }
   

   return tok;

}


#ifdef BL_LEXER_SELF_TEST


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

#endif

static int is_alpha(char c) {
    return (c >= 'A' && c <= 'Z') ||
           (c >= 'a' && c <= 'z');
}

static int is_digit(char c){
   return (c >= '0' && c <= '9');
}

static int is_alnum(char c){
   return is_alpha(c) || is_digit(c);
}


static int is_whitespace(char c){
   return (c == ' ') || (c == '\n') || (c == '\r');
}

static int token_size(bl_token *t){
   return t->where_lastchar - t->where_firstchar;
}

static char bl_peek_token(bl_lexer *l,int num){
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

static char bl_peek_prev_token(bl_lexer *l,int num){
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

static void bl_forward(bl_lexer *lexer){
   if (*lexer->parse_point == '\n') {
      lexer->current_line++;
      lexer->current_column = 1;
   } else {
      lexer->current_column++;
   }
   lexer->parse_point++;
}

static void bl_backward(bl_lexer *lexer){
   lexer->current_column--;
   lexer->parse_point--;
}

void bl_lexer_init(bl_lexer *lexer, const char *input_stream, const char *input_stream_end, char *string_store, int store_length){
   lexer->input_stream = (char *)input_stream;
   lexer->parse_point = (char *)input_stream;
   lexer->eof = (char *)input_stream_end;
   lexer->string_storage = string_store;
   lexer->string_storage_len = store_length;
   lexer->current_line = 1;
   lexer->current_column = 1;
}



static void bl_remove_whitespace(bl_lexer *l){
   char c = l->input_stream[l->parse_point - l->input_stream];
   while((c == ' ') || (c == '\n') || (c == '\r')){
      if (*(l->parse_point) == '\n') {
         l->current_line++;
         l->current_column = 1;
      } else {
         l->current_column++;
      }
      c = l->input_stream[++(l->parse_point) - l->input_stream];
   }
}

static void bl_next_step(bl_lexer *l){
   bl_remove_whitespace(l);
}


char *print_keyword(enum KEYWORD_TYPES var){
   switch(var){

      #ifdef BL_IDENTIFIERS

      case BL_IDENTIFIER:
         return "BL_IDENTIFIER";
      case BL_INT:
         return "BL_INT";
      case BL_FLOAT:
         return "BL_FLOAT";
      case BL_STRING:
         return "BL_STRING";
      case BL_CHAR:
         return "BL_CHAR";

      #endif //BL_IDENTIFIERS

      #ifdef BL_SYMBOLS

      case BL_SEMICOLON:
         return "BL_SEMICOLON";
      case BL_LPAREN:
         return "BL_LPAREN";
      case BL_RPAREN:
         return "BL_RPAREN";
      case BL_LBRACE:
         return "BL_LBRACE";
      case BL_RBRACE:
         return "BL_RBRACE";
      case BL_LBRACK:
         return "BL_LBRACK";
      case BL_RBRACK:
         return "BL_RBRACK";
      case BL_COMMA:
         return "BL_COMMA";
      #endif //BL_SYMBOLS

      case BL_UNIMPLEMENTED:
         return "BL_UNIMPLEMENTED";
      case BL_EOF:
         return "BL_EOF";

      #ifdef BL_OPERATORS
      case BL_EQUAL:
         return "BL_EQUAL";
      case BL_ISEQUALCOND:
         return "BL_ISEQUALCOND";
      case BL_SUBBINOP:
         return "BL_SUBBINOP";
      case BL_MULTBINOP:
         return "BL_MULTBINOP";
      case BL_ADDBINOP:
         return "BL_ADDBINOP";
      case BL_DIVBINOP:
         return "BL_DIVBINOP";
      case BL_ADDEQ:
         return "BL_ADDEQ";
      case BL_SUBEQ:
         return "BL_SUBEQ";
      case BL_MULTEQ:
         return "BL_MULTEQ";
      case BL_DIVEQ:
         return "BL_DIVEQ";
      case BL_INC:
         return "BL_INC";
      case BL_DEC:
         return "BL_DEC";
      case BL_LSHIFT:
         return "BL_LSHIFT";
      case BL_RSHIFT:
         return "BL_RSHIFT";
      case BL_AND:
         return "BL_AND";
      case BL_OR:
         return "BL_OR";
      case BL_XOR:
         return "BL_XOR";
      case BL_ANDEQ:
         return "BL_ANDEQ";
      case BL_OREQ:
         return "BL_OREQ";
      case BL_XOREQ:
         return "BL_XOREQ";
      case BL_NOT:
         return "BL_NOT";
      case BL_LESSTHAN:
         return "BL_LESSTHAN";
      case BL_GRTTHAN:
         return "BL_GRTTHAN";
      case BL_NOTEQ:
         return "BL_NOTEQ";
      case BL_LESSEQ:
         return "BL_LESSEQ";
      case BL_GRTEQ:
         return "BL_GRTEQ";
      case BL_LOGAND:
         return "BL_LOGAND";
      case BL_LOGOR:
         return "BL_LOGOR";
      #endif //BL_OPERATORS

      default:
         return "<<UNKNOWN TOKEN>>";

      
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
      printf(",        %s          lin %d col %d",print_keyword(tok.token), tok.loc.line_number, tok.loc.line_offset);
      printf("\n");
   }else{
      printf(", ----  %s           KEYWORD",print_keyword(tok.token));
      printf("\n");
   }

}


#endif //BL_LEXER_H