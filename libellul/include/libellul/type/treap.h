/*
 * 'treap' abstract data type.
 *
 * Available type implementations:
 *
 * T_IMPL_B_TREE (default)
 * ...
 *
 */

#ifndef T_TREAP_TAG
#error "Undefined T_TREAP_TAG"
#endif

#ifndef treap_datum_t
#error "Undefined treap datum type !"
#endif

#include <libellul/type/prologue.h>

#if defined(T_TREESET_IMPL_TREAP)
#define T_TREAP_INTERFACE T_TREESET_INTERFACE
#else
#if !defined( T_TREAP_EXPORT_DEFS ) && !defined( T_TREAP_EXPORT_CODE )
#define T_TREAP_INTERFACE static inline
#else
#define T_TREAP_INTERFACE extern
#endif
#endif

#ifndef T
#define T                      GEN_SYM( T_TREAP_TAG, t )
#define T_FLAG
#endif
#define TREAP_METHOD( name )     GEN_SYM( T_TREAP_TAG, name )

#define T_TREAP_IMPL_B_TREE

typedef struct treap_couple {
    treap_datum_t value;
    int priority;
} treap_couple;

#define b_tree_datum_t treap_couple
#define T_B_TREE_TAG GEN_SYM(b_tree_datum_t, b_tree)
#define B_TREE_METHOD( name )     GEN_SYM( T_B_TREE_TAG, name )

#define DESTRUCTOR(val) NULL
#define COMPARATOR(val1, val2) (val1.value - val2.value)
#define PRINTER(val) (printf("(%d, %d)", val.priority, val.value))

#include <libellul/structure/b-tree.h>

#if defined(T_TREESET_IMPL_TREAP)
#include <libellul/type/treeset/interface.h>
#include <libellul/type/treeset/treeset-implementation.h>
#endif

#define T_INTERFACE   T_TREESET_INTERFACE
#if defined( T_TREAP_EXPORT_DEFS )
#define T_EXPORT_DEFS
#endif

#undef T_TREAP_IMPL_B_TREE
#undef T_TREAP_TAG
#undef T_TREAP_INTERFACE
#undef T_TREAP_EXPORT_DEFS
#undef T_TREAP_EXPORT_CODE
#ifdef T_FLAG
#undef T
#undef T_FLAG
#endif
#undef TREAP_METHOD
