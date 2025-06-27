#ifndef ARENA_H
#define ARENA_H

#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>

//WARN if using dynarray_create_arena(..) allocate a proper chunck in which the entire dynarray can fit
//WARN there can be multiple error msgs due to multiple resizes in various funcs
#ifndef ARENA_BLOCK_SIZE
#define ARENA_BLOCK_SIZE 1024*1024*4
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
static inline void arena_print(const bl_arena *arena);
static inline void arena_check_overlap(const bl_arena *arena);
static inline void arena_dump_hex(const bl_arena *arena);
static inline void arena_verify_alignment(const bl_arena *arena, size_t alignment);
static inline void arena_stats(const bl_arena *arena);
static inline void arena_inspect_pointers(const bl_arena *arena);
static inline int pointer_in_arena(const void *ptr, const bl_arena *arena);
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

static inline void arena_print(const bl_arena *arena){
    const arena_block *block = arena->head;
    int block_index = 0;

    while (block) {
        printf("🧱 Block %d: used %zu / %zu bytes\n", block_index, block->used, ARENA_BLOCK_SIZE);

        for (size_t i = 0; i < block->used; i++) {
            unsigned char byte = block->memory[i];
            if (isprint(byte))
                printf("%c", byte);
            else
                printf("\\x%02X", byte);  // print non-printables as hex
        }
        printf("\n\n");

        block = block->next;
        block_index++;
    }
}

static inline void arena_stats(const bl_arena *arena) {
    const arena_block *block = arena->head;
    int blocks = 0;
    size_t total_used = 0;

    while (block) {
        total_used += block->used;
        blocks++;
        block = block->next;
    }

    size_t total_capacity = blocks * ARENA_BLOCK_SIZE;

    printf("📊 Arena Stats:\n");
    printf("  Blocks       : %d\n", blocks);
    printf("  Used bytes   : %zu\n", total_used);
    printf("  Capacity     : %zu\n", total_capacity);
    printf("  Utilization  : %.2f%%\n",
        total_capacity ? 100.0 * total_used / total_capacity : 0.0);
}

static inline void arena_verify_alignment(const bl_arena *arena, size_t alignment) {
    const arena_block *block = arena->head;

    while (block) {
        uintptr_t addr = (uintptr_t)(block->memory + block->used);
        if (addr % alignment != 0) {
            printf("❌ Misaligned allocation: address = %p (alignment = %zu)\n", (void *)addr, alignment);
        }
        block = block->next;
    }
}

static inline void arena_dump_hex(const bl_arena *arena) {
    const arena_block *block = arena->head;
    int block_index = 0;

    while (block) {
        printf("🔍 Hex Dump of Block %d (%zu bytes used):\n", block_index, block->used);
        for (size_t i = 0; i < block->used; i++) {
            printf("%02X ", (unsigned char)block->memory[i]);
            if ((i + 1) % 16 == 0) printf("\n");
        }
        if (block->used % 16 != 0) printf("\n");
        printf("\n");
        block = block->next;
        block_index++;
    }
}

static inline void arena_check_overlap(const bl_arena *arena) {
    const arena_block *a = arena->head;
    while (a) {
        uintptr_t a_start = (uintptr_t)a->memory;
        uintptr_t a_end = a_start + ARENA_BLOCK_SIZE;

        const arena_block *b = a->next;
        while (b) {
            uintptr_t b_start = (uintptr_t)b->memory;
            uintptr_t b_end = b_start + ARENA_BLOCK_SIZE;

            if ((a_start < b_end) && (b_start < a_end)) {
                printf("❌ Overlap detected between blocks!\n");
            }

            b = b->next;
        }
        a = a->next;
    }
}

static inline void arena_inspect_pointers(const bl_arena *arena) {
    const arena_block *block = arena->head;
    int block_index = 0;

    while (block) {
        printf("🔍 Inspecting Block %d:\n", block_index);
        size_t used = block->used;

        /*Aligned at 8 bytes (remember size = size + 7 & ~7)*/
        for (size_t i = 0; i + sizeof(void *) <= used; i += 8) {
            void **ptr_addr = (void **)(block->memory + i);
            void *maybe_ptr = *ptr_addr;

            /*Nulls and low addresses?*/
            if ((uintptr_t)maybe_ptr < 0x1000) continue;

            printf("Found possible pointer at offset %3zu -> %p\n", i, maybe_ptr);

            /*-------------------------unsafe, may result in seg fault*/
            // uintptr_t *target = (uintptr_t *)maybe_ptr;
            // printf(" | points to: 0x%" PRIxPTR "\n", *target);
        }

        block = block->next;
        block_index++;
    }
}

static inline int pointer_in_arena(const void *ptr, const bl_arena *arena) {
    const arena_block *block = arena->head;
    while (block) {
        uintptr_t base = (uintptr_t)block->memory;
        uintptr_t end = base + ARENA_BLOCK_SIZE;
        if ((uintptr_t)ptr >= base && (uintptr_t)ptr < end)
            return 1;
        block = block->next;
    }
    return 0;
}

#endif // ARENA_H
