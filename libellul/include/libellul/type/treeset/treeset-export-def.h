#ifndef _TREESET_EXPORT_DEF_H__
#define _TREESET_EXPORT_DEF_H__

#include "../treap.h"
#include "../../interface.h"

#ifndef datum_t
    #error "Undefined datum type !"
#endif

#define T treeset

typedef TYPE(treap, datum_t) TYPE(T, datum_t);

TYPE(T, datum_t)    METHOD(T, new) (void);
int                 METHOD(T, is_empty) (TYPE(T, datum_t) treeset);
TYPE(T, datum_t)    METHOD(T, add) (TYPE(T, datum_t) treeset, datum_t value, int (*comparator)(datum_t, datum_t), int (*priority_func)(datum_t));
datum_t             METHOD(T, upper_bound) (TYPE(T, datum_t) treeset);
datum_t             METHOD(T, lower_bound) (TYPE(T, datum_t) treeset);
TYPE(T, datum_t)    METHOD(T, remove_max) (TYPE(T, datum_t) treeset);
TYPE(T, datum_t)    METHOD(T, remove_min) (TYPE(T, datum_t) treeset);
int                 METHOD(T, contains) (TYPE(T, datum_t) treeset, datum_t value, int (*comparator)(datum_t, datum_t));
TYPE(T, datum_t)    METHOD(T, reunion) (TYPE(T, datum_t) treeset_1, TYPE(T, datum_t) treeset_2, int (*comparator)(datum_t, datum_t), int (*priority_func)(datum_t));
TYPE(T, datum_t)    METHOD(T, inter) (TYPE(T, datum_t) treeset_1, TYPE(T, datum_t) treeset_2, int (*comparator)(datum_t, datum_t), int (*priority_func)(datum_t));
TYPE(T, datum_t)    METHOD(T, delete) (TYPE(T, datum_t) treeset, void (*destructor)(datum_t));
void                METHOD(T, print) (TYPE(T, datum_t) treeset, void (*printer)(datum_t));


#undef T

#endif