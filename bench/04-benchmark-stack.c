#include "benchmark.h"

#include <stdio.h>

#define T_STACK
#define T_STACK_TAG size_t_stack
#define stack_datum_t size_t
#define T size_t_stack_t

#define DESTRUCTOR(val) NULL
#define DESTRUCTOR_IS_NULL
#define COMPARATOR(val1, val2) ((val1) == (val2))
#define PRINTER(val) printf("%d", (int)(val))

#include <libellul.h>
#include <libellul/type/stack.h>

static int onstack_push(size_t N) {
  size_t_stack_t stack = size_t_stack_new();
  int sum = 0;

  for (size_t i = 0; i < N; i++) {
    stack = size_t_stack_push(i, stack);
    sum += i;
  }

  size_t_stack_delete(stack);

  return sum;
}

static int onstack_pop(size_t N) {
  size_t_stack_t stack = size_t_stack_new();
  int sum = 0;
  size_t storage;

  for (size_t i = 0; i < N; i++) {
    stack = size_t_stack_push(i, stack);
  }

  elapsed_nsec();

  for (size_t i = 0; i < N; i++) {
    stack = size_t_stack_pop(&storage, stack);
    sum += i;
  }

  size_t_stack_delete(stack);

  return sum;
}

#undef T_STACK_TAG
#undef stack_datum_t
#undef T
#undef T_DEQUE_TAG
#undef deque_datum_t

/* Use Deque Array implementation as a proxy for Stack Array */
#define T_DEQUE
#define T_DEQUE_TAG size_t_deque_array
#define deque_datum_t size_t
#define T size_t_deque_array_t
#define T_DEQUE_IMPL_ARRAY
#include <libellul/type/deque.h>

static int onstack_array_push(size_t N) {
  size_t_deque_array_t deque = size_t_deque_array_new();
  int sum = 0;

  for (size_t i = 0; i < N; i++) {
    deque = size_t_deque_array_push_back(i, deque);
    sum += i;
  }

  size_t_deque_array_delete(deque);

  return sum;
}

static int onstack_array_pop(size_t N) {
  size_t_deque_array_t deque = size_t_deque_array_new();
  int sum = 0;
  size_t storage;

  for (size_t i = 0; i < N; i++) {
    deque = size_t_deque_array_push_back(i, deque);
  }

  elapsed_nsec();

  for (size_t i = 0; i < N; i++) {
    deque = size_t_deque_array_pop_back(&storage, deque);
    sum += i;
  }

  size_t_deque_array_delete(deque);

  return sum;
}

static void benchmark(size_t N, int runs) {
  int s1, s2;
  int p1, p2;

  for (int run = 0; run < runs; run++)
    s1 = run + onstack_push(N);

  printf("%10.2g\t,", elapsed_nsec() / (runs * N));

  elapsed_nsec();

  for (int run = 0; run < runs; run++)
    s2 = run + onstack_array_push(N);

  printf("%10.2g\t,", elapsed_nsec() / (runs * N));

  elapsed_nsec();

  for (int run = 0; run < runs; run++)
    p1 = run + onstack_pop(N);

  printf("%10.2g\t,", elapsed_nsec() / (runs * N));

  elapsed_nsec();

  for (int run = 0; run < runs; run++)
    p2 = run + onstack_array_pop(N);

  printf("%10.2g\t,", elapsed_nsec() / (runs * N));

  if (!s1 || !s2)
    abort();
  if (!p1 || !p2)
    abort();
}

int main() {

  fprintf(stderr, "%g\r", elapsed_nsec());
  onstack_array_push(LOG2_N_MAX);

  printf(" log2(N)   \t,  onstack_push      \t,  onstack_array_push      \t,  "
         "onstack_pop     \t, onstack_array_pop   \t\n");

  for (size_t log2_N = LOG2_N_MIN; log2_N < LOG2_N_MAX + 1; log2_N++) {
    fprintf(stderr, "N = %zu\r", (size_t)1 << log2_N);

    printf("%10zu\t, ", log2_N);

    benchmark(1 << log2_N, RUNS);

    printf("\n");
  }

  fprintf(stderr, "--END OF %s--\n", __FILE__);

  exit(EXIT_SUCCESS);
}
