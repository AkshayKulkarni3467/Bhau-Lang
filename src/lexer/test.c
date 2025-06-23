#include "bl_lexer.h"
#include "dynarray.h"
#include <stdlib.h>
#include <stdio.h>

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