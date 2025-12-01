#ifndef _STACK_IMPLEMENTATION_H__
#define _STACK_IMPLEMENTATION_H__

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#include "stack-export-def.h"

#define T stack

typedef TYPE(deque, stack_datum_t) TYPE(T, stack_datum_t);

TYPE(T, stack_datum_t) METHOD(T, stack_datum_t, new) (void) {return METHOD(deque, stack_datum_t, new) ();}

int METHOD(T, stack_datum_t, is_empty) (TYPE(T, stack_datum_t) stack) {return METHOD(deque, stack_datum_t, is_empty) (stack);}

int METHOD(T, stack_datum_t, length) (TYPE(T, stack_datum_t) stack) {return METHOD(deque, stack_datum_t, length) (stack);}

stack_datum_t METHOD(T, stack_datum_t, first) (TYPE(T, stack_datum_t) stack) {return METHOD(deque, stack_datum_t, first) (stack);}

TYPE(T, stack_datum_t) METHOD(T, stack_datum_t, push) (stack_datum_t value, TYPE(T, stack_datum_t) stack) {
    return METHOD(deque, stack_datum_t, push_front) (value, stack);
}

TYPE(T, stack_datum_t) METHOD(T, stack_datum_t, pop) (stack_datum_t *value, TYPE(T, stack_datum_t) stack, void (*destructor)(stack_datum_t)) {
    return METHOD(deque, stack_datum_t, pop_front) (value, stack, destructor);
}

TYPE(T, stack_datum_t) METHOD(T, stack_datum_t, delete) (TYPE(T, stack_datum_t) stack, void (*destructor) (stack_datum_t)){
    return METHOD(deque, stack_datum_t, delete) (stack, destructor);
}

void METHOD(T, stack_datum_t, print) (TYPE(T, stack_datum_t) stack, void (*printer)(stack_datum_t)){
    METHOD(deque, stack_datum_t, print) (stack, printer);
}


#undef T

#endif