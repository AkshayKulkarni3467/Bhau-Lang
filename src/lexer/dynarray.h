#ifndef DYNARRAY
#define DYNARRAY

#include <stdlib.h>     
#include <string.h>    

#define DYNARRAY_DEFAULT_CAP 1
#define DYNARRAY_RESIZE_FACTOR 2

#define dynarray_create(type) _dynarray_create(DYNARRAY_DEFAULT_CAP, sizeof(type))
#define dynarray_create_prealloc(type, capacity) _dynarray_create(capacity, sizeof(type))
#define dynarray_destroy(arr) _dynarray_destroy(arr)

#define dynarray_push(arr, x) arr = _dynarray_push(arr, &x)
#define dynarray_push_rval(arr, x) \
    do { \
        __auto_type temp = x; \
        arr = _dynarray_push(arr, &temp); \
    } while (0)

#define dynarray_pop(arr, xptr) _dynarray_pop(arr, xptr)

#define dynarray_capacity(arr) _dynarray_field_get(arr, CAPACITY)
#define dynarray_length(arr) _dynarray_field_get(arr, LENGTH)
#define dynarray_stride(arr) _dynarray_field_get(arr, STRIDE)

enum {
    CAPACITY,
    LENGTH,
    STRIDE,
    DYNARRAY_FIELDS
};

void *_dynarray_create(size_t length, size_t stride){
    size_t header_size = DYNARRAY_FIELDS * sizeof(size_t);
    size_t arr_size = length * stride;
    size_t *arr = (size_t *) malloc(header_size + arr_size);
    arr[CAPACITY] = length;
    arr[LENGTH] = 0;
    arr[STRIDE] = stride;
    return (void *) (arr + DYNARRAY_FIELDS);
}
void _dynarray_destroy(void *arr){
    free(arr - DYNARRAY_FIELDS * sizeof(size_t));
}

size_t _dynarray_field_get(void *arr, size_t field){
    return ((size_t *)(arr) - DYNARRAY_FIELDS)[field];
}

void _dynarray_field_set(void *arr, size_t field, size_t value){
    ((size_t *)(arr) - DYNARRAY_FIELDS)[field] = value;
}

void *_dynarray_resize(void *arr){
    void *temp = _dynarray_create( 
        DYNARRAY_RESIZE_FACTOR * dynarray_capacity(arr),
        dynarray_stride(arr)
    );
    memcpy(temp, arr, dynarray_length(arr) * dynarray_stride(arr)); 
    _dynarray_field_set(temp, LENGTH, dynarray_length(arr)); 
    _dynarray_destroy(arr);
    return temp;
}

void *_dynarray_push(void *arr, void *xptr){
    if (dynarray_length(arr) >= dynarray_capacity(arr))
        arr = _dynarray_resize(arr);

    memcpy(arr + dynarray_length(arr) * dynarray_stride(arr), xptr, dynarray_stride(arr));
    _dynarray_field_set(arr, LENGTH, dynarray_length(arr) + 1);
    return arr;
}

void _dynarray_pop(void *arr, void *dest){
    memcpy(dest, arr + (dynarray_length(arr) - 1) * dynarray_stride(arr), dynarray_stride(arr));
    _dynarray_field_set(arr, LENGTH, dynarray_length(arr) - 1); 
}




#endif // DYNARRAY

