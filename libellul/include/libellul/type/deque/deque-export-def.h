#ifndef _DEQUE_EXPORT_DEF_H__
#define _DEQUE_EXPORT_DEF_H__

#include "../../interface.h"

#ifndef datum_t
    #error "Undefined datum type !"
#endif

#define T deque

typedef struct TYPE(sentinel, datum_t) *TYPE(T, datum_t);

TYPE(T, datum_t)    METHOD(T, datum_t, new)(void);
int                 METHOD(T, datum_t, is_empty)(TYPE(T, datum_t) deque);
int                 METHOD(T, datum_t, length)(TYPE(T, datum_t) deque);
datum_t             METHOD(T, datum_t, first)(TYPE(T, datum_t) deque);
datum_t             METHOD(T, datum_t, last)(TYPE(T, datum_t) deque);
datum_t             METHOD(T, datum_t, get)(TYPE(T, datum_t) deque, int index);
TYPE(T, datum_t)    METHOD(T, datum_t, set)(datum_t value, TYPE(T, datum_t) deque, int index);
TYPE(T, datum_t)    METHOD(T, datum_t, push_front)(datum_t value, TYPE(T, datum_t) deque);
TYPE(T, datum_t)    METHOD(T, datum_t, push_back)(datum_t value, TYPE(T, datum_t) deque);
TYPE(T, datum_t)    METHOD(T, datum_t, pop_front)(datum_t *value, TYPE(T, datum_t) deque, void (*destructor)(datum_t));
TYPE(T, datum_t)    METHOD(T, datum_t, pop_back)(datum_t *value, TYPE(T, datum_t) deque, void (*destructor)(datum_t));
int                 METHOD(T, datum_t, contains)(TYPE(T, datum_t) deque, datum_t value, int (*comparator)(datum_t, datum_t));
TYPE(T, datum_t)    METHOD(T, datum_t, remove)(datum_t value, TYPE(T, datum_t) deque, int (*comparator)(datum_t, datum_t), void (*destructor)(datum_t));
TYPE(T, datum_t)    METHOD(T, datum_t, delete)(TYPE(T, datum_t) deque, void (*destructor)(datum_t));
void                METHOD(T, datum_t, print)(TYPE(T, datum_t) deque);

#undef T

#endif