#include "benchmark.h"

#include <stdio.h>
#include <stdlib.h>

#define T_TREESET
#define T_TREESET_TAG size_t_treeset
#define treeset_datum_t size_t
#define T size_t_treeset_t

#define TREESET_DESTRUCTOR(val) NULL
#define TREESET_COMPARATOR(val1, val2) ((int)(val1) - (int)(val2))
#define TREESET_PRINTER(val) printf("%d", (int)(val))
#define TREESET_PRIORITY_FUNC(val) (rand())

#include <libellul.h>
#include <libellul/type/treeset.h>

static int ontreeset_put(size_t N) {
  size_t_treeset_t set = size_t_treeset_new();
  int sum = 0;

  for (size_t i = 0; i < N; i++) {
    set = size_t_treeset_add(set, i); // treeset uses push?
    // treeset.h: #define TREESET_METHOD( name ) GEN_SYM( T_TREESET_TAG, name )
    // treeset-implementation.h: T TREESET_METHOD(push) (T treap, treap_datum_t
    // value) So size_t_treeset_push.
    sum += i;
  }

  size_t_treeset_delete(set);

  return sum;
}

static int ontreeset_contains(size_t N) {
  size_t_treeset_t set = size_t_treeset_new();
  int sum = 0;

  for (size_t i = 0; i < N; i++) {
    set = size_t_treeset_add(set, i);
  }

  elapsed_nsec();

  for (size_t i = 0; i < N; i++) {
    sum += size_t_treeset_contains(set, i);
  }

  size_t_treeset_delete(set);

  return sum;
}

#undef T_TREESET_TAG
#undef treeset_datum_t
#undef T

#define T_IMPL_HASHTABLE
#define T_IMPL_HASHTABLE_CLOSED_ADDRESSING
#define T_MAP_TAG size_t_size_t_hashtable
#define T_MAP_KEY size_t
#define T_MAP_VALUE size_t

#define HASHTABLE_SIZE 1009 // Prime number
#define HASH(key) (key)
#define VALUE_DESTRUCTOR(val) NULL
#define DESTRUCTOR_IS_NULL
#define KEY_COMPARATOR(val1, val2) ((val1) == (val2))
#define KEY_PRINTER(val) printf("%d", (int)(val))
#define VALUE_PRINTER(val) printf("%d", (int)(val))

#include <libellul/type/map.h>

static int onhashtable_put(size_t N) {
  size_t_size_t_hashtable_t map = size_t_size_t_hashtable_new();
  int sum = 0;

  for (size_t i = 0; i < N; i++) {
    size_t_size_t_hashtable_put(&map, i, i);
    sum += i;
  }

  size_t_size_t_hashtable_delete(&map);

  return sum;
}

static int onhashtable_contains(size_t N) {
  size_t_size_t_hashtable_t map = size_t_size_t_hashtable_new();
  int sum = 0;

  for (size_t i = 0; i < N; i++) {
    size_t_size_t_hashtable_put(&map, i, i);
  }

  elapsed_nsec();

  for (size_t i = 0; i < N; i++) {
    sum += size_t_size_t_hashtable_contains(map, i);
  }

  size_t_size_t_hashtable_delete(&map);

  return sum;
}

static void benchmark(size_t N, int runs) {
  int s1, s2;
  int p1, p2;

  for (int run = 0; run < runs; run++)
    s1 = run + ontreeset_put(N);

  printf("%10.2g\t,", elapsed_nsec() / (runs * N));

  elapsed_nsec();

  for (int run = 0; run < runs; run++)
    s2 = run + onhashtable_put(N);

  printf("%10.2g\t,", elapsed_nsec() / (runs * N));

  elapsed_nsec();

  for (int run = 0; run < runs; run++)
    p1 = run + ontreeset_contains(N);

  printf("%10.2g\t,", elapsed_nsec() / (runs * N));

  elapsed_nsec();

  for (int run = 0; run < runs; run++)
    p2 = run + onhashtable_contains(N);

  printf("%10.2g\t,", elapsed_nsec() / (runs * N));

  if (!s1 || !s2)
    abort();
  if (!p1 || !p2)
    abort();
}

int main() {

  fprintf(stderr, "%g\r", elapsed_nsec());
  onhashtable_put(LOG2_N_MAX);

  printf(" log2(N)   \t,  ontreeset_put      \t,  onhashtable_put      \t,  "
         "ontreeset_contains     \t, onhashtable_contains   \t\n");

  for (size_t log2_N = LOG2_N_MIN; log2_N < LOG2_N_MAX + 1; log2_N++) {
    fprintf(stderr, "N = %zu\r", (size_t)1 << log2_N);

    printf("%10zu\t, ", log2_N);

    benchmark(1 << log2_N, RUNS);

    printf("\n");
  }

  fprintf(stderr, "--END OF %s--\n", __FILE__);

  exit(EXIT_SUCCESS);
}
