#include <../include/libellul/type/b-tree.h>

#ifdef b_tree_datum_t
    #include <../include/libellul/type/b-tree/b-tree-implementation.h>
    #undef b_tree_datum_t
#endif

#define b_tree_datum_t int
#include <../include/libellul/type/b-tree/b-tree-implementation.h>