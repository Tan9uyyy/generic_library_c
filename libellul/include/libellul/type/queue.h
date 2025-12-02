/*
 * 'queue' abstract data type.
 *
 * Available type implementations:
 *
 * T_IMPL_DEQUE (default)
 * T_IMPL_DYN_ARRAY
 * ...
 *
 */

#ifndef T_QUEUE_TAG
#error "Undefined T_QUEUE_TAG"
#endif

#ifndef queue_datum_t
#error "Undefined queue datum type !"
#endif

#include <libellul/type/prologue.h>

#if !defined( T_QUEUE_EXPORT_DEFS ) && !defined( T_QUEUE_EXPORT_CODE )
#define T_QUEUE_INTERFACE static inline
#else
#define T_QUEUE_INTERFACE extern
#endif

#ifdef T
#undef T
#endif
#define T                      GEN_SYM( T_QUEUE_TAG, t )
#define QUEUE_METHOD( name )     GEN_SYM( T_QUEUE_TAG, name )


#if defined( T_IMPL_DYN_ARRAY )
#include <libellul/type/array.h>
#else /* Default data structure for a QUEUE is a deque */
#define T_QUEUE_IMPL_DEQUE
#define deque_datum_t queue_datum_t
#define T_DEQUE_TAG GEN_SYM(deque_datum_t, deque)
#define DEQUE_METHOD( name )     GEN_SYM( T_DEQUE_TAG, name )
#include <libellul/structure/deque.h>
#endif

#define T_INTERFACE   T_QUEUE_INTERFACE
//#define METHOD        QUEUE_METHOD A RAJOUTER APRÈS POUR NE PAS AVOIR DU CODE PLUS PROPRE AVEC SEULEMENT DES METHOD
#if defined( T_QUEUE_EXPORT_DEFS )
#define T_EXPORT_DEFS
#endif

#undef T_QUEUE_IMPL_DEQUE
#undef T_QUEUE_TAG
#undef T_QUEUE_INTERFACE
#undef T_QUEUE_EXPORT_DEFS
#undef T_QUEUE_EXPORT_CODE
#undef T
#undef QUEUE_METHOD
