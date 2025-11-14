#ifndef _TREE_EXPORT_DEF_H__
#define _TREE_EXPORT_DEF_H__

#ifndef datum_t
    #error "Undefined datum type !"
#endif

#define T binary_tree
#include "../../interface.h"

typedef struct TYPE(node, datum_t) *TYPE(T, datum_t);
typedef struct TYPE(node, datum_t) *TYPE(tree, datum_t);

TYPE(T, datum_t)    METHOD(T, datum_t, new) (void);
int                 METHOD(T, datum_t, is_empty) (TYPE(T, datum_t) tree);
TYPE(T, datum_t)    METHOD(T, datum_t, push) (TYPE(T, datum_t) tree, datum_t value, int (*comparator)(datum_t, datum_t));
TYPE(T, datum_t)    METHOD(T, datum_t, pop_small) (TYPE(T, datum_t) tree, datum_t *value);
TYPE(T, datum_t)    METHOD(T, datum_t, pop_big) (TYPE(T, datum_t) tree, datum_t *value);
int                 METHOD(T, datum_t, contains) (TYPE(T, datum_t) tree, datum_t value, int (*comparator)(datum_t, datum_t));
TYPE(T, datum_t)    METHOD(T, datum_t, delete) (TYPE(T, datum_t) tree, void (*destructor)(datum_t));
void                METHOD(T, datum_t, print) (TYPE(T, datum_t) tree, void (*printer)(datum_t));


#undef T

#endif