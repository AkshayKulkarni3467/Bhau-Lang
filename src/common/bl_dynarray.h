#ifndef DYNARRAY
#define DYNARRAY

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "bl_arena.h"

#define DYNARRAY_DEFAULT_CAP 1
#define DYNARRAY_RESIZE_FACTOR 2

#define dynarray_create(type) \
    _dynarray_create(DYNARRAY_DEFAULT_CAP, sizeof(type), NULL)

#define dynarray_create_prealloc(type, capacity) \
    _dynarray_create(capacity, sizeof(type), NULL)

#define dynarray_create_arena(type, arena) \
    _dynarray_create(DYNARRAY_DEFAULT_CAP, sizeof(type), arena)

#define dynarray_create_arena_prealloc(type, arena, capacity) \
    _dynarray_create(capacity, sizeof(type), arena)

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

enum {
    CAPACITY,
    LENGTH,
    STRIDE,
    IS_ARENA,
    DYNARRAY_FIELDS
};


static inline void *_dynarray_create(size_t cap, size_t stride, bl_arena *arena) {
    size_t header_size = DYNARRAY_FIELDS * sizeof(size_t);
    size_t total = header_size + cap * stride;
    size_t *raw;

    if (arena) {
        raw = (size_t *)arena_alloc(arena, total);
        if (!raw) return NULL;
        raw[IS_ARENA] = 1;
    } else {
        raw = (size_t *)malloc(total);
        if (!raw) return NULL;
        raw[IS_ARENA] = 0;
    }

    raw[CAPACITY] = cap;
    raw[LENGTH] = 0;
    raw[STRIDE] = stride;

    return (void *)(raw + DYNARRAY_FIELDS);
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
    /*Didnt find a solution to resize from arena directly...*/
    if (_dynarray_is_arena_backed(arr)) {
        assert(0 && "Arena-backed dynarray cannot be resized");
        return arr;
    }

    size_t old_len = dynarray_length(arr);
    size_t new_cap = dynarray_capacity(arr) * DYNARRAY_RESIZE_FACTOR;
    void *temp = _dynarray_create(new_cap, dynarray_stride(arr), NULL);
    memcpy(temp, arr, old_len * dynarray_stride(arr));
    _dynarray_field_set(temp, LENGTH, old_len);
    _dynarray_destroy(arr);
    return temp;
}

static inline void *_dynarray_push(void *arr, void *xptr) {
    if (dynarray_length(arr) >= dynarray_capacity(arr)) {
        arr = _dynarray_resize(arr);
    }

    size_t len = dynarray_length(arr);
    memcpy((char *)arr + len * dynarray_stride(arr), xptr, dynarray_stride(arr));
    _dynarray_field_set(arr, LENGTH, len + 1);
    return arr;
}

#endif // DYNARRAY

