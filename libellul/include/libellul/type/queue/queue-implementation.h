#ifndef _QUEUE_IMPLEMENTATION_H__
#define _QUEUE_IMPLEMENTATION_H__


#ifndef datum_t
    #error "Undefined datum type !"
#endif

#define T queue

#include "../deque.h"
#include "../../interface.h"

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

typedef TYPE(deque, datum_t) TYPE(T, datum_t);

TYPE(T, datum_t) METHOD(T, datum_t, new) (void) {return METHOD(deque, datum_t, new) ();}

int METHOD(T, datum_t, is_empty) (TYPE(T, datum_t) queue) {return METHOD(deque, datum_t, is_empty) (queue);}

int METHOD(T, datum_t, length) (TYPE(T, datum_t) queue) {return METHOD(deque, datum_t, length) (queue);}

datum_t METHOD(T, datum_t, first) (TYPE(T, datum_t) queue) {return METHOD(deque, datum_t, first) (queue);}

TYPE(T, datum_t) METHOD(T, datum_t, push) (datum_t value, TYPE(T, datum_t) queue) {return METHOD(deque, datum_t, push_back) (value, queue);}

TYPE(T, datum_t) METHOD(T, datum_t, pop) (datum_t *value, TYPE(T, datum_t) queue) {return METHOD(deque, datum_t, pop_front) (value, queue);}

TYPE(T, datum_t) METHOD(T, datum_t, delete) (TYPE(T, datum_t) queue, void (*destructor) (datum_t)){return METHOD(deque, datum_t, delete) (queue, destructor);}

void METHOD(T, datum_t, print) (TYPE(T, datum_t) queue){METHOD(deque, datum_t, print) (queue);}


#undef T

#endif