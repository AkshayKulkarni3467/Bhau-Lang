#ifndef DYNARRAY
#define DYNARRAY

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include "bl_arena.h"

#define DYNARRAY_DEFAULT_CAP 1
#define DYNARRAY_RESIZE_FACTOR 2

#define dynarray_create(type) \
    _dynarray_create(DYNARRAY_DEFAULT_CAP, sizeof(type), NULL)

#define dynarray_create_prealloc(type, capacity) \
    _dynarray_create(capacity, sizeof(type), NULL)

#define dynarray_create_arena(type, arena) \
    _dynarray_create(DYNARRAY_DEFAULT_CAP, sizeof(type), arena)


#define dynarray_destroy(arr) \
    if (!_dynarray_is_arena_backed(arr)) _dynarray_destroy(arr)

#define dynarray_push(arr, x, type) \
    do { \
        type _tmp = (x); \
        (arr) = _dynarray_push((arr), &_tmp); \
    } while (0)

#define dynarray_capacity(arr) _dynarray_field_get(arr, CAPACITY)
#define dynarray_length(arr) _dynarray_field_get(arr, LENGTH)
#define dynarray_stride(arr) _dynarray_field_get(arr, STRIDE)
#define dynarray_copy(arr) _dynarray_copy(arr)

enum {
    CAPACITY,
    LENGTH,
    STRIDE,
    IS_ARENA,
    ARENA_PTR,
    DYNARRAY_FIELDS
};

static inline void *_dynarray_create(size_t cap, size_t stride, bl_arena *arena) {
    size_t header_size = DYNARRAY_FIELDS * sizeof(size_t);
    size_t total = header_size + cap * stride;
    
    if (arena) {
        if (total > ARENA_BLOCK_SIZE) {
            fprintf(stderr, "Error: dynarray allocation size %zu exceeds arena block size %d\n",
                    total, ARENA_BLOCK_SIZE);
            fprintf(stderr, "Increase ARENA_BLOCK_SIZE to at least %zu\n", total);
            exit(69);
        }
        
        size_t *raw = (size_t *)arena_alloc(arena, total);
        if (!raw) return NULL;
        
        raw[CAPACITY] = cap;
        raw[LENGTH] = 0;
        raw[STRIDE] = stride;
        raw[IS_ARENA] = 1;
        raw[ARENA_PTR] = (size_t)arena;
        
        return (void *)(raw + DYNARRAY_FIELDS);
    } else {
        size_t *raw = (size_t *)malloc(total);
        if (!raw) return NULL;
        
        raw[CAPACITY] = cap;
        raw[LENGTH] = 0;
        raw[STRIDE] = stride;
        raw[IS_ARENA] = 0;
        raw[ARENA_PTR] = 0;
        
        return (void *)(raw + DYNARRAY_FIELDS);
    }
}

static inline void _dynarray_destroy(void *arr) {
    free((size_t *)arr - DYNARRAY_FIELDS);
}

static inline size_t _dynarray_field_get(void *arr, size_t field) {
    return ((size_t *)arr - DYNARRAY_FIELDS)[field];
}

static inline void _dynarray_field_set(void *arr, size_t field, size_t value) {
    ((size_t *)arr - DYNARRAY_FIELDS)[field] = value;
}

static inline int _dynarray_is_arena_backed(void *arr) {
    return _dynarray_field_get(arr, IS_ARENA);
}

static inline void *_dynarray_resize(void *arr) {
    size_t old_cap = dynarray_capacity(arr);
    size_t old_len = dynarray_length(arr);
    size_t stride = dynarray_stride(arr);
    size_t new_cap = old_cap * DYNARRAY_RESIZE_FACTOR;
    
    if (_dynarray_is_arena_backed(arr)) {
        size_t header_size = DYNARRAY_FIELDS * sizeof(size_t);
        size_t new_total = header_size + new_cap * stride;
        
        if (new_total > ARENA_BLOCK_SIZE) {
            fprintf(stderr, "Error: dynarray resize to %zu bytes exceeds arena block size %d\n",
                    new_total, ARENA_BLOCK_SIZE);
            fprintf(stderr, "Increase ARENA_BLOCK_SIZE to at least %zu\n", new_total);
            exit(69);
        }

        bl_arena *arena = (bl_arena *)_dynarray_field_get(arr, ARENA_PTR);
        
        void *new_arr = _dynarray_create(new_cap, stride, arena);
        if (!new_arr) return NULL;
        
        memcpy(new_arr, arr, old_len * stride);
        _dynarray_field_set(new_arr, LENGTH, old_len);
        
        return new_arr;
    } else {
        size_t header_size = DYNARRAY_FIELDS * sizeof(size_t);
        size_t *raw = (size_t *)realloc(
            (size_t *)arr - DYNARRAY_FIELDS, 
            header_size + new_cap * stride
        );
        if (!raw) return NULL;
        
        raw[CAPACITY] = new_cap;
        void *new_arr = (void *)(raw + DYNARRAY_FIELDS);
        _dynarray_field_set(new_arr, LENGTH, old_len);
        
        return new_arr;
    }
}

static inline void *_dynarray_push(void *arr, void *xptr) {
    if (dynarray_length(arr) >= dynarray_capacity(arr)) {
        arr = _dynarray_resize(arr);
        if (!arr) return NULL;
    }

    size_t len = dynarray_length(arr);
    size_t stride = dynarray_stride(arr);
    memcpy((char *)arr + len * stride, xptr, stride);
    _dynarray_field_set(arr, LENGTH, len + 1);
    return arr;
}

static inline void* _dynarray_copy(void* arr) {
    if (!arr) return NULL;

    size_t cap = dynarray_capacity(arr);
    size_t len = dynarray_length(arr);
    size_t stride = dynarray_stride(arr);

    // Allocate new heap-based dynarray
    void* new_arr = _dynarray_create(cap, stride, NULL);
    if (!new_arr) return NULL;

    // Copy data
    memcpy(new_arr, arr, len * stride);

    // Set metadata
    _dynarray_field_set(new_arr, LENGTH, len);

    return new_arr;
}

#endif // DYNARRAY