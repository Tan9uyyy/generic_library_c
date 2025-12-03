#include <libellul.h>

#define T_IMPL_HASHTABLE
#define T_IMPL_HASHTABLE_CLOSED_ADDRESSING
#define T_MAP_TAG int_int_closed_addressing_hashtable
#define T_MAP_KEY int
#define T_MAP_VALUE int

#define HASH(key) ((key) % 13)
#define VALUE_DESTRUCTOR(val) NULL
#define DESTRUCTOR_IS_NULL // macro flag pour indiquer que le destructeur est NULL (ça me simplifie pour les if parce que sinonje comprends rien)
#define KEY_COMPARATOR(val1, val2) ((val1) == (val2))
#define VALUE_PRINTER(val) printf("%d", (val))

#include <libellul/type/map.h>

static void closed_addressing_NULL(void) {
  int value = 42;
  int_int_closed_addressing_hashtable_t hashtable = NULL;

  test_suite("NULL as an hashtable");

  test_assert(0 == int_int_closed_addressing_hashtable_length(NULL),
              "NULL is an hashtable of length zero");
  test_assert(int_int_closed_addressing_hashtable_is_empty(NULL),
              "NULL is an the empty hashtable");

  test_assert(0 == int_int_closed_addressing_hashtable_contains(NULL, 42), "NULL cannot contain anywhat");

  int_int_closed_addressing_hashtable_delete(NULL);
  test_assert(1, "Can delete NULL as an hashtable");

  test_suite("NULL variable as an hashtable");

  test_assert(0 == int_int_closed_addressing_hashtable_length(hashtable),
              "A NULL hashtable has length zero");
  test_assert(int_int_closed_addressing_hashtable_is_empty(hashtable),
              "A NULL hashtable is empty");

  int_int_closed_addressing_hashtable_delete(&hashtable);
  test_assert(NULL == hashtable, "Can delete a NULL hashtable");

  // test_abort( int_int_closed_addressing_hashtable_put( &hashtable, 3, value),
  // "Cannot put to NULL hashtable" ); test_abort(
  // int_int_closed_addressing_hashtable_remove( &hashtable, 3), "Cannot remove
  // from NULL hashtable" ); test_abort(
  // int_int_closed_addressing_hashtable_get( hashtable, 3, &value ), "Cannot
  // get from NULL hashtable" );
}
/*
int *rand_ints( size_t n ) {
  int *vec = calloc( n, sizeof( *vec ) );
  assert( vec );

  for ( size_t i = 0 ; i < n ; i++ ) vec[ i ] = rand() % 50;

  return vec;
}
*/

// void int_int_closed_addressing_hashtable_stack( size_t n ) {
//   int *truth = rand_ints( n );

//   int *hashtable = hashtable( int );

//   test_assert( int_int_closed_addressing_hashtable_is_empty( hashtable ), "A
//   new hashtable is empty" );

//   for ( size_t i = 0 ; i < n ; i++ ) {
//     int_int_closed_addressing_hashtable_push( &hashtable, truth[ i ] );
//     test_assert( truth[ i ] == hashtable[ i ], "Can push to hashtable" );
//   }

//   for ( size_t i = 0 ; i < n ; i++ ) {
//     int popped = -1;
//     int_int_closed_addressing_hashtable_pop( &hashtable, &popped );
//     test_assert( truth[ n-1-i ] == popped, "Can pop from hashtable" );
//   }

//   test_assert( hashtable && int_int_closed_addressing_hashtable_is_empty(
//   hashtable ), "Empty, non-NULL hashtable at the end" );

//   int_int_closed_addressing_hashtable_delete( &hashtable );
//   test_assert( NULL == hashtable, "hashtable is NULL after delete" );

//   free( truth );
// }

int main(int argc, char *argv[]) {

  unit_test(argc, argv);

  test_suite("\n\n\n ================================================ TEST 11-closed-addressing.c =========================================================");

  closed_addressing_NULL();
  // int_int_closed_addressing_hashtable_stack( 13 );

  exit(EXIT_SUCCESS);
}