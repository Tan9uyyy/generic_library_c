#ifndef _QUEUE_EXPORT_DEF_H__
#define _QUEUE_EXPORT_DEF_H__

#include "../deque.h"
#include "../../interface.h"

#ifndef datum_t
    #error "Undefined datum type !"
#endif

#define T queue

typedef TYPE(deque, datum_t) TYPE(T, datum_t);

TYPE(T, datum_t)    METHOD(T, datum_t, new) (void);
int                 METHOD(T, datum_t, is_empty) (TYPE(T, datum_t) queue);
int                 METHOD(T, datum_t, length) (TYPE(T, datum_t) queue);
datum_t             METHOD(T, datum_t, first) (TYPE(T, datum_t) queue);
TYPE(T, datum_t)    METHOD(T, datum_t, push) (datum_t value, TYPE(T, datum_t) queue);
TYPE(T, datum_t)    METHOD(T, datum_t, pop) (datum_t *value, TYPE(T, datum_t) queue);
TYPE(T, datum_t)    METHOD(T, datum_t, delete) (TYPE(T, datum_t) queue, void (*destructor) (datum_t));
void                METHOD(T, datum_t, print) (TYPE(T, datum_t) queue);


#undef T

#endif