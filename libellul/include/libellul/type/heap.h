/*
 * 'heap' abstract data type.
 *
 * Available type implementations:
 *
 * T_IMPL_DYN_ARRAY (default)
 * ...
 *
 */

#ifndef T_HEAP_TAG
#error "Undefined T_HEAP_TAG"
#endif

#ifndef heap_datum_t
#error "Undefined heap datum type !"
#endif

#include <libellul/type/prologue.h>

#if !defined( T_HEAP_EXPORT_DEFS ) && !defined( T_HEAP_EXPORT_CODE )
#define T_HEAP_INTERFACE static inline
#else
#define T_HEAP_INTERFACE extern
#endif

#ifdef T
#undef T
#endif
#define T                      GEN_SYM( T_HEAP_TAG, t )
#define HEAP_METHOD( name )     GEN_SYM( T_HEAP_TAG, name )

typedef heap_datum_t *T;

#include <libellul/type/array.h>

#define T_INTERFACE   T_HEAP_INTERFACE
#if defined( T_HEAP_EXPORT_DEFS )
#define T_EXPORT_DEFS
#endif

#include <libellul/type/heap/interface.h>
#include <libellul/type/heap/heap-implementation.h>

#undef T_HEAP_IMPL_DEQUE
#undef T_HEAP_TAG
#undef T_HEAP_INTERFACE
#undef T_HEAP_EXPORT_DEFS
#undef T_HEAP_EXPORT_CODE
#undef T
#undef HEAP_METHOD
