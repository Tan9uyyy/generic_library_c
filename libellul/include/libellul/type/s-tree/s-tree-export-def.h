#ifndef _S_TREE_EXPORT_DEF_H__
#define _S_TREE_EXPORT_DEF_H__

#include "../../interface.h"

#ifndef s_tree_datum_t
    #error "Undefined datum type !"
#endif

#define b_tree_datum_t s_tree_datum_t
#include "../b-tree.h"
#undef b_tree_datum_t

#ifdef T
#undef T
#endif
#define T s_tree

typedef TYPE(b_tree, s_tree_datum_t) TYPE(T, s_tree_datum_t);

TYPE(T, s_tree_datum_t) METHOD(T, s_tree_datum_t, new) (void);
int                     METHOD(T, s_tree_datum_t, is_empty) (TYPE(T, s_tree_datum_t) s_tree);












#endif