#ifndef ARENA_H
#define ARENA_H

#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>

#ifndef ARENA_BLOCK_SIZE
#define ARENA_BLOCK_SIZE 4096
#endif



typedef struct arena_block {
    struct arena_block *next;
    size_t used;
    char memory[ARENA_BLOCK_SIZE];
} arena_block;

typedef struct {
    arena_block *head;
} bl_arena;

/*--------------------------------------------function defines*/
static inline void arena_init(bl_arena* arena);
static inline arena_block *arena_new_block();
static inline void *arena_alloc(bl_arena *arena, size_t size);
static inline void arena_reset(bl_arena *arena);
static inline void arena_free(bl_arena *arena);
/*-----------------------------------------------------------*/



static inline void arena_init(bl_arena *arena) {     
    arena->head = (arena_block *)malloc(sizeof(arena_block));
    if (arena->head) {
        arena->head->next = NULL;
        arena->head->used = 0;
    }
}

static inline arena_block *arena_new_block() {
    arena_block *block = (arena_block *)malloc(sizeof(arena_block));
    if (block) {
        block->next = NULL;
        block->used = 0;
    }
    return block;
}

static inline void *arena_alloc(bl_arena *arena, size_t size) {
    /*Always align to 8 bytes....*/
    size = (size + 7) & ~7; 
    arena_block *block = arena->head;

    while (block) {
        if (ARENA_BLOCK_SIZE - block->used >= size) {
            void *mem = &block->memory[block->used];
            block->used += size;
            return mem;
        }
        if (!block->next) {
            block->next = arena_new_block();
            if (!block->next) return NULL;
        }
        block = block->next;
    }
    return NULL; 
}

static inline void arena_reset(bl_arena *arena) {
    arena_block *block = arena->head;
    if (block) {
        block->used = 0;
        block = block->next;
    }
    while (block) {
        block->used = 0;
        block = block->next;
    }
}

static inline void arena_free(bl_arena *arena) {
    arena_block *block = arena->head;
    while (block) {
        arena_block *next = block->next;
        free(block);
        block = next;
    }
    arena->head = NULL;
}

#endif // ARENA_H
