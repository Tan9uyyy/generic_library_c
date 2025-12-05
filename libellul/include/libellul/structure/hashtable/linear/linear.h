/*
 * Linear addressing hashtable.
 *
 * Variants:
 * T_IMPL_HASHTABLE_LINEAR_NO_TOMBSTONES: Use backward-shifting deletion.
 *
 */

#if defined(T_MAP_EXPORT_DEFS) || !defined(T_MAP_EXPORT_CODE)

#ifndef LOAD_FACTOR
#define LOAD_FACTOR 0.55
#endif
#define ARRAY_ALLOC_MIN HASHTABLE_SIZE
#define ARRAY_ALLOC_GEOM 2.0

typedef struct T {
  size_t length; /* le nombre de couple qu'il y a dans la table */
#if defined(T_IMPL_HASHTABLE_LINEAR)
  size_t tombstones; /* le nombre de tombstones dans la table */
#endif
  T_MAP_KEY *bucket;
  int *occupied; /* tableau d'indicateurs d'occupation des cases */
#if !defined(T_SET_ELEMENT)
  T_MAP_VALUE *value;
#endif
} *T;

#endif

#include <libellul/type/map/interface.h>

#if !defined(T_MAP_EXPORT_DEFS)
/* Code templating for the actual implementation starts here */

#include <libellul/memory.h>
#include <libellul/structure/hashtable/linear/linear_implementation.h>
#include <libellul/type/array.h>

struct MAP_METHOD(iterator) {
  T map;
  size_t index;
};

T_MAP_INTERFACE MAP_METHOD(iterator_t) MAP_METHOD(iterator_new)(T map) {
  MAP_METHOD(iterator_t) it = malloc(sizeof(*it));
  if (!it)
    return NULL;
  it->map = map;
  it->index = 0;
  if (map) {
    size_t size = array_size(map->bucket);
    while (it->index < size && map->occupied[it->index] < 0) {
      it->index++;
    }
  }
  return it;
}

T_MAP_INTERFACE int MAP_METHOD(iterator_has_next)(MAP_METHOD(iterator_t) it) {
  if (!it || !it->map)
    return 0;
  size_t size = array_size(it->map->bucket);
  return it->index < size;
}

T_MAP_INTERFACE T_MAP_KEY MAP_METHOD(iterator_next)(MAP_METHOD(iterator_t) it) {
  if (!it || !it->map)
    return (T_MAP_KEY){0};
  T_MAP_KEY key = it->map->bucket[it->index];

  size_t size = array_size(it->map->bucket);
  it->index++;
  while (it->index < size && it->map->occupied[it->index] < 0) {
    it->index++;
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

#ifdef T_IMPL_HASHTABLE_LINEAR
#undef T_IMPL_HASHTABLE_LINEAR
#endif
#ifdef T_IMPL_HASHTABLE_LINEAR_NO_TOMBSTONES
#undef T_IMPL_HASHTABLE_LINEAR_NO_TOMBSTONES
#endif
#ifdef T_IMPL_HASHTABLE_ROBIN_HOOD
#undef T_IMPL_HASHTABLE_ROBIN_HOOD
#endif
