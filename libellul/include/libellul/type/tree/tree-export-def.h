#ifndef _TREE_EXPORT_DEF_H__
#define _TREE_EXPORT_DEF_H__

#ifndef datum_t
    #error "Undefined datum type !"
#endif

#define T tree
#include "../../interface.h"

typedef struct TYPE(node, datum_t) *TYPE(T, datum_t);

TYPE(T, datum_t)    METHOD(T, new) (void);
int                 METHOD(T, is_empty) (TYPE(T, datum_t) tree);
datum_t             METHOD(T, root) (TYPE(T, datum_t) tree);
TYPE(T, datum_t)    METHOD(T, left) (TYPE(T, datum_t) tree);
TYPE(T, datum_t)    METHOD(T, right) (TYPE(T, datum_t) tree);
TYPE(T, datum_t)    METHOD(T, push) (TYPE(T, datum_t) tree, datum_t value, void (*comparator)(datum_t, datum_t));
TYPE(T, datum_t)    METHOD(T, pop_small) (TYPE(T, datum_t) tree, datum_t *value);
TYPE(T, datum_t)    METHOD(T, pop_big) (TYPE(T, datum_t) tree, datum_t *value);
int                 METHOD(T, contains) (TYPE(T, datum_t) tree, datum_t value, int (*comparator)(datum_t, datum_t));
TYPE(T, datum_t)    METHOD(T, delete) (TYPE(T, datum_t) tree, void (*destructor)(datum_t));
void                METHOD(T, print) (TYPE(T, datum_t) tree, void (*printer)(datum_t));


#endif