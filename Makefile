CC = gcc
CFLAGS_TOKENIZER = -Wall -Wextra -Isrc/common -Isrc/keywords
CFLAGS_LEXER = -Wall -Wextra -Isrc/keywords -Isrc/common
CFLAGS_TEST = -Wall -Wextra -g -Isrc/common -Isrc/keywords
CFLAGS_PARSER = -Wall -Wextra -Isrc/lexer -Isrc/common -Isrc/keywords
CFLAGS_OPTIMIZER = -Wall -Wextra -Isrc/lexer -Isrc/common -Isrc/keywords
CFLAGS_IR = -Wall -Wextra -ggdb -Isrc/lexer -Isrc/common -Isrc/keywords -Isrc/parser
CFLAGS_CODEGEN = -Wall -Wextra -O0 -ggdb -Isrc/lexer -Isrc/common -Isrc/keywords -Isrc/parser -Isrc/ir
CFLAGS_MAIN = -Wall -Wextra -ggdb -Isrc/lexer -Isrc/common -Isrc/keywords -Isrc/parser -Isrc/ir -Isrc/codegen


DYNARR = src/common/bl_dynarray.h
ARENA  = src/common/bl_arena.h
TOKENIZE = src/lexer/bl_tokenizer.h
LEXER = src/lexer/bl_lexer.h
PARSER = src/parser/bl_parser.h
OPTIMIZER = src/parser/bl_astOptimizer.h
IR = src/ir/bl_ir.h
LANGKEYS = src/keywords/bl_langkeywords.h
CODEGEN = src/codegen/bl_codegen.h


.phony : clean

compile: $(CODEGEN)
	@ mkdir -p __blcache__
	@ $(CC) $(CFLAGS_MAIN) bl_compiler.c -o __blcache__/main
	@ ./__blcache__/main $(INPUT) __blcache__/out.asm
	@ nasm -f elf64 -o __blcache__/out.o __blcache__/out.asm
	@ gcc -no-pie -ggdb -o $(basename $(notdir $(INPUT))) __blcache__/out.o
	@ rm -rf __blcache__

tokenize  : $(DYNARR) $(ARENA) 
	@ $(CC) $(CFLAGS_TOKENIZER) src/lexer/bl_tokenizer.c -o ./out
	./out $(INPUT)

lexer : $(TOKENIZE) $(LANKEYS)
	@ $(CC) $(CFLAGS_LEXER) src/lexer/bl_lexer.c -o ./out
	./out $(INPUT)

parser : $(LEXER)
	$(CC) $(CFLAGS_PARSER) src/parser/bl_parser.c -o ./out
	./out $(INPUT)

optimizer: $(PARSER)
	$(CC) $(CFLAGS_OPTIMIZER) src/parser/bl_astOptimizer.c -o ./out
	./out $(INPUT)

ir : $(OPTIMIZER)
	$(CC) $(CFLAGS_IR) src/ir/bl_ir.c -o ./out
	./out $(INPUT)

codegen: $(IR)
	$(CC) $(CFLAGS_CODEGEN) src/codegen/bl_codegen.c -o src/codegen/codegen
	./src/codegen/codegen
	nasm -f elf64 -o src/codegen/out.o src/codegen/out.asm
	gcc -no-pie -ggdb -o src/codegen/out src/codegen/out.o
	./src/codegen/out

asm : $(CODEGEN)
	@ mkdir -p __blcache__
	@ $(CC) $(CFLAGS_MAIN) bl_compiler.c -o __blcache__/main
	@ ./__blcache__/main $(INPUT) $(basename $(notdir $(INPUT))).asm
	@ rm -rf __blcache__
	
clean : 
	@ rm patterns low_stress_test high_stress_test recursion multiple_funcs scope_resolution one floats mixed_literals
