#ifndef SIMPLE_SET_H
#define SIMPLE_SET_H

#include <stdbool.h>
#include <string.h>
#include "bl_arena.h"

typedef struct {
    char** items;
    size_t count;
    size_t capacity;
} bl_set;

#define SET_INITIAL_CAPACITY 1024

static inline bl_set* set_create(bl_arena* arena) {
    bl_set* set = (bl_set*)arena_alloc(arena, sizeof(bl_set));
    set->count = 0;
    set->capacity = SET_INITIAL_CAPACITY;
    set->items = (char**)arena_alloc(arena, sizeof(char*) * set->capacity);
    return set;
}

static inline bool set_contains(bl_set* set, const char* key) {
    for (size_t i = 0; i < set->count; ++i) {
        if (strcmp(set->items[i], key) == 0) {
            return true;
        }
    }
    return false;
}

static inline void set_insert(bl_set* set, const char* key, bl_arena* arena) {
    if (set_contains(set, key)) return;

    if (set->count >= set->capacity) {
        fprintf(stderr,"resizing not implemented in set");
        exit(69);
        return;
    }

    char* copy = (char*)arena_alloc(arena, strlen(key) + 1);
    strcpy(copy, key);
    set->items[set->count++] = copy;
}

static inline void set_print(bl_set* set) {
    printf("Set contains %zu item%s:\n", set->count, set->count == 1 ? "" : "s");
    for (size_t i = 0; i < set->count; ++i) {
        printf("  [%zu] %s\n", i, set->items[i]);
    }
}

#endif // SIMPLE_SET_H