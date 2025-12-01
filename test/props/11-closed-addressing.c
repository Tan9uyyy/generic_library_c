#include <libellul.h>
/*
#define T_IMPL_HASHTABLE
#define T_IMPL_HASHTABLE_CLOSED_ADDRESSING
#define T_MAP_TAG closed_addressing_hashtable_int_int
#define T_MAP_KEY int
#define T_MAP_VALUE int

#include <libellul/type/map.h>

#define destructor NULL

int comparator(int val1, int val2) { return val1 == val2; }

static void closed_addressing_NULL( void ) {
  int  value = 42;
  int *hashtable = NULL;

  test_suite( "NULL as an hashtable" );

  test_assert( 0 == closed_addressing_hashtable_int_int_length( NULL ), "NULL is an hashtable of length zero" );
  test_assert( closed_addressing_hashtable_int_int_is_empty( NULL ), "NULL is an the empty hashtable" );

  test_abort( closed_addressing_hashtable_int_int_contains( NULL, 42, comparator), "NULL cannot contain anywhat" );

  closed_addressing_hashtable_int_int_delete( NULL );
  test_assert( 1, "Can delete NULL as an hashtable" );


  test_suite( "NULL variable as an hashtable" );

  test_assert( 0 == closed_addressing_hashtable_int_int_length( hashtable ), "A NULL hashtable has length zero" );
  test_assert( closed_addressing_hashtable_int_int_is_empty( hashtable ), "A NULL hashtable is empty" );

  closed_addressing_hashtable_int_int_delete( &hashtable );
  test_assert( NULL == hashtable, "Can delete a NULL hashtable" );

  test_abort( closed_addressing_hashtable_int_int_put( &hashtable, 3 ), "Cannot put to NULL hashtable" );
  test_abort( closed_addressing_hashtable_int_int_remove( &hashtable, &value ), "Cannot remove from NULL hashtable" );
  test_abort( closed_addressing_hashtable_int_int_get( hashtable, 3, &value ), "Cannot get from NULL hashtable" );
}*/
/*
int *rand_ints( size_t n ) {
  int *vec = calloc( n, sizeof( *vec ) );
  assert( vec );

  for ( size_t i = 0 ; i < n ; i++ ) vec[ i ] = rand() % 50;

  return vec;
}
*/
/*
void closed_addressing_hashtable_int_int_stack( size_t n ) {
  int *truth = rand_ints( n );

  int *hashtable = hashtable( int );

  test_assert( closed_addressing_hashtable_int_int_is_empty( hashtable ), "A new hashtable is empty" );

  for ( size_t i = 0 ; i < n ; i++ ) {
    closed_addressing_hashtable_int_int_push( &hashtable, truth[ i ] );
    test_assert( truth[ i ] == hashtable[ i ], "Can push to hashtable" );
  }

  for ( size_t i = 0 ; i < n ; i++ ) {
    int popped = -1;
    closed_addressing_hashtable_int_int_pop( &hashtable, &popped );
    test_assert( truth[ n-1-i ] == popped, "Can pop from hashtable" );
  }

  test_assert( hashtable && closed_addressing_hashtable_int_int_is_empty( hashtable ), "Empty, non-NULL hashtable at the end" );

  closed_addressing_hashtable_int_int_delete( &hashtable );
  test_assert( NULL == hashtable, "hashtable is NULL after delete" );

  free( truth );
}
*/

int main ( int argc, char *argv[] ) {

  //unit_test( argc, argv );

  //closed_addressing_NULL();
  //closed_addressing_hashtable_int_int_stack( 13 );

  exit( EXIT_SUCCESS );
}