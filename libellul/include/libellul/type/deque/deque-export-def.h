#ifndef _DEQUE_EXPORT_DEF_H__
#define _DEQUE_EXPORT_DEF_H__

#ifndef datum_t
    #error "Undefined datum type !"
#endif

#define T deque
#include "interface.h"

typedef struct TYPE(sentinel, datum_t) *TYPE(T, datum_t);

typedef struct TYPE(link, datum_t) TYPE(link, datum_t);

TYPE(T, datum_t)    METHOD(new) (void);
int                 METHOD(is_empty) (TYPE(T, datum_t) deque);
datum_t             METHOD(first) (TYPE(T, datum_t) deque);
TYPE(T, datum_t)    METHOD(next) (TYPE(T, datum_t) deque);
TYPE(T, datum_t)    METHOD(push_front) (datum_t value, TYPE(T, datum_t) deque);
TYPE(T, datum_t)    METHOD(push_back) (datum_t value, TYPE(T, datum_t) deque);
TYPE(T, datum_t)    METHOD(pop_front) (datum_t *value, TYPE(T, datum_t) deque);
TYPE(T, datum_t)    METHOD(pop_back) (datum_t *value, TYPE(T, datum_t) deque);
TYPE(T, datum_t)    METHOD(delete) (TYPE(T, datum_t) list, void (*destructor)(datum_t));

#undef T
#undef datum_t
// #undef TYPENAME
// #undef TYPE
// #undef METHOD


#endif