#ifndef _TREAP_EXPORT_DEF_H__
#define _TREAP_EXPORT_DEF_H__

#ifndef datum_t
    #error "Undefined datum type !"
#endif

#define T treap
#include "../../interface.h"

typedef struct TYPE(node, datum_t) *TYPE(T, datum_t);

TYPE(T, datum_t)    METHOD(T, new) (void);
int                 METHOD(T, is_empty) (TYPE(T, datum_t) treap);
TYPE(T, datum_t)    METHOD(T, push) (TYPE(T, datum_t) treap, datum_t value, int (*comparator)(datum_t, datum_t), int (*priority_func)(datum_t));
TYPE(T, datum_t)    METHOD(T, pop_small) (TYPE(T, datum_t) treap, datum_t *value);
TYPE(T, datum_t)    METHOD(T, pop_big) (TYPE(T, datum_t) treap, datum_t *value);
int                 METHOD(T, contains) (TYPE(T, datum_t) treap, datum_t value, int (*comparator)(datum_t, datum_t));
TYPE(T, datum_t)    METHOD(T, delete) (TYPE(T, datum_t) treap, void (*destructor)(datum_t));
void                METHOD(T, print) (TYPE(T, datum_t) treap, void (*printer)(datum_t));


#undef T

#endif