CC = gcc

lexer : bl_dynarray.h bl_arena.h bl_tokenizer.c
	$(CC) bl_lexer.c -o lexer
	./lexer

test : bl_dynarray.h bl_tokenizer.h bl_arena.h test.c
	$(CC) test.c -o test
	./test

clean : 
	rm -rf lexer test arena