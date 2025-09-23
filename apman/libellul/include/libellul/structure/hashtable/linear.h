/*
 * Linear addressing hashtable.
 *
 * Variants:
 * T_IMPL_HASHTABLE_LINEAR_NO_TOMBSTONES: Use backward-shifting deletion.
 *
 */

#if defined( T_MAP_EXPORT_DEFS ) || !defined( T_MAP_EXPORT_CODE )

typedef struct T {
  size_t       length;
  T_MAP_KEY   *bucket;

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

/* Of course we are entitled to functions that are always local: */
static inline int MAP_METHOD( foo_helper ) ( T map ) {
  /* Dummy example! Mostly useful to factorize code in the implementation! */
  return printf( "Called %s::%s on %sempty map at %p\n",
                 __FILE__, __func__, !MAP_METHOD( is_empty ) ( map ) ? "non-" : "", map );
}


T_MAP_INTERFACE T MAP_METHOD( new )( void ) {
  T map = NULL;

  /* In the implementation, use any local or interface function like: */
  MAP_METHOD( foo_helper ) ( map );

  /* TODO: Finish init */

  return map;
}

/* TODO: Implement other functions in the interface */

T_MAP_INTERFACE size_t MAP_METHOD( length )( T map ) {
  return 0 == map->length;
}

T_MAP_INTERFACE void   MAP_METHOD( delete )( T *map ) {

}

T_MAP_INTERFACE int    MAP_METHOD( contains )( T map, T_MAP_KEY key ) {

}

T_MAP_INTERFACE int    MAP_METHOD( remove )( T *map, T_MAP_KEY key ) {

}

#if defined( T_SET_ELEMENT )
T_MAP_INTERFACE int    MAP_METHOD( insert )( T *set, T_SET_ELEMENT element ) {

}
#else
T_MAP_INTERFACE int    MAP_METHOD( put )( T *map, T_MAP_KEY key, T_MAP_VALUE value ) {

}

T_MAP_INTERFACE int    MAP_METHOD( get )( T map, T_MAP_KEY key, T_MAP_VALUE *value ) {

}
#endif

#endif

#undef T_IMPL_HASHTABLE_LINEAR
#undef T_IMPL_HASHTABLE_LINEAR_NO_TOMBSTONES
