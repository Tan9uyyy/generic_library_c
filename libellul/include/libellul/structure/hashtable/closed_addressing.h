/*
 * Closed addressing hashtable.
 *
 * Variants:
 * T_IMPL_HASHTABLE_CLOSED_ADDRESSING_MOVE_TO_FRONT : Upon each successful lookup of a key, it is moved to the front of the collision list it belongs to.
 *
 */

#if defined( T_MAP_EXPORT_DEFS ) || !defined( T_MAP_EXPORT_CODE )

#include "../../generics.h"
#include "../../interface.h"

/* On définit le nom du type couple de manière unique via GEN_SYM 
   Ex: int_int_closed_addressing_couple */
#undef COUPLE_TYPE
#define COUPLE_TYPE GEN_SYM(T_MAP_TAG, couple)

typedef struct COUPLE_TYPE {
    T_MAP_KEY key;
#if !defined( T_SET_ELEMENT )
    T_MAP_VALUE value;
#endif
} COUPLE_TYPE;

/* La structure principale de la Map */
typedef struct T {
  size_t    count;      /* Nombre d'éléments total */
  void      *buckets;    /* Tableau de tableau redimensionnable qui contient les listes de couple */
} *T;

#endif

#undef T_IMPL_HASHTABLE_CLOSED_ADDRESSING_H