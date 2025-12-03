/**
 * Binary Tree
 * 
 * Variants :
 * 
 */

#ifndef b_tree_datum_t
    #error "Undefined datum type !"
#endif

#ifndef T_B_TREE_TAG
    #error "Undefined tag !"
#endif

typedef struct T{
    struct T *ls;
    struct T *rs;
    b_tree_datum_t value;
} *T;

#ifdef T_B_TREE
    #define B_TREE_METHOD( name ) GEN_SYM( T_B_TREE_TAG, name )
#elif defined( T_TREAP_IMPL_B_TREE )
    #include <libellul/type/treap/interface.h>
#elif defined( T_S_TREE_IMPL_B_TREE )
    #include <libellul/type/s-tree/interface.h>
#elif defined( T_TREESET_IMPL_B_TREE)
    #include <libellul/type/treeset/interface.h>
#else
    #error "B-tree must implemente an abstract data type!"
#endif

#include <libellul/structure/b-tree/b-tree-export-def.h>
#include <libellul/structure/b-tree/b-tree-implementation.h>

#ifdef T_B_TREE
#elif defined( T_TREAP_IMPL_B_TREE )
    #include <libellul/type/treap/treap-implementation.h>
#elif defined( T_S_TREE_IMPL_B_TREE )
    #include <libellul/type/s-tree/s-tree-implementation.h>
#elif defined( T_TREESET_IMPL_B_TREE)
    #include <libellul/type/treeset/treeset-implementation.h>
#else
    #error "B-tree must implemente an abstract data type!"
#endif

#undef T_IMPL_B_TREE