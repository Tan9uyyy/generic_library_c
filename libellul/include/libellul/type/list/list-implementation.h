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

TYPE(T, datum_t) METHOD(T, datum_t, new) (void) {return METHOD(deque, datum_t, new) ();}

int METHOD(T, datum_t, is_empty) (TYPE(T, datum_t) list) {return METHOD(deque, datum_t, is_empty) (list);}

int METHOD(T, datum_t, length) (TYPE(T, datum_t) list) {return METHOD(deque, datum_t, length) (list);}

datum_t METHOD(T, datum_t, get) (TYPE(T, datum_t) list, int index) {return METHOD(deque, datum_t, get) (list, index);}

TYPE(T, datum_t) METHOD(T, datum_t, set) (datum_t value, TYPE(T, datum_t) list, int index) {return METHOD(deque, datum_t, set) (value, list, index);}

TYPE(T, datum_t) METHOD(T, datum_t, push) (datum_t value, TYPE(T, datum_t) list) {return METHOD(deque, datum_t, push_back) (value, list);}

TYPE(T, datum_t) METHOD(T, datum_t, pop) (datum_t *value, TYPE(T, datum_t) list) {return METHOD(deque, datum_t, pop_back) (value, list);}

TYPE(T, datum_t) METHOD(T, datum_t, delete) (TYPE(T, datum_t) list, void (*destructor) (datum_t)){return METHOD(deque, datum_t, delete) (list, destructor);}

void METHOD(T, datum_t, print) (TYPE(T, datum_t) list){METHOD(deque, datum_t, print) (list);}


#undef T

#endif