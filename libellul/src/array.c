#include <libellul/type/array.h>

#include <libellul/memory.h>

#include <assert.h>
#include <string.h>

/*

   alloc_ptr
      v
      +---------+---------------+
      |  header |  data slots   |
      +---------+---------------+
                ^
            user_ptr

*/

typedef struct {
  size_t length;
  size_t allocd;
  size_t size;
  int    strict;
} array_header_t;

#define ARRAY_HEADER( array ) (((array_header_t*)(array))-1)

#if !defined( ARRAY_ALLOC_GEOM )
#define ARRAY_ALLOC_GEOM         1.3
#endif

#if !defined( ARRAY_ALLOC_MIN )
#define ARRAY_ALLOC_MIN          8
#endif

/*
 * Dynamic arrays by genericity with hidden metadata.
 *
 * An array contains 'length' elements of 'size' bytes,
 * with enough room for 'allocd' >= 'length' of them.
 * This is called amortized allocation.
 *
 * Amortized allocation will typically pre-allocate
 * ARRAY_ALLOC_MIN slots and the growth of 'allocd'
 * is a geometric progession of ratio ARRAY_ALLOC_GEOM.
 *
 * If 'strict' is non-zero, amortized allocation is
 * disabled and 'allocd' == 'length' at all times.
 *
 */

void   *array_new__( size_t nmemb, size_t size, int strict ) {
  /* TODO: Create new array. */

  if (strict) {

    array_header_t *array = malloc(sizeof(array_header_t) + (nmemb*size));
    array->length = nmemb; array->allocd = array->length; array->strict = strict; array->size = size;

    return 1 + array;
  }
  
  int alloc = ARRAY_ALLOC_MIN;
  if((int)(ARRAY_ALLOC_GEOM*nmemb*size) > ARRAY_ALLOC_MIN){
    alloc = (int) (ARRAY_ALLOC_GEOM*nmemb);
  }
  array_header_t *array = malloc(sizeof(array_header_t) + (int)(ARRAY_ALLOC_GEOM*(nmemb*size)));
  array->length=nmemb; array->allocd = (int)(ARRAY_ALLOC_GEOM*nmemb); array->strict = strict; array->size = size;
  
  return 1 + array;
}

void    array_delete__( void **array_ptr ) {
  /* TODO: Delete array, set *array_ptr to NULL. */
  if(**array_ptr != NULL){
    if (*array_ptr != NULL){
    array_header_t *array = ARRAY_HEADER(*array_ptr);
    free(1 + array);
    *array_ptr = NULL;
    free(array);
    }
  }
}

size_t  array_length( void *array ) {
  return array ? ARRAY_HEADER( array )->length : 0;
}


size_t  array_resize__( void **array_ptr, size_t nmemb ) {
  array_header_t *header;

  assert( array_ptr && *array_ptr && "Array must be allocated first!" );

  header = ARRAY_HEADER( *array_ptr );

  /* TODO: Actually do the resize, update header and *array_ptr */

  return header->length;
}

#undef ARRAY_HEADER
#undef ARRAY_ALLOC_GEOM
#undef ARRAY_ALLOC_MIN
