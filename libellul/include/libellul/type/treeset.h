/*
 * 'treeset' abstract data type.
 *
 * Available type implementations:
 *
 * T_IMPL_TREAP (default)
 * ...
 *
 */

#ifndef T_TREESET_TAG
#error "Undefined T_TREESET_TAG"
#endif

#ifndef treeset_datum_t
#error "Undefined treeset datum type !"
#endif

#include <libellul/type/prologue.h>

#if !defined( T_TREESET_EXPORT_DEFS ) && !defined( T_TREESET_EXPORT_CODE )
#define T_TREESET_INTERFACE static inline
#else
#define T_TREESET_INTERFACE extern
#endif

#ifdef T
#undef T
#endif
#define T                      GEN_SYM( T_TREESET_TAG, t )
#define TREESET_METHOD( name )     GEN_SYM( T_TREESET_TAG, name )


#define T_TREESET_IMPL_TREAP
#define treap_datum_t treeset_datum_t
#define T_TREAP_TAG GEN_SYM(treap_datum_t, treap)
#define TREAP_METHOD( name )     GEN_SYM( T_TREAP_TAG, name )

#define TREAP_DESTRUCTOR(val) TREESET_DESTRUCTOR(val)
#define TREAP_COMPARATOR(val1, val2) TREESET_COMPARATOR(val1, val2)
#define TREAP_PRINTER(val) TREESET_PRINTER(val)
#define TREAP_PRIORITY_FUNC(val) TREESET_PRIORITY_FUNC(val)

#include <libellul/type/treap.h>

#define T_INTERFACE   T_TREESET_INTERFACE
#if defined( T_TREESET_EXPORT_DEFS )
#define T_EXPORT_DEFS
#endif

#undef T_TREESET_IMPL_TREAP
#undef T_TREESET_TAG
#undef T_TREESET_INTERFACE
#undef T_TREESET_EXPORT_DEFS
#undef T_TREESET_EXPORT_CODE
#undef T
#undef TREESET_METHOD
