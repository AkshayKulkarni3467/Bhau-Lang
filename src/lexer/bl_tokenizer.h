#ifndef INCLUDE_BL_TOKENIZER_H
#define INCLUDE_BL_TOKENIZER_H


/*-----------------------------------------------------------------Includes*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h> 
#include <ctype.h>
#include <assert.h>
#include <inttypes.h>


#include "bl_dynarray.h"
#include "bl_arena.h"
#include "bl_langkeywords.h"
/*-------------------------------------------------------------------------*/


/*------------------------------------------------------------------Defines*/

#define BHAU_LANG

//WARN Taking maximum text file size as 256 KB
#define TEXT_FILE_SIZE (1<<18) 
// #define BL_LEXER_SELF_TEST   // ---------------Undefine for self testing
#define BL_DEBUG
// maybe bhai lang, bro lang later

/*----------------------------------------------------------Helper defines*/
#define SET_DEFAULT_TOKEN(type) bl_set_token(tok,type,0,0,tok->where_firstchar,token_size(tok),lexer->current_line,lexer->current_column)
#define SET_FLOAT_TOKEN(type,value) bl_set_token(tok,type,value,0,tok->where_firstchar,token_size(tok),lexer->current_line,lexer->current_column)
#define SET_INT_TOKEN(type,value) bl_set_token(tok,type,0,value,tok->where_firstchar,token_size(tok),lexer->current_line,lexer->current_column)
#define SET_STRING_TOKEN(type,str_ptr,str_len) bl_set_token(tok,type,0,0,str_ptr,str_len,lexer->current_line,lexer->current_column)
#define UPDATE_CHAR_PTR() (character = &(lexer->input_stream[lexer->parse_point - lexer->input_stream]))




#define SET_SIMPLE_TOKEN(type) \
    tok->where_firstchar = lexer->parse_point; \
    bl_forward(lexer, 1); \
    tok->where_lastchar = lexer->parse_point; \
   SET_DEFAULT_TOKEN(type)

#define SET_COMPOUND_TOKEN(type,len) \
   tok->where_firstchar = lexer->parse_point; \
   bl_forward(lexer,len); \
   tok->where_lastchar = lexer->parse_point; \
   SET_DEFAULT_TOKEN(type)


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
   BL_COLON,
   BL_LPAREN,
   BL_RPAREN,
   BL_LBRACE,
   BL_RBRACE,
   BL_LBRACK,
   BL_RBRACK,
   BL_COMMA,
   #endif //BL_SYMBOLS

   #ifdef BL_OPERATORS
   BL_EQUAL,            //
   BL_ISEQUALCOND,      //
   BL_MODBINOP,         //
   BL_ADDBINOP,         //
   BL_SUBBINOP,         //
   BL_MULTBINOP,        //
   BL_DIVBINOP,         //
   BL_ADDEQ,            //
   BL_MODEQ,            //
   BL_SUBEQ,            //
   BL_MULTEQ,           //
   BL_DIVEQ,            //
   BL_INC,              //
   BL_DEC,              //
   BL_LSHIFT,           //
   BL_RSHIFT,           //
   BL_AND,              //
   BL_OR,               //
   BL_XOR,              //
   BL_ANDEQ,            //
   BL_OREQ,             //
   BL_XOREQ,            //
   BL_NOT,              //
   BL_LESSTHAN,         //
   BL_GRTTHAN,          //
   BL_NOTEQ,            //
   BL_LESSEQ,           //
   BL_GRTEQ,            //
   BL_LOGAND,           //--
   BL_LOGOR,            //--
   BL_COMMENT,          //
   BL_MULCOMMENT,       //
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
   bl_arena* arena;
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
static inline int is_alpha(char c);
static inline int is_digit(char c);
static inline int is_alnum(char c);
static inline int is_whitespace(char c);
static inline int is_newline(char c);

static inline char *keyword_enum_to_str(int var);
static inline int token_size(bl_token *t);
static inline char bl_peek_token(bl_lexer *l,int num);
static inline char bl_peek_prev_token(bl_lexer *l,int num);
static inline void bl_set_token(bl_token* tok, enum KEYWORD_TYPES label,double real_number, long int_number, char* string, int string_len, int line_number, int line_offset);

static inline void bl_forward(bl_lexer *lexer,int num);
static inline void bl_backward(bl_lexer *lexer, int num);
static inline void bl_remove_whitespace(bl_lexer *l);
static inline void bl_next_step(bl_lexer *l);

#ifdef BL_DEBUG


static inline void bl_token_print(const bl_token *tok);
static inline void bl_token_list_print(bl_token *tokens, size_t count);
static inline void bl_token_dump_raw(const bl_token *tok);
static inline void bl_token_debug_string(const bl_token *tok, char *buf, size_t bufsize);

static inline void bl_lexer_print(const bl_lexer *l);
static inline void bl_lexer_peek_context(const bl_lexer *l, int chars_around);
static inline void bl_lexer_print_remaining(const bl_lexer *l);
static inline void bl_token_verify_arena(const bl_token *tok, const bl_arena *arena);
static inline bl_token* bl_token_list_filter(bl_arena *arena,bl_token *tokens,size_t count, enum KEYWORD_TYPES type);
static inline void bl_token_list_revfilter(bl_token *tokens, bl_token* temp_arr,size_t count, enum KEYWORD_TYPES type);
static inline bl_token* bl_token_list_filter_multiple(bl_arena* arena,bl_token* tokens,size_t token_count,enum KEYWORD_TYPES* keyword_arr,size_t keyword_count);
char* ptrs_to_string(const char* start, const char* end, bl_arena* arena);



#endif //BL_DEBUG

static inline char * bl_token_get_str(bl_token token,char* buf);
static inline enum KEYWORD_TYPES bl_token_get_type(bl_token token);
static inline bl_token* bl_token_list_preprocess(bl_token* token_list);
static inline bl_token* bl_tokenize_file(char* filename,bl_arena* arena);



/*---------------------------------------------------------Init functions*/
static inline void bl_lexer_init(bl_lexer *lexer, bl_arena* arena,const char *input_stream, const char *input_stream_end, char *string_store, int store_length);


/*------------------------------------------------------Tokenize function*/
bl_token *bl_tokenize(bl_lexer *lexer);


#ifdef BL_LEXER_SELF_TEST


int main(int argc, char** argv){

   if(argc != 2){
      fprintf(stderr, "Usage : ./prog <input_file>\n");
      exit(1);
   }
   bl_arena* arena = (bl_arena*)malloc(sizeof(bl_arena));
   arena_init(arena);
   bl_token* tok_list = bl_tokenize_file(argv[argc - 1],arena);
   bl_token_list_print(tok_list,dynarray_length(tok_list));
}

#endif

bl_token *bl_tokenize(bl_lexer *lexer){
   char* character = &(lexer->input_stream[lexer->parse_point - lexer->input_stream]);
   bl_token *tok = (bl_token *)arena_alloc(lexer->arena, sizeof(bl_token));

  #ifdef BL_IDENTIFIERS


  while(*character == ' ' || *character == '\n' || *character == '\r'){
   bl_forward(lexer,1);
   UPDATE_CHAR_PTR();
  }

   if (*character && *character && (is_alpha(*character) || *character == '_'))
   {
      tok->where_firstchar = lexer->parse_point;
      bl_forward(lexer,1);
      while(*character && (is_alnum(*character) || *character == '_' || *character == '$')){
         UPDATE_CHAR_PTR();
         bl_forward(lexer,1);

      }
      bl_backward(lexer,1);
      tok->where_lastchar = lexer->parse_point;
      SET_DEFAULT_TOKEN(BL_IDENTIFIER);
   }
   /*DIGITS*/
   else if
   (*character && (*character >= '0' && *character <= '9'))
   {
      char buf[64];
      tok->where_firstchar = lexer->parse_point;
      while(*character && 
         (*character >= '0' && *character <= '9')
         ){
         UPDATE_CHAR_PTR();
         bl_forward(lexer,1);
      }
      bl_backward(lexer,1);
      if(*(lexer->parse_point) == '.'){
         bl_forward(lexer,1);
         UPDATE_CHAR_PTR();
         while(*character && (*character >= '0' && *character <= '9')){
            UPDATE_CHAR_PTR();
            bl_forward(lexer,1);
         }
         bl_backward(lexer,1);
         tok->where_lastchar = lexer->parse_point;

         int len = token_size(tok);
         memcpy(buf, tok->where_firstchar, len);
         buf[len] = '\0';

         SET_FLOAT_TOKEN(BL_FLOAT,strtod(buf,NULL));

      }else{
         tok->where_lastchar = lexer->parse_point;
         int len = token_size(tok);
         memcpy(buf, tok->where_firstchar, len);
         buf[len] = '\0';

         SET_INT_TOKEN(BL_INT,strtol(buf,NULL,10));
      }      
   }
   /*STRINGS*/
   else if 
   (*character && *character == '"')
   {
      tok->where_firstchar = lexer->parse_point;  
      bl_forward(lexer,1);  
      char *start = lexer->parse_point;

      while (lexer->parse_point < lexer->eof && *lexer->parse_point != '"') {
         UPDATE_CHAR_PTR();
         bl_forward(lexer,1);
         if(*lexer->parse_point == '\\'){
            bl_forward(lexer,2);
         }
      }
      int str_len = lexer->parse_point - start;
      if (lexer->parse_point < lexer->eof) {
         bl_forward(lexer,1); 
      }

      tok->where_lastchar = lexer->parse_point;

      if (lexer->string_storage_len >= str_len + 1){
         memcpy(lexer->string_storage, start, str_len);
         lexer->string_storage[str_len] = '\0';

         SET_STRING_TOKEN(BL_STRING,lexer->string_storage,str_len);

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
      char esc_char = bl_peek_token(lexer,1);

      switch(esc_char){
         case '\\':{
            bl_forward(lexer,4);
            tok->where_lastchar = lexer->parse_point;
            int str_len = 2;

            if(lexer->string_storage_len >= str_len+1){
               memcpy(lexer->string_storage,(tok->where_firstchar+1),str_len);
               lexer->string_storage[str_len] = '\0';
               SET_STRING_TOKEN(BL_CHAR,lexer->string_storage,str_len);

               lexer->string_storage += str_len +1;
               lexer->string_storage_len -= str_len +1;
            }else{
               fprintf(stderr, "String storage buffer overflow\n");
               tok->string = NULL;
               tok->string_len = 0;
            }
            break;
         }
         default: {
            bl_forward(lexer,3);
            tok->where_lastchar = lexer->parse_point;
            int str_len = 1;

            if(lexer->string_storage_len >= str_len+1){
               memcpy(lexer->string_storage,(tok->where_firstchar+1),str_len);
               lexer->string_storage[str_len] = '\0';
               SET_STRING_TOKEN(BL_CHAR,lexer->string_storage,str_len);

               lexer->string_storage += str_len +1;
               lexer->string_storage_len -= str_len +1;
            }else{
               fprintf(stderr, "String storage buffer overflow\n");
               tok->string = NULL;
               tok->string_len = 0;
            }
            break;
         }
      }
   }
   else 
   
   #endif //BL_IDENTIFIERS
   
   /*SEMICOLON*/
   if 
   (*character){
      switch (*character){
         #ifdef BL_SYMBOLS

         case ';' : SET_SIMPLE_TOKEN(BL_SEMICOLON); break;
         case ':' : SET_SIMPLE_TOKEN(BL_COLON); break;
         case '{' : SET_SIMPLE_TOKEN(BL_LBRACE); break;
         case '}' : SET_SIMPLE_TOKEN(BL_RBRACE); break;
         case '[' : SET_SIMPLE_TOKEN(BL_LBRACK); break;
         case ']' : SET_SIMPLE_TOKEN(BL_RBRACK); break;
         case '(' : SET_SIMPLE_TOKEN(BL_LPAREN); break;
         case ')' : SET_SIMPLE_TOKEN(BL_RPAREN); break;
         case ',' : SET_SIMPLE_TOKEN(BL_COMMA); break;

         #endif //BL_SYMBOLS

         #ifdef BL_OPERATORS
         char suff;
         case '=':
            suff = bl_peek_token(lexer,1);
            switch(suff){
               case '=': SET_COMPOUND_TOKEN(BL_ISEQUALCOND,2); break;
               default : SET_SIMPLE_TOKEN(BL_EQUAL); break;
            }
            break;

         case '!': 
            suff = bl_peek_token(lexer,1);
            switch(suff){
               case '=': SET_COMPOUND_TOKEN(BL_NOTEQ,2); break;
               default : SET_SIMPLE_TOKEN(BL_NOT); break;
            }
            break;

         case '+':
            suff = bl_peek_token(lexer,1);
            switch(suff){
               case '=': SET_COMPOUND_TOKEN(BL_ADDEQ,2); break;
               case '+': SET_COMPOUND_TOKEN(BL_INC,2); break;
               default : SET_SIMPLE_TOKEN(BL_ADDBINOP); break;
            }
            break;
         
         case '%':
            suff = bl_peek_token(lexer,1);
            switch(suff){
               case '=' : SET_COMPOUND_TOKEN(BL_MODEQ,2); break;
               default  : SET_SIMPLE_TOKEN(BL_MODBINOP); break;
            }
            break;

         case '-':
            suff = bl_peek_token(lexer,1);
            switch(suff){
               case '-' : SET_COMPOUND_TOKEN(BL_DEC,2); break;
               case '=' : SET_COMPOUND_TOKEN(BL_SUBEQ,2); break;
               default  : SET_SIMPLE_TOKEN(BL_SUBBINOP); break;
            }
            break;
         case '*':
            suff = bl_peek_token(lexer,1);
            switch(suff){
               case '=' : SET_COMPOUND_TOKEN(BL_MULTEQ,2); break;
               default  : SET_SIMPLE_TOKEN(BL_MULTBINOP); break;
            }
            break;
         case '/':
            suff = bl_peek_token(lexer,1);
            switch(suff){
               case '=' : SET_COMPOUND_TOKEN(BL_DIVEQ,2); break;
               case '/' : 
                  tok->where_firstchar = lexer->parse_point;
                  while(!is_newline(*character)){
                     UPDATE_CHAR_PTR();
                     bl_forward(lexer,1);
                  }
                  // printf("%c  ",*character);
                  bl_backward(lexer,1);
                  UPDATE_CHAR_PTR();
                  tok->where_lastchar = lexer->parse_point;
                  SET_DEFAULT_TOKEN(BL_COMMENT);
                  break;

               case '*' : 
                  tok->where_firstchar = lexer->parse_point;
                  bl_forward(lexer,2);
                  while(!((*character == '*') && (*(lexer->parse_point) == '/'))){
                     UPDATE_CHAR_PTR();
                     bl_forward(lexer,1);
                  }
                  bl_forward(lexer,1);
                  UPDATE_CHAR_PTR();
                  tok->where_lastchar = lexer->parse_point;
                  SET_DEFAULT_TOKEN(BL_MULCOMMENT);
                  break;

               default  : SET_SIMPLE_TOKEN(BL_DIVBINOP); break;
            }
            break;

         case '&':
            suff = bl_peek_token(lexer,1);
            switch(suff){
               case '=' : SET_COMPOUND_TOKEN(BL_ANDEQ,2); break;
               case '&' : SET_COMPOUND_TOKEN(BL_LOGAND,2); break;
               default  : SET_SIMPLE_TOKEN(BL_AND); break;
            }
            break;
         
         case '|':
            suff = bl_peek_token(lexer,1);
            switch(suff){
               case '=' : SET_COMPOUND_TOKEN(BL_OREQ,2); break;
               case '|' : SET_COMPOUND_TOKEN(BL_LOGOR,2); break;
               default  : SET_SIMPLE_TOKEN(BL_OR); break;
            }
            break;

         case '^':
            suff = bl_peek_token(lexer,1);
            switch(suff){
               case '=' : SET_COMPOUND_TOKEN(BL_XOREQ,2); break;
               default  : SET_SIMPLE_TOKEN(BL_XOR); break;
            }
            break;

         case '<':
            suff = bl_peek_token(lexer,1);
            switch(suff){
               case '=' : SET_COMPOUND_TOKEN(BL_LESSEQ,2); break;
               case '<' : SET_COMPOUND_TOKEN(BL_LSHIFT,2); break;
               default  : SET_SIMPLE_TOKEN(BL_LESSTHAN); break;
            }
            break;

         case '>':
            suff = bl_peek_token(lexer,1);
            switch(suff){
               case '=' : SET_COMPOUND_TOKEN(BL_GRTEQ,2); break;
               case '>' : SET_COMPOUND_TOKEN(BL_RSHIFT,2); break;
               default  : SET_SIMPLE_TOKEN(BL_GRTTHAN); break;
            }
            break;

         #endif //BL_OPERATORS

         default: SET_SIMPLE_TOKEN(BL_UNIMPLEMENTED); break;

         
      }
   }else {
      SET_SIMPLE_TOKEN(BL_EOF);
   }
   
   return tok;

}

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
   return (c == ' ');
}

static int is_newline(char c){
   return (c == '\n') || (c == '\r');
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
      while(is_whitespace(character) && is_newline(character)){
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
      while(is_whitespace(character) && is_newline(character)){
         character = l->input_stream[l->parse_point - l->input_stream - ++number];
      }
      count++;
      number++;
      printf("%c ",character);
      printf("\n");
   }while(count<=num);
   return character;
}


static void bl_set_token(bl_token* tok,enum KEYWORD_TYPES label, double real_number, long int_number, char* string, int string_len, int line_number, int line_offset){
   tok->token = label;
   tok->real_number = real_number;
   tok->int_number = int_number;
   tok->string = string;
   tok->string_len = string_len;
   tok->loc.line_number = line_number;
   tok->loc.line_offset = line_offset;
}


static void bl_forward(bl_lexer *lexer,int num){
   int count = 0;
   while(count < num){
      if (*lexer->parse_point == '\n') {
         lexer->current_line++;
         lexer->current_column = 1;
      } else {
         lexer->current_column++;
      }
      lexer->parse_point++;
      count++;
   }
}

static void bl_backward(bl_lexer *lexer,int num){
   int count = 0;
   while(count<num){
      lexer->current_column--;
      lexer->parse_point--;
      count++;
   }
}

void bl_lexer_init(bl_lexer *lexer, bl_arena* arena,const char *input_stream, const char *input_stream_end, char *string_store, int store_length){
   lexer->input_stream = (char *)input_stream;
   lexer->parse_point = (char *)input_stream;
   lexer->eof = (char *)input_stream_end;
   lexer->string_storage = string_store;
   lexer->string_storage_len = store_length;
   lexer->current_line = 1;
   lexer->current_column = 1;
   lexer->arena = arena;
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

#ifdef BL_DEBUG

char *keyword_enum_to_str(int var){
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
      case BL_COLON:
         return "BL_COLON";
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
      case BL_MODBINOP:
         return "BL_MODBINOP";
      case BL_DIVBINOP:
         return "BL_DIVBINOP";
      case BL_ADDEQ:
         return "BL_ADDEQ";  
      case BL_MODEQ:
         return "BL_MODEQ";        
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
      case BL_COMMENT:
         return "BL_COMMENT"; 
      case BL_MULCOMMENT:
         return "BL_MULCOMMENT";
      #endif //BL_OPERATORS

      case BL_KW_BYE_BHAU:
         return "BL_KW_BYE_BHAU";
      case BL_KW_HI_BHAU:
         return "BL_KW_HI_BHAU";
      case BL_KW_BHAU_HAI_AHE:
         return "BL_KW_BHAU_HAI_AHE";
      case BL_KW_BHAU_JAR:
         return "BL_KW_BHAU_JAR";
      case BL_KW_BHAU_TAR:
         return "case BL_KW_BHAU_TAR";
      case BL_KW_BHAU_NAHITAR:
         return "BL_KW_BHAU_NAHITAR";
      case BL_KW_BHAU_JOPARENT:
         return "case BL_KW_BHAU_JOPARENT";
      case BL_KW_BHAU_LAKSHAT_THEV:
         return "BL_KW_BHAU_LAKSHAT_THEV";
      case BL_KW_BHAU_PARAT_DE:
         return "KW_BHAU_PARAT_DE";
      case BL_KW_BHAU_CHUNAV:
         return "case BL_KW_BHAU_CHUNAV";
      case BL_KW_BHAU_THAMB:
         return "BL_KW_BHAU_THAMB";
      case BL_KW_BHAU_CHALU_RHA:
         return "BL_KW_BHAU_CHALU_RHA";
      case BL_KW_BHAU_RAHUDET:
         return "BL_KW_BHAU_RAHUDET";
      case BL_KW_BHAU_KHARA:
         return "BL_KW_BHAU_KHARA";
      case BL_KW_BHAU_KHOTA:
         return "BL_KW_BHAU_KHOTA";
      case BL_KW_BHAU_BAHERUN_GHE:
         return "BL_KW_BHAU_BAHERUN_GHE";
      case BL_KW_BHAU_MAIN:
         return "BL_KW_BHAU_MAIN";
      case BL_KW_BHAU_NIVAD:
         return "BL_KW_BHAU_NIVAD";
       case BL_KW_BHAU_PTR:
         return "BL_KW_BHAU_PTR";
      case BL_KW_BHAU_REF:
         return "BL_KW_BHAU_REF";
      default:
         return "<<UNKNOWN TOKEN>>";

      
   }
}


static inline void bl_token_print(const bl_token *tok) {
    printf("$ Token {\n");
    printf("   type          : %ld\n", tok->token);
    printf("   location      : line %d, offset %d\n", tok->loc.line_number, tok->loc.line_offset);
    printf("   chars         : '%.*s'\n",
           (int)(tok->where_lastchar - tok->where_firstchar),
           tok->where_firstchar);

    if (tok->string) {
        printf("   string value  : \"%.*s\" (len=%d)\n", tok->string_len, tok->string, tok->string_len);
    }

    if (tok->token == BL_INT) {
        printf("   int value     : %ld\n", tok->int_number);
    } else if (tok->token == BL_FLOAT) {
        printf("   float value   : %f\n", tok->real_number);
    }


    printf("}\n");
    printf("\n");
}

static inline void bl_token_list_print(bl_token *tokens, size_t count) {
    for (size_t i = 0; i < count; ++i) {
        printf("$ Token :%s:\n", keyword_enum_to_str(tokens[i].token));
        bl_token_print(&tokens[i]);
    }
}

static inline void bl_lexer_print(const bl_lexer *l) {
    printf("$ Lexer State:\n");
    printf("   input_stream      : %p\n", (void *)l->input_stream);
    printf("   eof               : %p\n", (void *)l->eof);
    printf("   parse_point       : %p\n", (void *)l->parse_point);
    printf("   recent char      : '%c'\n", *(l->parse_point-1));
    printf("   string_storage    : %p\n", (void *)l->string_storage);
    printf("   string_store_len  : %d\n", l->string_storage_len);
    printf("   current line      : %d\n", l->current_line);
    printf("   current column    : %d\n", l->current_column);
    printf("   arena             : %p\n", (void *)l->arena);
    printf("\n");
}


static inline void bl_token_dump_raw(const bl_token *tok) {
    const unsigned char *bytes = (const unsigned char *)tok;
    printf("$ Raw Token (%p):\n", (void *)tok);
    for (size_t i = 0; i < sizeof(bl_token); ++i) {
        printf("%02X ", bytes[i]);
        if ((i + 1) % 8 == 0) printf("\n");
    }
    printf("\n");
}

static inline void bl_token_debug_string(const bl_token *tok, char *buf, size_t bufsize) {
    snprintf(buf, bufsize,
             "[%s] \"%.*s\" at line %d, col %d",
             keyword_enum_to_str(tok->token),
             (int)(tok->where_lastchar - tok->where_firstchar),
             tok->where_firstchar,
             tok->loc.line_number,
             tok->loc.line_offset);
}

static inline void bl_lexer_peek_context(const bl_lexer *l, int chars_around) {
    char *start = l->parse_point - (chars_around);
    char *end = l->parse_point + (chars_around);

    if (start < l->input_stream) start = l->input_stream;
    if (end > l->eof) end = l->eof;

    printf("$ Lexer context (around parse_point):\n  ");
    for (char *p = start; p < end; p++) {
        if (p == l->parse_point) printf("|");  
        putchar(isprint(*p) ? *p : '.');
    }
    printf("\n");
}

static inline void bl_lexer_print_remaining(const bl_lexer *l) {
    printf("$ Remaining input:\n");
    const char *p = l->parse_point;
    while (p < l->eof) {
        putchar(isprint(*p) ? *p : ' ');
        p++;
    }
    printf("\n\n");
}

static inline void bl_token_verify_arena(const bl_token *tok, const bl_arena *arena) {
    if (!pointer_in_arena(tok, arena)) {
        printf("!! Token not in arena: %p\n",tok);
    }

}

static inline bl_token* bl_token_list_filter(bl_arena* arena,bl_token *tokens,size_t count,enum KEYWORD_TYPES type) {
    bl_token* temp_arr = dynarray_create_arena(bl_token,arena);
    for (size_t i = 0; i < count; ++i) {
        if (tokens[i].token == type) {
            // printf("🔎 [%zu] ", i);
            // bl_token_print(&tokens[i]);
            dynarray_push(temp_arr,tokens[i], bl_token);
        }
    }
    return temp_arr;
}

static inline void bl_token_list_revfilter(bl_token *tokens, bl_token* temp_arr,size_t count, enum KEYWORD_TYPES type){
   for (size_t i = 0; i < count; ++i){
      if(tokens[i].token != type){
         dynarray_push(temp_arr,tokens[i],bl_token);
      }
   }
}

static inline bl_token* bl_token_list_filter_multiple(bl_arena* arena,bl_token* tokens,size_t token_count,enum KEYWORD_TYPES* keyword_arr,size_t keyword_count){
   bl_token* temp_arr = dynarray_create_arena(bl_token,arena);
   for (size_t i = 0; i< token_count; ++i){
      for(size_t j = 0; j< keyword_count; ++j){
         if(tokens[i].token == keyword_arr[j]){
            dynarray_push(temp_arr,tokens[i],bl_token);
         }
      }
   }
   return temp_arr;
}

char* ptrs_to_string(const char* start, const char* end, bl_arena* arena){
    size_t len = end - start;
    char* str = (char *)arena_alloc(arena, len + 1); 
    memcpy(str, start, len);
    str[len] = '\0';
    return str;
}



#endif


char* bl_token_get_str(bl_token tok, char* buf) {
    memcpy(buf, tok.where_firstchar, tok.string_len);
    buf[tok.string_len] = '\0';
    return buf;
}

static inline enum KEYWORD_TYPES bl_token_get_type(bl_token token){
   return token.token;

}

/*-----------------------------------any preprocessing steps required for tokens list*/
static inline bl_token* bl_token_list_preprocess(bl_token* token_list){
   return token_list;
}
/*-----------------------------------------------------------------------------------*/

static inline bl_token* bl_tokenize_file(char* filename,bl_arena* arena){
   FILE *f = fopen(filename,"rb");
   char *text = (char*)arena_alloc(arena,TEXT_FILE_SIZE);
   int len =  f ? (int)fread(text, 1, TEXT_FILE_SIZE, f) : (int)-1;

   bl_lexer* l = (bl_lexer*)arena_alloc(arena,sizeof(bl_lexer));
   bl_token *da = dynarray_create_arena(bl_token,arena);
   bl_token *tok;

   if (len < 0) {
      fprintf(stderr, "Error opening file\n");
   }
   if(f != NULL){
      fclose(f);
   }

   char* string_store = (char *)arena_alloc(arena,1<<13);
   int string_store_len = 1<<13;
   bl_lexer_init(l,arena,text,text+len,string_store, string_store_len);

   do{
   tok = bl_tokenize(l);

   // bl_token_print(tok);      
   bl_next_step(l);
   dynarray_push(da,*tok,bl_token);

   }while(tok->token != (long)BL_EOF);

   da = bl_token_list_preprocess(da);

   return da;
}


#endif //INCLUDE_BL_TOKENIZER_H