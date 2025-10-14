#ifndef _QUEUE_EXPORT_DEF_H__
#define _QUEUE_EXPORT_DEF_H__

#include "../deque.h"
#include "../../interface.h"

#ifndef datum_t
    #error "Undefined datum type !"
#endif

#define T queue

typedef TYPE(deque, datum_t) TYPE(T, datum_t);

TYPE(T, datum_t)    METHOD(T, new) (void);
int                 METHOD(T, is_empty) (TYPE(T, datum_t) queue);
datum_t             METHOD(T, first) (TYPE(T, datum_t) queue);
TYPE(T, datum_t)    METHOD(T, push) (datum_t value, TYPE(T, datum_t) queue);
TYPE(T, datum_t)    METHOD(T, pop) (datum_t *value, TYPE(T, datum_t) queue);
TYPE(T, datum_t)    METHOD(T, delete) (TYPE(T, datum_t) queue, void (*destructor) (datum_t));
void                METHOD(T, print) (TYPE(T, datum_t) queue);


#undef T
#undef datum_t

#endif