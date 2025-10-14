#ifndef _DEQUE_EXPORT_DEF_H__
#define _DEQUE_EXPORT_DEF_H__

#ifndef datum_t
    #error "Undefined datum type !"
#endif

#define T deque
#include "../../interface.h"

typedef struct TYPE(link, datum_t) *TYPE(T, datum_t);

TYPE(T, datum_t)    METHOD(T, new) (void);
int                 METHOD(T, is_empty) (TYPE(T, datum_t) deque);
datum_t             METHOD(T, first) (TYPE(T, datum_t) deque);
datum_t             METHOD(T, last) (TYPE(T, datum_t) deque);
TYPE(T, datum_t)    METHOD(T, push_front) (datum_t value, TYPE(T, datum_t) deque);
TYPE(T, datum_t)    METHOD(T, push_back) (datum_t value, TYPE(T, datum_t) deque);
TYPE(T, datum_t)    METHOD(T, pop_front) (datum_t *value, TYPE(T, datum_t) deque);
TYPE(T, datum_t)    METHOD(T, pop_back) (datum_t *value, TYPE(T, datum_t) deque);
TYPE(T, datum_t)    METHOD(T, delete) (TYPE(T, datum_t) list, void (*destructor)(datum_t));
void                METHOD(T, print) (TYPE(T, datum_t) deque);

#undef T
// #undef datum_t
// #undef TYPENAME
// #undef TYPE
// #undef METHOD


#endif