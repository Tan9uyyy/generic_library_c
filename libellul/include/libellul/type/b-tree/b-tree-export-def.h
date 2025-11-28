#ifndef _TREE_EXPORT_DEF_H__
#define _TREE_EXPORT_DEF_H__

#ifndef b_tree_datum_t
    #error "Undefined datum type !"
#endif

#define T binary_tree
#include "../../interface.h"

typedef struct TYPE(node, b_tree_datum_t) *TYPE(T, b_tree_datum_t);
typedef struct TYPE(node, b_tree_datum_t) *TYPE(tree, b_tree_datum_t);

TYPE(T, b_tree_datum_t)    METHOD(T, b_tree_datum_t, new) (void);
int                 METHOD(T, b_tree_datum_t, is_empty) (TYPE(T, b_tree_datum_t) tree);
TYPE(T, b_tree_datum_t)    METHOD(T, b_tree_datum_t, push) (TYPE(T, b_tree_datum_t) tree, b_tree_datum_t value, int (*comparator)(b_tree_datum_t, b_tree_datum_t));
TYPE(T, b_tree_datum_t)    METHOD(T, b_tree_datum_t, pop_small) (TYPE(T, b_tree_datum_t) tree, b_tree_datum_t *value);
TYPE(T, b_tree_datum_t)    METHOD(T, b_tree_datum_t, pop_big) (TYPE(T, b_tree_datum_t) tree, b_tree_datum_t *value);
int                 METHOD(T, b_tree_datum_t, contains) (TYPE(T, b_tree_datum_t) tree, b_tree_datum_t value, int (*comparator)(b_tree_datum_t, b_tree_datum_t));
TYPE(T, b_tree_datum_t)    METHOD(T, b_tree_datum_t, delete) (TYPE(T, b_tree_datum_t) tree, void (*destructor)(b_tree_datum_t));
void                METHOD(T, b_tree_datum_t, print) (TYPE(T, b_tree_datum_t) tree, void (*printer)(b_tree_datum_t));


#undef T

#endif