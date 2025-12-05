#include "benchmark.h"

#include <stdio.h>

#include <libellul.h>

#define T_IMPL_HASHTABLE
/* choix de l'implémentation : soit
* T_IMPL_HASHTABLE_CLOSED_ADDRESSING pour l'implémentation normale 
* T_IMPL_HASHTABLE_CLOSED_ADDRESSING_MOVE_TO_FRONT pour l'implé move_to_front */
#define T_IMPL_HASHTABLE_CLOSED_ADDRESSING
#define T_MAP_TAG size_t_size_t_closed_addressing_hashtable
#define T_MAP_KEY size_t
#define T_MAP_VALUE size_t

#define HASHTABLE_SIZE 13 
#define HASH(key) (key)
#define VALUE_DESTRUCTOR(val) NULL
#define DESTRUCTOR_IS_NULL // macro flag pour indiquer que le destructeur est NULL (ça me simplifie pour les if parce que sinonje comprends rien)
#define KEY_COMPARATOR(val1, val2) ((val1) == (val2))
#define KEY_PRINTER(val) printf("%d", (int)(val))
#define VALUE_PRINTER(val) printf("%d", (int)(val))

#include <libellul/type/map.h>

static int  onhashtable_closed_put( size_t N ) {
  size_t_size_t_closed_addressing_hashtable_t hashtable = size_t_size_t_closed_addressing_hashtable_new();
  int sum = 0;

  for ( size_t i = 0 ; i < N ; i++ ) {
    size_t_size_t_closed_addressing_hashtable_put(&hashtable, i, i);
    sum += i;
  }

  size_t_size_t_closed_addressing_hashtable_delete(&hashtable);

  return sum;
}

#undef T_IMPL_HASHTABLE_CLOSED_ADDRESSING
#define T_IMPL_HASHTABLE_LINEAR_NO_TOMBSTONES
#define T_MAP_TAG size_t_size_t_linear_hashtable
#define T_MAP_KEY size_t
#define T_MAP_VALUE size_t

#include <libellul/type/map.h>

static int  onhashtable_linear_put( size_t N ) {
  size_t_size_t_linear_hashtable_t hashtable = size_t_size_t_linear_hashtable_new();
  int sum = 0;

  for ( size_t i = 0 ; i < N ; i++ ) {
    size_t_size_t_linear_hashtable_put(&hashtable, i, i);
    sum += i;
  }

  size_t_size_t_linear_hashtable_delete(&hashtable);

  return sum;
}









static void benchmark( size_t N, size_t runs ) {
  size_t s1, s2;

  for ( size_t run = 0 ; run < runs ; run++ )
    s1 = run + onhashtable_closed_put( N ); /* Perform test for onhashtable_push_back column */

  printf( "%10.2g\t,", elapsed_nsec()/(runs*N) ); /* Normalize execution time by N  */

  elapsed_nsec();

  for ( size_t run = 0 ; run < runs ; run++ )
    s2 = run + onhashtable_linear_put( N ); /* Perform test for onhashtable_push_back column */

  printf( "%10.2g\t,", elapsed_nsec()/(runs*N) ); /* Normalize execution time by N  */

  /* Actually use the values so the compiler keeps all code */
  if ( !s1 || !s2 ) abort();
}

int main () {

  /* Warmup: Force dummy calls to all useful functions beforehand */
  fprintf( stderr, "%g\r", elapsed_nsec() );
  onhashtable_closed_put( LOG2_N_MAX );

  /* Prsize_t CSV header */
  printf( " log2(N)   \t,  onhashtable_closed_put      \t,  onhashtable_linear_put      \t\n" );
  for ( size_t log2_N = LOG2_N_MIN ; log2_N < LOG2_N_MAX+1 ; log2_N++ ) {
    fprintf( stderr, "N = %zu\r", (size_t)1 << log2_N ); /* User output on stderr */

    printf( "%10zu\t, ", log2_N ); /* CSV on standard output */

    benchmark( 1 << log2_N, RUNS );

    printf( "\n" ); /* End of CSV line  */
  }

  fprintf( stderr, "--END OF %s--\n", __FILE__ ); /* User output */

  exit( EXIT_SUCCESS );
}