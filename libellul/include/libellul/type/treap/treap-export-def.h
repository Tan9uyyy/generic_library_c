#ifndef _TREAP_EXPORT_DEF_H__
#define _TREAP_EXPORT_DEF_H__

#ifndef datum_t
    #error "Undefined datum type !"
#endif

#define T treap
#include "../../interface.h"

typedef struct TYPE(node, datum_t) *TYPE(T, datum_t);
typedef struct TYPE(node, datum_t) *TYPE(treap, datum_t);

TYPE(T, datum_t)    METHOD(T, datum_t, new) (void);
int                 METHOD(T, datum_t, is_empty) (TYPE(T, datum_t) treap);
TYPE(T, datum_t)    METHOD(T, datum_t, push) (TYPE(T, datum_t) treap, datum_t value, int (*comparator)(datum_t, datum_t), int (*priority_func)(datum_t));
datum_t             METHOD(T, datum_t, min) (TYPE(T, datum_t) treap);
datum_t             METHOD(T, datum_t, max) (TYPE(T, datum_t) treap);
TYPE(T, datum_t)    METHOD(T, datum_t, pop_small) (TYPE(T, datum_t) treap, datum_t *value);
TYPE(T, datum_t)    METHOD(T, datum_t, pop_big) (TYPE(T, datum_t) treap, datum_t *value);
int                 METHOD(T, datum_t, contains) (TYPE(T, datum_t) treap, datum_t value, int (*comparator)(datum_t, datum_t));
TYPE(T, datum_t)    METHOD(T, datum_t, delete) (TYPE(T, datum_t) treap, void (*destructor)(datum_t));
void                METHOD(T, datum_t, print) (TYPE(T, datum_t) treap, void (*printer)(datum_t));


#undef T

#endif