CC = gcc

lexer : dynarray.h bl_lexer.c
	$(CC) bl_lexer.c -o lexer
	./lexer

test : dynarray.h bl_lexer.h test.c
	$(CC) test.c -o test
	./test

clean : 
	rm -rf lexer test