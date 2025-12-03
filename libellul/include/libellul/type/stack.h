/*
 * 'stack' abstract data type.
 *
 * Available type implementations:
 *
 * T_IMPL_DEQUE (default)
 * T_IMPL_DYN_ARRAY
 * ...
 *
 */

#ifndef T_STACK_TAG
#error "Undefined T_STACK_TAG"
#endif

#ifndef stack_datum_t
#error "Undefined stack datum type !"
#endif

#include <libellul/type/prologue.h>

#if !defined( T_STACK_EXPORT_DEFS ) && !defined( T_STACK_EXPORT_CODE )
#define T_STACK_INTERFACE static inline
#else
#define T_STACK_INTERFACE extern
#endif

#ifdef T
#undef T
#endif
#define T                      GEN_SYM( T_STACK_TAG, t )
#define STACK_METHOD( name )     GEN_SYM( T_STACK_TAG, name )


#if defined( T_IMPL_DYN_ARRAY )
#include <libellul/type/array.h>
#else /* Default data structure for a STACK is a deque */
#define T_STACK_IMPL_DEQUE
#define deque_datum_t stack_datum_t
#define T_DEQUE_TAG GEN_SYM(deque_datum_t, deque)
#define DEQUE_METHOD( name )     GEN_SYM( T_DEQUE_TAG, name )
#include <libellul/structure/deque.h>
#endif

#define T_INTERFACE   T_STACK_INTERFACE
//#define METHOD        STACK_METHOD A RAJOUTER APRÈS POUR NE PAS AVOIR DU CODE PLUS PROPRE AVEC SEULEMENT DES METHOD
#if defined( T_STACK_EXPORT_DEFS )
#define T_EXPORT_DEFS
#endif

#undef T_STACK_IMPL_DEQUE
#undef T_STACK_TAG
#undef T_STACK_INTERFACE
#undef T_STACK_EXPORT_DEFS
#undef T_STACK_EXPORT_CODE
#undef T
#undef STACK_METHOD
