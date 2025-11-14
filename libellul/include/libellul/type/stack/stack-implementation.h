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

TYPE(T, datum_t) METHOD(T, datum_t, new) (void) {return METHOD(deque, datum_t, new) ();}

int METHOD(T, datum_t, is_empty) (TYPE(T, datum_t) stack) {return METHOD(deque, datum_t, is_empty) (stack);}

int METHOD(T, datum_t, length) (TYPE(T, datum_t) stack) {return METHOD(deque, datum_t, length) (stack);}

datum_t METHOD(T, datum_t, first) (TYPE(T, datum_t) stack) {return METHOD(deque, datum_t, first) (stack);}

TYPE(T, datum_t) METHOD(T, datum_t, push) (datum_t value, TYPE(T, datum_t) stack) {return METHOD(deque, datum_t, push_front) (value, stack);}

TYPE(T, datum_t) METHOD(T, datum_t, pop) (datum_t *value, TYPE(T, datum_t) stack) {return METHOD(deque, datum_t, pop_front) (value, stack);}

TYPE(T, datum_t) METHOD(T, datum_t, delete) (TYPE(T, datum_t) stack, void (*destructor) (datum_t)){return METHOD(deque, datum_t, delete) (stack, destructor);}

void METHOD(T, datum_t, print) (TYPE(T, datum_t) stack){METHOD(deque, datum_t, print) (stack);}


#undef T

#endif