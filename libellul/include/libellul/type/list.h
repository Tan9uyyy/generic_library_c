/*
 * 'list' abstract data type.
 *
 * Available type implementations:
 *
 * T_IMPL_DEQUE (default)
 *
 */

#ifndef T_LIST_TAG
#error "Undefined T_LIST_TAG"
#endif

#ifndef list_datum_t
#error "Undefined list datum type !"
#endif

#include <libellul/type/prologue.h>

#if !defined( T_LIST_EXPORT_DEFS ) && !defined( T_LIST_EXPORT_CODE )
#define T_LIST_INTERFACE static inline
#else
#define T_LIST_INTERFACE extern
#endif

#ifdef T
#undef T
#endif
#define T                      GEN_SYM( T_LIST_TAG, t )
#define LIST_METHOD( name )     GEN_SYM( T_LIST_TAG, name )


/* on implémente forcément une liste avec une deque */
#define T_LIST_IMPL_DEQUE
#define deque_datum_t list_datum_t
#define T_DEQUE_TAG GEN_SYM(deque_datum_t, deque)
#define DEQUE_METHOD( name )     GEN_SYM( T_DEQUE_TAG, name )
#include <libellul/structure/deque.h>


#define T_INTERFACE   T_LIST_INTERFACE
//#define METHOD        LIST_METHOD A RAJOUTER APRÈS POUR NE PAS AVOIR DU CODE PLUS PROPRE AVEC SEULEMENT DES METHOD
#if defined( T_LIST_EXPORT_DEFS )
#define T_EXPORT_DEFS
#endif

#undef T_LIST_IMPL_DEQUE
#undef T_LIST_TAG
#undef T_LIST_INTERFACE
#undef T_LIST_EXPORT_DEFS
#undef T_LIST_EXPORT_CODE
#undef T
#undef LIST_METHOD
