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

TYPE(T, datum_t) METHOD(T, new) (void) {return NULL;}

int METHOD(T, is_empty) (TYPE(T, datum_t) queue) {return METHOD(deque, is_empty) (queue);}

datum_t METHOD(T, first) (TYPE(T, datum_t) queue) {return METHOD(deque, first) (queue);}

TYPE(T, datum_t) METHOD(T, push) (datum_t value, TYPE(T, datum_t) queue) {return METHOD(deque, push_front) (value, queue);}

TYPE(T, datum_t) METHOD(T, pop) (datum_t *value, TYPE(T, datum_t) queue) {return METHOD(deque, pop_back) (value, queue);}

void METHOD(T, print) (TYPE(T, datum_t) queue) {return METHOD(deque, print) (queue);}


#undef T
#undef datum_t

#endif