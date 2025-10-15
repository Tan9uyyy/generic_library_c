#ifndef _LIST_EXPORT_DEF_H__
#define _LIST_EXPORT_DEF_H__

#include "../deque.h"
#include "../../interface.h"

#ifndef datum_t
    #error "Undefined datum type !"
#endif

#define T list

typedef TYPE(deque, datum_t) TYPE(T, datum_t);

TYPE(T, datum_t)    METHOD(T, new) (void);
int                 METHOD(T, is_empty) (TYPE(T, datum_t) list);
int                 METHOD(T, length) (TYPE(T, datum_t) list);
datum_t             METHOD(T, first) (TYPE(T, datum_t) list);
TYPE(T, datum_t)    METHOD(T, push) (datum_t value, TYPE(T, datum_t) list);
TYPE(T, datum_t)    METHOD(T, pop) (datum_t *value, TYPE(T, datum_t) list);
TYPE(T, datum_t)    METHOD(T, delete) (TYPE(T, datum_t) list, void (*destructor) (datum_t));
void                METHOD(T, print) (TYPE(T, datum_t) list);

#undef T

#endif