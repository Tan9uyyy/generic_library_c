/*
 * Linear addressing hashtable.
 *
 * Variants:
 * T_IMPL_HASHTABLE_LINEAR_NO_TOMBSTONES: Use backward-shifting deletion.
 *
 */

#if defined( T_MAP_EXPORT_DEFS ) || !defined( T_MAP_EXPORT_CODE )

#ifndef LOAD_FACTOR
#define LOAD_FACTOR 0.55
#endif
#define ARRAY_ALLOC_MIN HASHTABLE_SIZE
#define ARRAY_ALLOC_GEOM 2.0

typedef struct T {
  size_t       length; /* le nombre de couple qu'il y a dans la table */
#if !defined ( T_IMPL_HASHTABLE_LINEAR_NO_TOMBSTONES )
  size_t tombstones; /* le nombre de tombstones dans la table */
#endif
  T_MAP_KEY   *bucket;
  int *occupied; /* tableau d'indicateurs d'occupation des cases */
#if !defined ( T_SET_ELEMENT )
  T_MAP_VALUE *value;
#endif
} *T;

#endif

#include <libellul/type/map/interface.h>

#if !defined( T_MAP_EXPORT_DEFS )
/* Code templating for the actual implementation starts here */

#include <libellul/memory.h>
#include <libellul/type/array.h>
#include <libellul/structure/hashtable/linear/linear_implementation.h>

#endif

#ifdef T_IMPL_HASHTABLE_LINEAR
#undef T_IMPL_HASHTABLE_LINEAR
#endif
#ifdef T_IMPL_HASHTABLE_LINEAR_NO_TOMBSTONES
#undef T_IMPL_HASHTABLE_LINEAR_NO_TOMBSTONES
#endif
