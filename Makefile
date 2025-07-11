CC = gcc
CFLAGS_TOKENIZER = -Wall -Wextra -Isrc/common
CFLAGS_LEXER = -Wall -Wextra -Isrc/keywords -Isrc/common
CFLAGS_TEST = -Wall -Wextra -g -Isrc/common -Isrc/keywords
CFLAGS_PARSER = -Wall -Wextra -Isrc/lexer -Isrc/common -Isrc/keywords
CFLAGS_OPTIMIZER = -Wall -Wextra -Isrc/lexer -Isrc/common -Isrc/keywords
CFLAGS_IR = -Wall -Wextra -O0 -ggdb -Isrc/lexer -Isrc/common -Isrc/keywords -Isrc/parser
CFLAGS_CODEGEN = -Wall -Wextra -O0 -ggdb -Isrc/lexer -Isrc/common -Isrc/keywords -Isrc/parser -Isrc/ir


DYNARR = src/common/bl_dynarray.h
ARENA  = src/common/bl_arena.h
TOKENIZE = src/lexer/bl_tokenizer.h
LEXER = src/lexer/bl_lexer.h
PARSER = src/parser/bl_parser.h
OPTIMIZER = src/parser/bl_astOptimizer.h
IR = src/ir/bl_ir.h
LANGKEYS = src/keywords/bl_langkeywords.h


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

parser : $(LEXER)
	$(CC) $(CFLAGS_PARSER) src/parser/bl_parser.c -o src/parser/parser
	./src/parser/parser

optimizer: $(PARSER)
	$(CC) $(CFLAGS_OPTIMIZER) src/parser/bl_astOptimizer.c -o src/parser/astOptimizer
	./src/parser/astOptimizer

ir : $(OPTIMIZER)
	$(CC) $(CFLAGS_IR) src/ir/bl_ir.c -o src/ir/ir
	./src/ir/ir

codegen: $(IR)
	$(CC) $(CFLAGS_CODEGEN) src/codegen/codegen.c -o src/codegen/codegen
	./src/codegen/codegen

asm : $(CODEGEN)
	$(CC) $(CFLAGS_CODEGEN) src/codegen/codegen.c -o src/codegen/codegen
	./src/codegen/codegen
	nasm -f elf64 -o src/codegen/out.o src/codegen/out.asm
	gcc -no-pie -ggdb -o src/codegen/out src/codegen/out.o
	./src/codegen/out

	
clean : 
	rm -rf test reducer lexer parser src/lexer/reducer src/lexer/test src/lexer/lexer src/parser/parser src/parser/astOptimizer main
