#ifndef _TREAP_EXPORT_DEF_H__
#define _TREAP_EXPORT_DEF_H__

#include "../../interface.h"

#ifndef treap_datum_t
    #error "Undefined datum type !"
#endif

#define T treap

typedef struct TYPE(node, treap_datum_t) *TYPE(T, treap_datum_t);
typedef struct TYPE(node, treap_datum_t) *TYPE(treap, treap_datum_t);

TYPE(T, treap_datum_t)    METHOD(T, treap_datum_t, new) (void);
int                 METHOD(T, treap_datum_t, is_empty) (TYPE(T, treap_datum_t) treap);
TYPE(T, treap_datum_t)    METHOD(T, treap_datum_t, push) (TYPE(T, treap_datum_t) treap, treap_datum_t value, int (*comparator)(treap_datum_t, treap_datum_t), int (*priority_func)(treap_datum_t));
treap_datum_t             METHOD(T, treap_datum_t, min) (TYPE(T, treap_datum_t) treap);
treap_datum_t             METHOD(T, treap_datum_t, max) (TYPE(T, treap_datum_t) treap);
TYPE(T, treap_datum_t)    METHOD(T, treap_datum_t, pop_small) (TYPE(T, treap_datum_t) treap, treap_datum_t *value);
TYPE(T, treap_datum_t)    METHOD(T, treap_datum_t, pop_big) (TYPE(T, treap_datum_t) treap, treap_datum_t *value);
int                 METHOD(T, treap_datum_t, contains) (TYPE(T, treap_datum_t) treap, treap_datum_t value, int (*comparator)(treap_datum_t, treap_datum_t));
TYPE(T, treap_datum_t)    METHOD(T, treap_datum_t, delete) (TYPE(T, treap_datum_t) treap, void (*destructor)(treap_datum_t));
void                METHOD(T, treap_datum_t, print) (TYPE(T, treap_datum_t) treap, void (*printer)(treap_datum_t));


#undef T

#endif