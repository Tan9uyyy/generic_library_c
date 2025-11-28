#ifndef _TREESET_EXPORT_DEF_H__
#define _TREESET_EXPORT_DEF_H__

#include "../../interface.h"

#ifndef treeset_datum_t
    #error "Undefined datum type !"
#endif

#define treap_datum_t treeset_datum_t
#include "../treap.h"
#undef treap_datum_t

#define T treeset

typedef TYPE(treap, treeset_datum_t) TYPE(T, treeset_datum_t);

TYPE(T, treeset_datum_t)    METHOD(T, treeset_datum_t, new) (void);
int                 METHOD(T, treeset_datum_t, is_empty) (TYPE(T, treeset_datum_t) treeset);
TYPE(T, treeset_datum_t)    METHOD(T, treeset_datum_t, add) (TYPE(T, treeset_datum_t) treeset, treeset_datum_t value, int (*comparator)(treeset_datum_t, treeset_datum_t), int (*priority_func)(treeset_datum_t));
treeset_datum_t             METHOD(T, treeset_datum_t, upper_bound) (TYPE(T, treeset_datum_t) treeset);
treeset_datum_t             METHOD(T, treeset_datum_t, lower_bound) (TYPE(T, treeset_datum_t) treeset);
TYPE(T, treeset_datum_t)    METHOD(T, treeset_datum_t, remove_max) (TYPE(T, treeset_datum_t) treeset);
TYPE(T, treeset_datum_t)    METHOD(T, treeset_datum_t, remove_min) (TYPE(T, treeset_datum_t) treeset);
int                 METHOD(T, treeset_datum_t, contains) (TYPE(T, treeset_datum_t) treeset, treeset_datum_t value, int (*comparator)(treeset_datum_t, treeset_datum_t));
TYPE(T, treeset_datum_t)    METHOD(T, treeset_datum_t, reunion) (TYPE(T, treeset_datum_t) *treeset_1, TYPE(T, treeset_datum_t) *treeset_2, int (*comparator)(treeset_datum_t, treeset_datum_t), int (*priority_func)(treeset_datum_t));
TYPE(T, treeset_datum_t)    METHOD(T, treeset_datum_t, inter) (TYPE(T, treeset_datum_t) *treeset_1, TYPE(T, treeset_datum_t) *treeset_2, int (*comparator)(treeset_datum_t, treeset_datum_t), int (*priority_func)(treeset_datum_t));
TYPE(T, treeset_datum_t)    METHOD(T, treeset_datum_t, delete) (TYPE(T, treeset_datum_t) treeset, void (*destructor)(treeset_datum_t));
void                METHOD(T, treeset_datum_t, print) (TYPE(T, treeset_datum_t) treeset, void (*printer)(treeset_datum_t));


#undef T

#endif