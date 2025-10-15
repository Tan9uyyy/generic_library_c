#ifndef _STACK_IMPLEMENTATION_H__
#define _STACK_IMPLEMENTATION_H__

#ifndef datum_t
    #error "Undefined datum type !"
#endif

#define T stack

#include "../deque.h"
#include "../../interface.h"

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

typedef TYPE(deque, datum_t) TYPE(T, datum_t);

TYPE(T, datum_t) METHOD(T, new) (void) {return METHOD(deque, new) ();}

int METHOD(T, is_empty) (TYPE(T, datum_t) stack) {return METHOD(deque, is_empty) (stack);}

datum_t METHOD(T, first) (TYPE(T, datum_t) stack) {return METHOD(deque, first) (stack);}

TYPE(T, datum_t) METHOD(T, push) (datum_t value, TYPE(T, datum_t) stack) {return METHOD(deque, push_front) (value, stack);}

TYPE(T, datum_t) METHOD(T, pop) (datum_t *value, TYPE(T, datum_t) stack) {return METHOD(deque, pop_front) (value, stack);}

TYPE(T, datum_t) METHOD(T, delete) (TYPE(T, datum_t) stack, void (*destructor) (datum_t)){return METHOD(deque, delete) (stack, destructor);}

void METHOD(T, print) (TYPE(T, datum_t) stack){METHOD(deque, print) (stack);}


#undef T

#endif