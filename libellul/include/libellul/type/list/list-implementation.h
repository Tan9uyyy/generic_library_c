#ifndef _LIST_IMPLEMENTATION_H__
#define _LIST_IMPLEMENTATION_H__

#ifndef datum_t
    #error "Undefined datum type !"
#endif

#define T list

#include "../deque.h"
#include "../../interface.h"

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

typedef TYPE(deque, datum_t) TYPE(T, datum_t);

TYPE(T, datum_t) METHOD(T, new) (void) {return METHOD(deque, new) ();}

int METHOD(T, is_empty) (TYPE(T, datum_t) list) {return METHOD(deque, is_empty) (list);}

int METHOD(T, length) (TYPE(T, datum_t) list) {return METHOD(deque, length) (list);}

TYPE(T, datum_t) METHOD(T, push) (datum_t value, TYPE(T, datum_t) list) {return METHOD(deque, push_back) (value, list);}

TYPE(T, datum_t) METHOD(T, pop) (datum_t *value, TYPE(T, datum_t) list) {return METHOD(deque, pop_back) (value, list);}

TYPE(T, datum_t) METHOD(T, delete) (TYPE(T, datum_t) list, void (*destructor) (datum_t)){return METHOD(deque, delete) (list, destructor);}

void METHOD(T, print) (TYPE(T, datum_t) list){METHOD(deque, print) (list);}


#undef T

#endif