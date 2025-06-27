CC = gcc
CFLAGS_TOKENIZER = -Isrc/common
CFLAGS_LEXER = -Isrc/keywords -Isrc/common
CFLAGS_TEST = -g -Isrc/common -Isrc/keywords
CFLAGS_PARSER = -Isrc/lexer -Isrc/common -Isrc/keywords


DYNARR = src/common/bl_dynarray.h
ARENA  = src/common/bl_arena.h

TOKENIZE = src/lexer/bl_tokenizer.h
LEXER = src/lexer/bl_lexer.h

LANGKEYS = src/keywords/bl_langkeywords.h

# lexer : $(DYNARR) $(ARENA) bl_tokenizer.c
# 	$(CC) bl_lexer.c -o lexer
# 	./lexer

.phony : clean

tokenize  : $(DYNARR) $(ARENA) $(TOKENIZE) src/lexer/test.c
	$(CC) $(CFLAGS_TOKENIZER) src/lexer/test.c -o src/lexer/test
	./src/lexer/test

lexer : $(TOKENIZE) $(LANKEYS) src/lexer/bl_lexer.c
	$(CC) $(CFLAGS_LEXER) src/lexer/bl_lexer.c -o src/lexer/lexer
	./src/lexer/lexer

test : $(LEXER)
	$(CC) $(CFLAGS_TEST) src/lexer/test.c -o src/lexer/test
	./src/lexer/test

make parser : $(LEXER)
	$(CC) $(CFLAGS_PARSER) src/parser/parser.c -o src/parser/parser
	./src/parser/parser

clean : 
	rm -rf test reducer lexer parser src/lexer/reducer src/lexer/test src/lexer/lexer src/parser/parser