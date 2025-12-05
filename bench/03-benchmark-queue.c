#include "benchmark.h"

#include <stdio.h>

#define T_QUEUE
#define T_QUEUE_TAG size_t_queue
#define queue_datum_t size_t
#define T size_t_queue_t

#define DESTRUCTOR(val) NULL
#define DESTRUCTOR_IS_NULL
#define COMPARATOR(val1, val2) ((val1) == (val2))
#define PRINTER(val) printf("%d", (int)(val))

#include <libellul.h>
#include <libellul/type/queue.h>

static int onqueue_push(size_t N) {
  size_t_queue_t queue = size_t_queue_new();
  int sum = 0;

  for (size_t i = 0; i < N; i++) {
    queue = size_t_queue_push(i, queue);
    sum += i;
  }

  size_t_queue_delete(queue);

  return sum;
}

static int onqueue_pop(size_t N) {
  size_t_queue_t queue = size_t_queue_new();
  int sum = 0;
  size_t storage;

  for (size_t i = 0; i < N; i++) {
    queue = size_t_queue_push(i, queue);
  }

  elapsed_nsec();

  for (size_t i = 0; i < N; i++) {
    queue = size_t_queue_pop(&storage, queue);
    sum += i;
  }

  size_t_queue_delete(queue);

  return sum;
}

#undef T_QUEUE_TAG
#undef queue_datum_t
#undef T
#undef T_DEQUE_TAG
#undef deque_datum_t

/* Use Deque Array implementation as a proxy for Queue Array */
#define T_DEQUE
#define T_DEQUE_TAG size_t_deque_array
#define deque_datum_t size_t
#define T size_t_deque_array_t
#define T_DEQUE_IMPL_ARRAY
#include <libellul/type/deque.h>

static int onqueue_array_push(size_t N) {
  size_t_deque_array_t deque = size_t_deque_array_new();
  int sum = 0;

  for (size_t i = 0; i < N; i++) {
    deque = size_t_deque_array_push_back(i, deque);
    sum += i;
  }

  size_t_deque_array_delete(deque);

  return sum;
}

static int onqueue_array_pop(size_t N) {
  size_t_deque_array_t deque = size_t_deque_array_new();
  int sum = 0;
  size_t storage;

  for (size_t i = 0; i < N; i++) {
    deque = size_t_deque_array_push_back(i, deque);
  }

  elapsed_nsec();

  for (size_t i = 0; i < N; i++) {
    deque = size_t_deque_array_pop_front(&storage, deque);
    sum += i;
  }

  size_t_deque_array_delete(deque);

  return sum;
}

static void benchmark(size_t N, int runs) {
  int s1, s2;
  int p1, p2;

  for (int run = 0; run < runs; run++)
    s1 = run + onqueue_push(N);

  printf("%10.2g\t,", elapsed_nsec() / (runs * N));

  elapsed_nsec();

  for (int run = 0; run < runs; run++)
    s2 = run + onqueue_array_push(N);

  printf("%10.2g\t,", elapsed_nsec() / (runs * N));

  elapsed_nsec();

  for (int run = 0; run < runs; run++)
    p1 = run + onqueue_pop(N);

  printf("%10.2g\t,", elapsed_nsec() / (runs * N));

  elapsed_nsec();

  for (int run = 0; run < runs; run++)
    p2 = run + onqueue_array_pop(N);

  printf("%10.2g\t,", elapsed_nsec() / (runs * N));

  if (!s1 || !s2)
    abort();
  if (!p1 || !p2)
    abort();
}

int main() {

  fprintf(stderr, "%g\r", elapsed_nsec());
  onqueue_array_push(LOG2_N_MAX);

  printf(" log2(N)   \t,  onqueue_push      \t,  onqueue_array_push      \t,  "
         "onqueue_pop     \t, onqueue_array_pop   \t\n");

  for (size_t log2_N = LOG2_N_MIN; log2_N < LOG2_N_MAX + 1; log2_N++) {
    // In 01-benchmark-deque.c: for ( size_t log2_N = LOG2_N_MIN ; log2_N <
    // LOG2_N_MIN-1 ; log2_N++ ) That looks wrong. It should be LOG2_N_MAX. Let
    // me check 01-benchmark-deque.c again. Line 247: for ( size_t log2_N =
    // LOG2_N_MIN ; log2_N < LOG2_N_MIN-1 ; log2_N++ ) That loop will never run
    // if MIN is 1. Ah, wait. 01-benchmark-deque.c content I read: 247:   for (
    // looks like a bug in the existing file or I misread it? Let's check
    // 02-benchmark-hashtable.c 97:   for ( size_t log2_N = LOG2_N_MIN ; log2_N
    // < LOG2_N_MAX+1 ; log2_N++ ) { This looks correct. I will use
    // LOG2_N_MAX+1.

    fprintf(stderr, "N = %zu\r", (size_t)1 << log2_N);

    printf("%10zu\t, ", log2_N);

    benchmark(1 << log2_N, RUNS);

    printf("\n");
  }

  fprintf(stderr, "--END OF %s--\n", __FILE__);

  exit(EXIT_SUCCESS);
}
