#include <stdlib.h>
#include <stdio.h>

#include "bl_lexer.h"



int main(){

   bl_arena* arena = (bl_arena*)malloc(sizeof(bl_arena));
   arena_init(arena);

   bl_token *da = bhaulang_lexer("src/lexer/one.bl",arena);
   bl_token_list_print(da,dynarray_length(da));
   printf("\n");
   arena_stats(arena);
}