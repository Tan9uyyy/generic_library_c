#ifndef _B_TREE_EXPORT_DEF_H__
#define _B_TREE_EXPORT_DEF_H__

#include "../../interface.h"

#ifndef b_tree_datum_t
    #error "Undefined datum type !"
#endif

#ifdef T
#undef T
#endif
#define T b_tree

typedef struct TYPE(b_tree_node, b_tree_datum_t) *TYPE(T, b_tree_datum_t);

TYPE(T, b_tree_datum_t)     METHOD(T, b_tree_datum_t, new) (void);
int                         METHOD(T, b_tree_datum_t, is_empty) (TYPE(T, b_tree_datum_t) b_tree);
TYPE(T, b_tree_datum_t)     METHOD(T, b_tree_datum_t, push) (TYPE(T, b_tree_datum_t) b_tree, b_tree_datum_t value);
TYPE(T, b_tree_datum_t)     METHOD(T, b_tree_datum_t, pop) (TYPE(T, b_tree_datum_t) b_tree, b_tree_datum_t value);
TYPE(T, b_tree_datum_t)     METHOD(T, b_tree_datum_t, pop_small) (TYPE(T, b_tree_datum_t) b_tree, b_tree_datum_t *value);
TYPE(T, b_tree_datum_t)     METHOD(T, b_tree_datum_t, pop_big) (TYPE(T, b_tree_datum_t) b_tree, b_tree_datum_t *value);
int                         METHOD(T, b_tree_datum_t, contains) (TYPE(T, b_tree_datum_t) b_tree, b_tree_datum_t value);
TYPE(T, b_tree_datum_t)     METHOD(T, b_tree_datum_t, delete) (TYPE(T, b_tree_datum_t) b_tree);
void                        METHOD(T, b_tree_datum_t, print) (TYPE(T, b_tree_datum_t) b_tree);


#undef T

#endif