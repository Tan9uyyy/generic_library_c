#ifndef _QUEUE_EXPORT_DEF_H__
#define _QUEUE_EXPORT_DEF_H__

#include "../../interface.h"

#ifndef queue_datum_t
    #error "Undefined datum type !"
#endif

#define deque_datum_t queue_datum_t
#include "../deque.h"
#undef deque_datum_t

#define T queue

typedef TYPE(deque, queue_datum_t) TYPE(T, queue_datum_t);

TYPE(T, queue_datum_t)  METHOD(T, queue_datum_t, new) (void);
int                     METHOD(T, queue_datum_t, is_empty) (TYPE(T, queue_datum_t) queue);
int                     METHOD(T, queue_datum_t, length) (TYPE(T, queue_datum_t) queue);
queue_datum_t           METHOD(T, queue_datum_t, first) (TYPE(T, queue_datum_t) queue);
TYPE(T, queue_datum_t)  METHOD(T, queue_datum_t, push) (queue_datum_t value, TYPE(T, queue_datum_t) queue);
TYPE(T, queue_datum_t)  METHOD(T, queue_datum_t, pop) (queue_datum_t *value, TYPE(T, queue_datum_t) queue, void (*destructor) (queue_datum_t));
TYPE(T, queue_datum_t)  METHOD(T, queue_datum_t, delete) (TYPE(T, queue_datum_t) queue, void (*destructor) (queue_datum_t));
void                    METHOD(T, queue_datum_t, print) (TYPE(T, queue_datum_t) queue, void (*printer) (queue_datum_t));


#undef T

#endif