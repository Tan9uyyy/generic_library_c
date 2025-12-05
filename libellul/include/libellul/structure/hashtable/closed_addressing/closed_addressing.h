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

#ifndef map_datum_t
#ifdef T_SET_ELEMENT
#define map_datum_t T_MAP_KEY
#else
#define map_datum_t GEN_SYM(T_MAP_KEY, T_MAP_VALUE)
#endif
#endif

#ifdef T_SET_ELEMENT
#define CLOSED_ADDR_DATUM T_MAP_KEY
#else
#define CLOSED_ADDR_DATUM GEN_SYM(T_MAP_KEY, T_MAP_VALUE)
#endif

/* On définit le nom du type couple de manière unique via GEN_SYM
   Ex: int_int_couple */
#ifdef COUPLE_TYPE
#undef COUPLE_TYPE
#endif
#define COUPLE_TYPE GEN_SYM(CLOSED_ADDR_DATUM, couple)

typedef struct COUPLE_TYPE {
  T_MAP_KEY key;
#if !defined(T_SET_ELEMENT)
  T_MAP_VALUE value;
#endif
} COUPLE_TYPE;

/* Definition des macro comparator, destructor, printer pour le couple */
#define COMPARATOR(couple1, couple2)                                           \
  KEY_COMPARATOR((couple1).key, (couple2).key)
#ifdef DESTRUCTOR_IS_NULL
#define DESTRUCTOR(couple) NULL
#else
#define DESTRUCTOR(couple) VALUE_DESTRUCTOR((couple).value)
#endif
#ifdef T_SET_ELEMENT
#define PRINTER(couple) (printf("{"), KEY_PRINTER((couple).key), printf("}"))
#else
#define PRINTER(couple)                                                        \
  (printf("{"), KEY_PRINTER((couple).key), printf(","),                        \
   VALUE_PRINTER((couple).value), printf("}"))
#endif

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
  size_t count;  /* Nombre d'éléments total dans la map */
  size_t length; /* Nombre de buckets (taille de la map) */
  T_L *buckets;  /* Tableau de tableau redimensionnable qui contient les listes
                    de couple */
} *T;

#endif

#include <libellul/type/map/interface.h>

#if !defined(T_MAP_EXPORT_DEFS)
/* Code templating for the actual implementation starts here */

#include <libellul/memory.h>
#include <libellul/structure/hashtable/closed_addressing/closed_addressing_implementation.h>

struct MAP_METHOD(iterator) {
  T map;
  size_t bucket_index;
  struct TYPE(node, COUPLE_TYPE) * current_node;
};

T_MAP_INTERFACE MAP_METHOD(iterator_t) MAP_METHOD(iterator_new)(T map) {
  MAP_METHOD(iterator_t) it = malloc(sizeof(*it));
  if (!it)
    return NULL;
  it->map = map;
  it->bucket_index = 0;
  it->current_node = NULL;

  if (map) {
    while (it->bucket_index < map->length) {
      T_L list = map->buckets[it->bucket_index];
      if (list && list->head) {
        it->current_node = list->head;
        break;
      }
      it->bucket_index++;
    }
  }
  return it;
}

T_MAP_INTERFACE int MAP_METHOD(iterator_has_next)(MAP_METHOD(iterator_t) it) {
  if (!it || !it->map)
    return 0;
  return it->current_node != NULL;
}

T_MAP_INTERFACE T_MAP_KEY MAP_METHOD(iterator_next)(MAP_METHOD(iterator_t) it) {
  if (!it || !it->current_node)
    return (T_MAP_KEY){0};

  COUPLE_TYPE couple = it->current_node->datum;
  T_MAP_KEY key = couple.key;

  it->current_node = it->current_node->next;
  if (!it->current_node ||
      it->current_node == it->map->buckets[it->bucket_index]->head) {
    it->bucket_index++;
    while (it->bucket_index < it->map->length) {
      T_L list = it->map->buckets[it->bucket_index];
      if (list && list->head) {
        it->current_node = list->head;
        break;
      }
      it->bucket_index++;
    }
    /* If we reached the end of buckets, ensure current_node is NULL */
    if (it->bucket_index >= it->map->length) {
      it->current_node = NULL;
    }
  }
  return key;
}

T_MAP_INTERFACE void MAP_METHOD(iterator_delete)(MAP_METHOD(iterator_t) * it) {
  if (it && *it) {
    free(*it);
    *it = NULL;
  }
}

#endif

#ifdef T_IMPL_HASHTABLE_CLOSED_ADDRESSING
#undef T_IMPL_HASHTABLE_CLOSED_ADDRESSING
#endif
#ifdef T_IMPL_HASHTABLE_CLOSED_ADDRESSING_MOVE_TO_FRONT
#undef T_IMPL_HASHTABLE_CLOSED_ADDRESSING_MOVE_TO_FRONT
#endif