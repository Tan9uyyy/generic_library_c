#ifndef _QUEUE_IMPLEMENTATION_H__
#define _QUEUE_IMPLEMENTATION_H__

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#ifndef queue_datum_t
    #error "Undefined datum type !"
#endif

#include "queue-export-def.h"

#ifdef T
#undef T
#endif
#define T queue

typedef TYPE(deque, queue_datum_t) TYPE(T, queue_datum_t);

TYPE(T, queue_datum_t) METHOD(T, queue_datum_t, new) (void) {return METHOD(deque, queue_datum_t, new) ();}

int METHOD(T, queue_datum_t, is_empty) (TYPE(T, queue_datum_t) queue) {return METHOD(deque, queue_datum_t, is_empty) (queue);}

int METHOD(T, queue_datum_t, length) (TYPE(T, queue_datum_t) queue) {return METHOD(deque, queue_datum_t, length) (queue);}

queue_datum_t METHOD(T, queue_datum_t, first) (TYPE(T, queue_datum_t) queue) {return METHOD(deque, queue_datum_t, first) (queue);}

TYPE(T, queue_datum_t) METHOD(T, queue_datum_t, push) (queue_datum_t value, TYPE(T, queue_datum_t) queue) {
    return METHOD(deque, queue_datum_t, push_back) (value, queue);
}

TYPE(T, queue_datum_t) METHOD(T, queue_datum_t, pop) (queue_datum_t *value, TYPE(T, queue_datum_t) queue, void (*destructor)(queue_datum_t)) {
    return METHOD(deque, queue_datum_t, pop_front) (value, queue, destructor);
}

TYPE(T, queue_datum_t) METHOD(T, queue_datum_t, delete) (TYPE(T, queue_datum_t) queue, void (*destructor) (queue_datum_t)){
    return METHOD(deque, queue_datum_t, delete) (queue, destructor);
}

void METHOD(T, queue_datum_t, print) (TYPE(T, queue_datum_t) queue, void (*printer)(queue_datum_t)){
    METHOD(deque, queue_datum_t, print) (queue, printer);
}


#undef T

#endif