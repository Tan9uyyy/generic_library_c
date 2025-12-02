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

/* On définit le type de la hashtable en fonction du type des clés et des valeurs */
#ifdef map_datum_t
#undef datum_t
#endif
#if !defined( T_SET_ELEMENT )
#define map_datum_t GEN_SYM(T_MAP_KEY, T_MAP_VALUE)
#else
#define map_datum_t T_MAP_KEY
#endif

/* On définit le nom du type couple de manière unique via GEN_SYM 
   Ex: int_int_closed_addressing_couple */
#ifdef COUPLE_TYPE
#undef COUPLE_TYPE
#endif
#define COUPLE_TYPE GEN_SYM(map_datum_t, couple)

typedef struct COUPLE_TYPE {
    T_MAP_KEY key;
#if !defined( T_SET_ELEMENT )
    T_MAP_VALUE value;
#endif
} COUPLE_TYPE;

#undef list_datum_t
#define list_datum_t COUPLE_TYPE
#include "../../type/list/list-implementation.h"
#undef T_L
#define T_L TYPE(list, list_datum_t)

#ifdef T
#undef T
#endif
#define T TYPE(closed_addressing_hashtable, map_datum_t)

/* La structure principale de la Map */
typedef struct T {
  size_t    count;      /* Nombre d'éléments total */
  T_L      *buckets;    /* Tableau de tableau redimensionnable qui contient les listes de couple */
} *T;

#undef T

#endif

#include <libellul/type/map/interface.h>

#if !defined( T_MAP_EXPORT_DEFS )
/* Code templating for the actual implementation starts here */

#include <libellul/memory.h>
#include <libellul/type/array.h>

#include <libellul/type/closed_addressing/closed-adressing-export-defs.h>

#undef T_IMPL_HASHTABLE_CLOSED_ADDRESSING_H