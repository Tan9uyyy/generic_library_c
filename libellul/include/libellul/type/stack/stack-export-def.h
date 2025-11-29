#ifndef _STACK_EXPORT_DEF_H__
#define _STACK_EXPORT_DEF_H__

#include "../../interface.h"

#ifndef stack_datum_t
    #error "Undefined datum type !"
#endif

#define deque_datum_t stack_datum_t
#include "../deque.h"
#undef deque_datum_t

#define T stack

typedef TYPE(deque, stack_datum_t) TYPE(T, stack_datum_t);

TYPE(T, stack_datum_t)    METHOD(T, stack_datum_t, new) (void);
int                 METHOD(T, stack_datum_t, is_empty) (TYPE(T, stack_datum_t) stack);
int                 METHOD(T, stack_datum_t, length) (TYPE(T, stack_datum_t) queue);
stack_datum_t             METHOD(T, stack_datum_t, first) (TYPE(T, stack_datum_t) stack);
TYPE(T, stack_datum_t)    METHOD(T, stack_datum_t, push) (stack_datum_t value, TYPE(T, stack_datum_t) stack);
TYPE(T, stack_datum_t)    METHOD(T, stack_datum_t, pop) (stack_datum_t *value, TYPE(T, stack_datum_t) stack, void (*destructor) (stack_datum_t));
TYPE(T, stack_datum_t)    METHOD(T, stack_datum_t, delete) (TYPE(T, stack_datum_t) stack, void (*destructor) (stack_datum_t));
void                METHOD(T, stack_datum_t, print) (TYPE(T, stack_datum_t) stack, void (*printer) (stack_datum_t));


#undef T

#endif