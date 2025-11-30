#ifndef _DEQUE_EXPORT_DEF_H__
#define _DEQUE_EXPORT_DEF_H__

#include "../../interface.h"

#ifndef deque_datum_t
    #error "Undefined datum type !"
#endif

#define T deque

typedef struct TYPE(sentinel, deque_datum_t) *TYPE(T, deque_datum_t);

TYPE(T, deque_datum_t)  METHOD(T, deque_datum_t, new)(void);
int                     METHOD(T, deque_datum_t, is_empty)(TYPE(T, deque_datum_t) deque);
int                     METHOD(T, deque_datum_t, length)(TYPE(T, deque_datum_t) deque);
deque_datum_t           METHOD(T, deque_datum_t, first)(TYPE(T, deque_datum_t) deque);
deque_datum_t           METHOD(T, deque_datum_t, last)(TYPE(T, deque_datum_t) deque);
deque_datum_t           METHOD(T, deque_datum_t, get)(TYPE(T, deque_datum_t) deque, int index);
TYPE(T, deque_datum_t)  METHOD(T, deque_datum_t, set)(deque_datum_t value, TYPE(T, deque_datum_t) deque, int index);
TYPE(T, deque_datum_t)  METHOD(T, deque_datum_t, push_front)(deque_datum_t value, TYPE(T, deque_datum_t) deque);
TYPE(T, deque_datum_t)  METHOD(T, deque_datum_t, push_back)(deque_datum_t value, TYPE(T, deque_datum_t) deque);
TYPE(T, deque_datum_t)  METHOD(T, deque_datum_t, pop_front)(deque_datum_t *value, TYPE(T, deque_datum_t) deque);
TYPE(T, deque_datum_t)  METHOD(T, deque_datum_t, pop_back)(deque_datum_t *value, TYPE(T, deque_datum_t) deque);
TYPE(T, deque_datum_t)  METHOD(T, deque_datum_t, rotate)(int nb_rot, TYPE(T, deque_datum_t) deque);
int                     METHOD(T, deque_datum_t, contains)(TYPE(T, deque_datum_t) deque, deque_datum_t value, int (*comparator)(deque_datum_t, deque_datum_t));
TYPE(T, deque_datum_t)  METHOD(T, deque_datum_t, remove)(deque_datum_t value, TYPE(T, deque_datum_t) deque, int (*comparator)(deque_datum_t, deque_datum_t));
TYPE(T, deque_datum_t)  METHOD(T, deque_datum_t, delete)(TYPE(T, deque_datum_t) deque, void (*destructor)(deque_datum_t));
void                    METHOD(T, deque_datum_t, print)(TYPE(T, deque_datum_t) deque, void (*printer) (deque_datum_t));

#undef T

#endif