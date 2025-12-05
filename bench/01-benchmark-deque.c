#include "benchmark.h"

#include <stdio.h>

#define T_DEQUE
#define T_DEQUE_TAG size_t_deque
#define deque_datum_t size_t
#define T size_t_deque_t

#define DESTRUCTOR(val) NULL
#define DESTRUCTOR_IS_NULL // macro flag pour indiquer que le destructeur est
                           // NULL (ça me simplifie pour les if parce que sinon
                           // je comprends rien)
#define COMPARATOR(val1, val2) ((val1) == (val2))
#define PRINTER(val) printf("%d", (int)(val))

#include <libellul.h>
#include <libellul/type/deque.h>

static int  ondeque_push_front( size_t N ) {
  size_t_deque_t deque = size_t_deque_new();
  int sum = 0;

  for ( size_t i = 0 ; i < N ; i++ ) {
    deque = size_t_deque_push_front(i, deque);
    sum += i;
  }

  size_t_deque_delete(deque);

  return sum;
}

static int  ondeque_push_back( size_t N ) {
  size_t_deque_t deque = size_t_deque_new();
  int sum = 0;

  for ( size_t i = 0 ; i < N ; i++ ) {
    deque = size_t_deque_push_back(i, deque);
    sum += i;
  }

  size_t_deque_delete(deque);

  return sum;
}

static int  ondeque_pop_front( size_t N ) {
  size_t_deque_t deque = size_t_deque_new();
  int sum = 0; size_t storage;

  for ( size_t i = 0 ; i < N ; i++ ) {
    deque = size_t_deque_push_front(i, deque);
  }

  elapsed_nsec();

  for ( size_t i = 0 ; i < N ; i++ ) {
    deque = size_t_deque_pop_front(&storage, deque);
    sum += i;
  }

  size_t_deque_delete(deque);

  return sum;
}

static int  ondeque_pop_back( size_t N ) {
  size_t_deque_t deque = size_t_deque_new();
  int sum = 0; size_t storage;

  for ( size_t i = 0 ; i < N ; i++ ) {
    deque = size_t_deque_push_back(i, deque);
  }

  elapsed_nsec();

  for ( size_t i = 0 ; i < N ; i++ ) {
    deque = size_t_deque_pop_back(&storage, deque);
    sum += i;
  }

  size_t_deque_delete(deque);

  return sum;
}

#undef T_DEQUE_TAG
#undef deque_datum_t
#undef T

#define T_DEQUE_TAG size_t_deque_array
#define deque_datum_t size_t
#define T size_t_deque_array_t
#define T_DEQUE_IMPL_ARRAY
#include <libellul/type/deque.h>

static int  ondeque_array_push_front( size_t N ) {
  size_t_deque_array_t deque = size_t_deque_array_new();
  int sum = 0;

  for ( size_t i = 0 ; i < N ; i++ ) {
    deque = size_t_deque_array_push_front(i, deque);
    sum += i;
  }

  size_t_deque_array_delete(deque);

  return sum;
}

static int  ondeque_array_push_back( size_t N ) {
  size_t_deque_array_t deque = size_t_deque_array_new();
  int sum = 0;

  for ( size_t i = 0 ; i < N ; i++ ) {
    deque = size_t_deque_array_push_back(i, deque);
    sum += i;
  }

  size_t_deque_array_delete(deque);

  return sum;
}

static int  ondeque_array_pop_front( size_t N ) {
  size_t_deque_array_t deque = size_t_deque_array_new();
  int sum = 0; size_t storage;

  for ( size_t i = 0 ; i < N ; i++ ) {
    deque = size_t_deque_array_push_front(i, deque);
  }

  elapsed_nsec();

  for ( size_t i = 0 ; i < N ; i++ ) {
    deque = size_t_deque_array_pop_front(&storage, deque);
    sum += i;
  }

  size_t_deque_array_delete(deque);

  return sum;
}

static int  ondeque_array_pop_back( size_t N ) {
  size_t_deque_array_t deque = size_t_deque_array_new();
  int sum = 0; size_t storage;

  for ( size_t i = 0 ; i < N ; i++ ) {
    deque = size_t_deque_array_push_back(i, deque);
  }

  elapsed_nsec();

  for ( size_t i = 0 ; i < N ; i++ ) {
    deque = size_t_deque_array_pop_back(&storage, deque);
    sum += i;
  }

  size_t_deque_array_delete(deque);

  return sum;
}

static void benchmark( size_t N, int runs ) {
  int s1, s2, s3, s4;
  int p1, p2, p3, p4;

  for ( int run = 0 ; run < runs ; run++ )
    s1 = run + ondeque_push_front( N ); /* Perform test for ondeque_push_back column */

  printf( "%10.2g\t,", elapsed_nsec()/(runs*N) ); /* Normalize execution time by N  */

  elapsed_nsec();

  for ( int run = 0 ; run < runs ; run++ )
    s2 = run + ondeque_array_push_front( N );

  printf( "%10.2g\t,", elapsed_nsec()/(runs*N) ); /* Normalize execution time by N  */

  elapsed_nsec(); /* Reset clock */

  for ( int run = 0 ; run < runs ; run++ )
    s3 = run + ondeque_push_back( N ); /* Perform test for ondeque_push_back column */

  printf( "%10.2g\t,", elapsed_nsec()/(runs*N) ); /* Normalize execution time by N  */

  elapsed_nsec();

  for ( int run = 0 ; run < runs ; run++ )
    s4 = run + ondeque_array_push_back( N );

  printf( "%10.2g\t,", elapsed_nsec()/(runs*N) ); /* Normalize execution time by N  */






  for ( int run = 0 ; run < runs ; run++ )
    p1 = run + ondeque_pop_front( N ); /* Perform test for ondeque_push_back column */

  printf( "%10.2g\t,", elapsed_nsec()/(runs*N) ); /* Normalize execution time by N  */

  elapsed_nsec();

  for ( int run = 0 ; run < runs ; run++ )
    p2 = run + ondeque_array_pop_front( N );

  printf( "%10.2g\t,", elapsed_nsec()/(runs*N) ); /* Normalize execution time by N  */

  elapsed_nsec(); /* Reset clock */

  for ( int run = 0 ; run < runs ; run++ )
    p3 = run + ondeque_pop_back( N ); /* Perform test for ondeque_push_back column */

  printf( "%10.2g\t,", elapsed_nsec()/(runs*N) ); /* Normalize execution time by N  */

  elapsed_nsec();

  for ( int run = 0 ; run < runs ; run++ )
    p4 = run + ondeque_array_pop_back( N );

  printf( "%10.2g\t,", elapsed_nsec()/(runs*N) ); /* Normalize execution time by N  */






  /* Actually use the values so the compiler keeps all code */
  if ( !s1 || !s2 || !s3 || !s4) abort();
  if ( !p1 || !p2 || !p3 || !p4) abort();
}

int main () {

  /* Warmup: Force dummy calls to all useful functions beforehand */
  fprintf( stderr, "%g\r", elapsed_nsec() );
  ondeque_array_push_back( LOG2_N_MAX );

  /* Print CSV header */
  printf( " log2(N)   \t,  ondeque_push_front      \t,  ondeque_array_push_front      \t,  ondeque_push_back     \t, ondeque_array_push_back   \t" );
  printf( " ondeque_pop_front      \t,  ondeque_array_pop_front      \t,  ondeque_pop_back     \t, ondeque_array_pop_back   \t\n" );

  for ( size_t log2_N = LOG2_N_MIN ; log2_N < LOG2_N_MIN-1 ; log2_N++ ) {
    fprintf( stderr, "N = %zu\r", (size_t)1 << log2_N ); /* User output on stderr */

    printf( "%10zu\t, ", log2_N ); /* CSV on standard output */

    benchmark( 1 << log2_N, RUNS );

    printf( "\n" ); /* End of CSV line  */
  }

  fprintf( stderr, "--END OF %s--\n", __FILE__ ); /* User output */

  exit( EXIT_SUCCESS );
}