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

TYPE(T, datum_t) METHOD(T, new) (void) {return METHOD(deque, new) ();}

int METHOD(T, is_empty) (TYPE(T, datum_t) queue) {return METHOD(deque, is_empty) (queue);}

datum_t METHOD(T, first) (TYPE(T, datum_t) queue) {return METHOD(deque, first) (queue);}

TYPE(T, datum_t) METHOD(T, push) (datum_t value, TYPE(T, datum_t) queue) {return METHOD(deque, push_back) (value, queue);}

TYPE(T, datum_t) METHOD(T, pop) (datum_t *value, TYPE(T, datum_t) queue) {return METHOD(deque, pop_front) (value, queue);}

TYPE(T, datum_t) METHOD(T, delete) (TYPE(T, datum_t) queue, void (*destructor) (datum_t)){return METHOD(deque, delete) (queue, destructor);}

void METHOD(T, print) (TYPE(T, datum_t) queue){METHOD(deque, print) (queue);}


#undef T

#endif