#include "benchmark.h"

#include <stdio.h>

#define T_PQ
#define T_PQ_TAG size_t_pq
#define pq_datum_t size_t
#define T size_t_pq_t

#include <libellul.h>
#define PQ_DESTRUCTOR(val) NULL
#define PQ_PRINTER(val) printf("%zu", val)
#include <libellul/type/priority-queue.h>
#undef T_INTERFACE

static int onpq_push(size_t N) {
  size_t_pq_t pq = size_t_pq_new();
  int sum = 0;

  for (size_t i = 0; i < N; i++) {
    pq = size_t_pq_push(i, (int)i, pq);
    sum += i;
  }

  size_t_pq_delete(pq);

  return sum;
}

static int onpq_pop(size_t N) {
  size_t_pq_t pq = size_t_pq_new();
  int sum = 0;
  size_t storage;

  for (size_t i = 0; i < N; i++) {
    pq = size_t_pq_push(i, (int)i, pq);
  }

  elapsed_nsec();

  for (size_t i = 0; i < N; i++) {
    pq = size_t_pq_pop(&storage, pq);
    sum += i;
  }

  size_t_pq_delete(pq);

  return sum;
}

#undef T_PQ_TAG
#undef pq_datum_t
#undef T

#define T_HEAP
#define T_HEAP_TAG pq_couple_heap
#define heap_datum_t pq_couple
#define T pq_couple_heap_t

#define HEAP_DESTRUCTOR(val) NULL
#define HEAP_COMPARATOR(val1, val2) ((val1).priority - (val2).priority)
#define HEAP_PRINTER(val) printf("(%d, %d)", (val).priority, (int)(val).value)

#include <libellul/type/heap.h>

static int onheap_push(size_t N) {
  pq_couple_heap_t heap = pq_couple_heap_new();
  int sum = 0;

  for (size_t i = 0; i < N; i++) {
    pq_couple c = {.value = i, .priority = (int)i};
    pq_couple_heap_push(&heap, c);
    sum += i;
  }

  pq_couple_heap_delete(heap);

  return sum;
}

static int onheap_pop(size_t N) {
  pq_couple_heap_t heap = pq_couple_heap_new();
  int sum = 0;
  pq_couple storage;

  for (size_t i = 0; i < N; i++) {
    pq_couple c = {.value = i, .priority = (int)i};
    pq_couple_heap_push(&heap, c);
  }

  elapsed_nsec();

  for (size_t i = 0; i < N; i++) {
    pq_couple_heap_pop(&heap, &storage);
    sum += i;
  }

  pq_couple_heap_delete(heap);

  return sum;
}

static void benchmark(size_t N, int runs) {
  int s1, s2;
  int p1, p2;

  for (int run = 0; run < runs; run++)
    s1 = run + onpq_push(N);

  printf("%10.2g\t,", elapsed_nsec() / (runs * N));

  elapsed_nsec();

  for (int run = 0; run < runs; run++)
    s2 = run + onheap_push(N);

  printf("%10.2g\t,", elapsed_nsec() / (runs * N));

  elapsed_nsec();

  for (int run = 0; run < runs; run++)
    p1 = run + onpq_pop(N);

  printf("%10.2g\t,", elapsed_nsec() / (runs * N));

  elapsed_nsec();

  for (int run = 0; run < runs; run++)
    p2 = run + onheap_pop(N);

  printf("%10.2g\t,", elapsed_nsec() / (runs * N));

  if (!s1 || !s2)
    abort();
  if (!p1 || !p2)
    abort();
}

int main() {

  fprintf(stderr, "%g\r", elapsed_nsec());
  onheap_push(LOG2_N_MAX);

  printf(" log2(N)   \t,  onpq_push      \t,  onheap_push      \t,  onpq_pop   "
         "  \t, onheap_pop   \t\n");

  for (size_t log2_N = LOG2_N_MIN; log2_N < LOG2_N_MAX + 1; log2_N++) {
    fprintf(stderr, "N = %zu\r", (size_t)1 << log2_N);

    printf("%10zu\t, ", log2_N);

    benchmark(1 << log2_N, RUNS);

    printf("\n");
  }

  fprintf(stderr, "--END OF %s--\n", __FILE__);

  exit(EXIT_SUCCESS);
}
