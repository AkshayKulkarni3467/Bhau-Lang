#ifndef STACK_H
#define STACK_H

#include <stddef.h>
#include "bl_arena.h"


typedef struct {
    void **items;
    size_t top;
    size_t capacity;
    bl_arena *arena;
} bl_stack;

static inline size_t stack_size(bl_stack *stack);

static inline void stack_init(bl_stack *stack, bl_arena *arena, size_t initial_capacity) {
    stack->arena = arena;
    stack->items = (void **)arena_alloc(arena, sizeof(void *) * initial_capacity);
    stack->top = 0;
    stack->capacity = initial_capacity;
}

static inline void *stack_get_index(bl_stack *stack, int num){
    if(num > ((int)stack_size(stack) - 1)){
        fprintf(stderr, "Index out of bounds of stack size");
        exit(1);
    }
    
    return stack->items[num];
}

static inline void stack_push(bl_stack *stack, void *item) {
    if (stack->top >= stack->capacity) {
        size_t new_capacity = stack->capacity * 2;
        void **new_items = (void **)arena_alloc(stack->arena, sizeof(void *) * new_capacity);
        for (size_t i = 0; i < stack->top; ++i) {
            new_items[i] = stack->items[i];
        }
        stack->items = new_items;
        stack->capacity = new_capacity;
    }
    stack->items[stack->top++] = item;
}

static inline void *stack_pop(bl_stack *stack) {
    if (stack->top == 0) return NULL;
    return stack->items[--stack->top];
}

static inline void *stack_peek(bl_stack *stack) {
    if (stack->top == 0) return NULL;
    return stack->items[stack->top - 1];
}

static inline int stack_empty(bl_stack *stack) {
    return stack->top == 0;
}

static inline size_t stack_size(bl_stack *stack) {
    return stack->top;
}

#endif // STACK_H