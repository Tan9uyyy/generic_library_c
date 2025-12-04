/*
 * Closed addressing hashtable.
 *
 * Variants:
 * T_IMPL_HASHTABLE_CLOSED_ADDRESSING_MOVE_TO_FRONT : Upon each successful
 * lookup of a key, it is moved to the front of the collision list it belongs
 * to.
 *
 */

#if defined(T_MAP_EXPORT_DEFS) || !defined(T_MAP_EXPORT_CODE)

/* On défini le load factor */
#ifndef LOAD_FACTOR
#define LOAD_FACTOR 0.75
#endif

/* On définit le nom du type couple de manière unique via GEN_SYM
   Ex: int_int_couple */
#ifdef COUPLE_TYPE
#undef COUPLE_TYPE
#endif
#define COUPLE_TYPE GEN_SYM(map_datum_t, couple)

typedef struct COUPLE_TYPE {
  T_MAP_KEY key;
#if !defined(T_SET_ELEMENT)
  T_MAP_VALUE value;
#endif
} COUPLE_TYPE;

/* Definition des macro comparator, destructor, printer pour le couple */
#define COMPARATOR(couple1, couple2)  KEY_COMPARATOR((couple1).key, (couple2).key)
#ifdef DESTRUCTOR_IS_NULL
#define DESTRUCTOR(couple) NULL
#else
#define DESTRUCTOR(couple) VALUE_DESTRUCTOR((couple).value)
#endif
#define PRINTER(couple) (printf("{"), KEY_PRINTER((couple).key), printf(","), VALUE_PRINTER((couple).value), printf("}"))

#undef list_datum_t
#define list_datum_t COUPLE_TYPE
#include <libellul/type/list.h>
#ifdef T_L
#undef T_L
#endif
#define T_L TYPE(list_datum_t, list)
#define LIST_METHOD(name) GEN_SYM(TYPENAME(list_datum_t, list), name)

#undef T
#define T GEN_SYM(T_MAP_TAG, t)

/* La structure principale de la Map */
typedef struct T {
  size_t count; /* Nombre d'éléments total */
  size_t length; /* Nombre de buckets */
  T_L *buckets; /* Tableau de tableau redimensionnable qui contient les listes de couple */
} *T;

#endif

#include <libellul/type/map/interface.h>

#if !defined(T_MAP_EXPORT_DEFS)
/* Code templating for the actual implementation starts here */

#include <libellul/memory.h>
#include <libellul/structure/hashtable/closed_addressing/closed_addressing_implementation.h>

#endif

#ifdef T_IMPL_HASHTABLE_CLOSED_ADDRESSING
#undef T_IMPL_HASHTABLE_CLOSED_ADDRESSING
#endif
#ifdef T_IMPL_HASHTABLE_CLOSED_ADDRESSING_MOVE_TO_FRONT
#undef T_IMPL_HASHTABLE_CLOSED_ADDRESSING_MOVE_TO_FRONT
#endif