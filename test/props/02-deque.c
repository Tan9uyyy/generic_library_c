#define T_DEQUE
#define T_DEQUE_TAG int_deque
#define deque_datum_t int
#define T int_deque_t

#define DESTRUCTOR(val) NULL
#define DESTRUCTOR_IS_NULL //macro flag pour indiquer que le destructeur est NULL (ça me simplifie pour les if parce que sinon je comprends rien)
#define COMPARATOR(val1, val2) ((val1) == (val2))
#define PRINTER(val) printf("%d", (val))

#include <libellul/type/deque.h>
#include <libellul.h>

void deque_NULL(void) {
  int_deque_t deque = int_deque_new();

  int_deque_print(deque);

  test_suite("NULL as a deque");

  test_assert(int_deque_is_empty(deque), "NULL is an empty deque");
  test_assert(int_deque_length(deque) == 0, "NULL length is 0");

  int_deque_delete(deque);
  test_assert(1, "Can delete NULL as a deque");

  free(deque);
}

void deque_tests(void) {
  int_deque_t deque = int_deque_new();

  test_suite("Push front in deque");

  int *values = calloc(7, sizeof(values));
  values[0] = 42;
  values[1] = 1;
  values[2] = 2;
  values[3] = 3;
  values[4] = -39;
  values[5] = -1;
  values[6] = -2;

  deque = int_deque_push_front(values[0], deque);

  int_deque_print(deque);

  test_assert(!int_deque_is_empty(deque), "Deque is not empty");
  test_assert(int_deque_length(deque) == 1, "Deque length is 1");
  test_assert(values[0] == int_deque_first(deque), "Deque head is correct");

  for (int i = 1; i < 4; i++)
    deque = int_deque_push_front(values[i], deque);
  int_deque_print(deque);

  test_assert(!int_deque_is_empty(deque), "Push front multiple values");
  test_assert(int_deque_length(deque) == 4, "Deque length is 4");

  test_suite("Push back in deque");

  deque = int_deque_push_back(values[4], deque);
  int_deque_print(deque);

  test_assert(!int_deque_is_empty(deque), "Deque is still not empty");
  test_assert(int_deque_length(deque) == 5, "Deque length is 5");
  test_assert(values[4] == int_deque_last(deque), "Deque queue is correct");

  for (int i = 5; i < 7; i++)
    deque = int_deque_push_back(values[i], deque);
  int_deque_print(deque);

  test_assert(!int_deque_is_empty(deque), "Push back multiple values");
  test_assert(int_deque_length(deque) == 7, "Deque length is 7");

  test_suite("Rotate the deque");

  int_deque_print(deque);
  int_deque_rotate(1, deque);
  int_deque_print(deque);
  int_deque_rotate(-1, deque);
  int_deque_print(deque);

  test_suite("Pop front in deque");

  int value = 0;
  while (!int_deque_is_empty(deque)) {
    deque = int_deque_pop_front(&value, deque);
    int_deque_print(deque);
    test_assert(value, "Pop front is correct");
  }

  test_suite("Pop back in deque");

  deque = int_deque_push_front(values[0], deque);
  deque = int_deque_push_front(values[1], deque);
  deque = int_deque_push_front(values[2], deque);
  deque = int_deque_push_front(values[3], deque);
  deque = int_deque_push_front(values[4], deque);
  deque = int_deque_push_front(values[5], deque);
  deque = int_deque_push_front(values[6], deque);
  int_deque_print(deque);

  while (!int_deque_is_empty(deque)) {
    deque = int_deque_pop_back(&value, deque);
    int_deque_print(deque);
    test_assert(value, "Pop back is correct");
  }

  test_assert(int_deque_is_empty(deque), "Deque is empty after fully poped");

  test_suite("Deque contains");

  deque = int_deque_push_front(0, deque);
  int_deque_print(deque);

  test_assert(int_deque_contains(deque, 0), "Deque contient 0.");
  test_assert(!int_deque_contains(deque, 1), "Deque ne contient pas 1.");

  test_suite("Deque remove");

  deque = int_deque_push_front(2, deque);
  deque = int_deque_push_front(3, deque);
  int_deque_print(deque);

  test_assert(int_deque_remove(1, deque), "supprime 1 qui n'existe pas dans la liste (ne fait rien).");
  int_deque_print(deque);
  test_assert(int_deque_remove(2, deque), "supprime 2.");
  int_deque_print(deque);
  test_assert(int_deque_remove(3, deque), "supprime 3.");
  int_deque_print(deque);
  test_assert(int_deque_remove(0, deque), "supprime 0.");
  int_deque_print(deque);
  test_assert(int_deque_is_empty(deque), "Deque est vide après suppressions.");

  test_suite("Deque delete");

  deque = int_deque_push_back(values[0], deque);
  deque = int_deque_push_back(values[1], deque);
  deque = int_deque_push_back(values[2], deque);
  deque = int_deque_push_back(values[3], deque);
  deque = int_deque_push_front(values[4], deque);
  deque = int_deque_push_front(values[5], deque);
  deque = int_deque_push_front(values[6], deque);

  int_deque_print(deque);

  deque = int_deque_delete(deque);

  int_deque_print(deque);
  test_assert(int_deque_is_empty(deque), "Deque is empty after delete");

  free(values);
  free(deque);
}

int main(int argc, char *argv[]) {
  unit_test(argc, argv);

  test_suite(
      "\n\n\n ================================================ TEST 02-deque.c "
      "=========================================================");

  deque_NULL();
  deque_tests();

  exit(EXIT_SUCCESS);
}