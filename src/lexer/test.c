#include <stdlib.h>
#include <stdio.h>

#include "bl_tokenizer.h"


int main(){
   bl_arena* arena;
   arena_init(arena);

   bl_token* da = bl_tokenize_file("one.bl",arena);

   bl_token_list_print(da,dynarray_length(da));
   

   return 0;
}