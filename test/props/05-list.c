#define T_LIST_TAG list_int
#define list_datum_t int

#define DESTRUCTOR(val) NULL
#define COMPARATOR(val1, val2) ((val1) == (val2))
#define PRINTER(val) printf("%d", (val))

#include <libellul/type/list.h>
#include <libellul.h>

void list_NULL(void) {
  test_suite("NULL as a list");

  list_int_t list = list_int_new();

  test_assert(list_int_is_empty(list), "NULL is an empty list");
  test_assert(list_int_length(list) == 0, "NULL length is 0");

  list_int_print(list);

  list_int_delete(list);
  test_assert(1, "Can delete NULL as a list");

  free(list);
}

void list_test(void) {
  list_int_t list = list_int_new();
  int input = 42;
  int output = 0;

  int inputs[7] = {1, 2, 3, -1, -2, 0, 87};
  int outputs[7] = {0, 0, 0, 0, 0, 0, 0};

  test_suite("list push one element");

  list = list_int_push(input, list);

  list_int_print(list);

  test_assert(!list_int_is_empty(list), "list is not empty after push");
  test_assert(list_int_length(list) == 1, "list length is 1");

  test_assert(list_int_get(list, 0) == input, "Correct push");

  test_suite("list pop one element");

  list = list_int_pop(&output, list);

  list_int_print(list);

  test_assert(output == input, "Correct pop");

  test_assert(list_int_is_empty(list), "list is empty after fully popped");

  test_suite("list push multiple elements");

  for (int i = 0; i < 7; i++) {
    list = list_int_push(inputs[i], list);
    list_int_print(list);

    test_assert(list_int_get(list, i) == inputs[i],
                "i-eme value is the i-eme value pushed");
  }

  test_assert(list_int_length(list) == 7, "list length is 7");

  test_suite("list pop multiple elements");

  for (int i = 0; i < 7; i++) {
    list = list_int_pop(&outputs[i], list);
    list_int_print(list);

    test_assert(outputs[i] == inputs[6 - i], "Popped value is correct");
  }

  test_assert(list_int_is_empty(list), "list is empty after fully popped");

  test_suite("list contains");

  list = list_int_push(0, list);
  list_int_print(list);

  test_assert(list_int_contains(list, 0), "list contient 0.");
  test_assert(!list_int_contains(list, 1), "list ne contient pas 1.");

  test_suite("list remove");

  list = list_int_push(2, list);
  list = list_int_push(3, list);
  
  list_int_print(list);
  test_assert(list_int_remove(1, list), "supprime 1 qui n'existe pas dans la liste (ne fait rien).");
  list_int_print(list);
  test_assert(list_int_remove(2, list), "supprime 2.");
  list_int_print(list);
  test_assert(list_int_remove(3, list), "supprime 3.");
  list_int_print(list);
  test_assert(list_int_remove(0, list), "supprime 0.");
  list_int_print(list);
  test_assert(list_int_is_empty(list), "list est vide après suppressions.");

  test_suite("list delete");

  for (int i = 0; i < 7; i++) {
    list = list_int_push(inputs[i], list);
  }

  list_int_print(list);

  list = list_int_delete(list);

  test_assert(list_int_is_empty(list), "list is empty after deleted");

  free(list);
}

int main(int argc, char *argv[]) {
  unit_test(argc, argv);

  test_suite(
      "\n\n\n ================================================ TEST 05-list.c "
      "=========================================================");

  list_NULL();
  list_test();

  exit(EXIT_SUCCESS);
}