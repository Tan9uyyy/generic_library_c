#define T_LIST_TAG int_list
#define list_datum_t int

#define DESTRUCTOR(val) NULL
#define DESTRUCTOR_IS_NULL // macro flag pour indiquer que le destructeur est
                           // NULL (ça me simplifie pour les if parce que sinon
                           // je comprends rien)
#define COMPARATOR(val1, val2) ((val1) == (val2))
#define PRINTER(val) printf("%d", (val))

#include <libellul.h>
#include <libellul/type/list.h>

void list_NULL(void) {
  test_suite("NULL as a list");

  int_list_t list = int_list_new();

  test_assert(int_list_is_empty(list), "NULL is an empty list");
  test_assert(int_list_length(list) == 0, "NULL length is 0");

  int_list_print(list);

  int_list_delete(list);
  test_assert(1, "Can delete NULL as a list");
}

void list_test(void) {
  int_list_t list = int_list_new();
  int input = 42;
  int output = 0;

  int inputs[7] = {1, 2, 3, -1, -2, 0, 87};
  int outputs[7] = {0, 0, 0, 0, 0, 0, 0};

  test_suite("list push one element");

  list = int_list_push(input, list);

  int_list_print(list);

  test_assert(!int_list_is_empty(list), "list is not empty after push");
  test_assert(int_list_length(list) == 1, "list length is 1");

  test_assert(int_list_get(list, 0) == input, "Correct push");

  test_suite("list pop one element");

  list = int_list_pop(&output, list);

  int_list_print(list);

  test_assert(output == input, "Correct pop");

  test_assert(int_list_is_empty(list), "list is empty after fully popped");

  test_suite("list push multiple elements");

  for (int i = 0; i < 7; i++) {
    list = int_list_push(inputs[i], list);
    int_list_print(list);

    test_assert(int_list_get(list, i) == inputs[i],
                "i-eme value is the i-eme value pushed");
  }

  test_assert(int_list_length(list) == 7, "list length is 7");

  test_suite("list pop multiple elements");

  for (int i = 0; i < 7; i++) {
    list = int_list_pop(&outputs[i], list);
    int_list_print(list);

    test_assert(outputs[i] == inputs[6 - i], "Popped value is correct");
  }

  test_assert(int_list_is_empty(list), "list is empty after fully popped");

  test_suite("list contains");

  list = int_list_push(0, list);
  int_list_print(list);

  test_assert(int_list_contains(list, 0) >= 0, "list contient 0.");
  test_assert(int_list_contains(list, 1) < 0, "list ne contient pas 1.");

  test_suite("list remove");

  list = int_list_push(2, list);
  list = int_list_push(3, list);

  int_list_print(list);
  test_assert(int_list_remove(1, list),
              "supprime 1 qui n'existe pas dans la liste (ne fait rien).");
  int_list_print(list);
  test_assert(int_list_remove(2, list), "supprime 2.");
  int_list_print(list);
  test_assert(int_list_remove(3, list), "supprime 3.");
  int_list_print(list);
  test_assert(int_list_remove(0, list), "supprime 0.");
  int_list_print(list);
  test_assert(int_list_is_empty(list), "list est vide après suppressions.");

  test_suite("list delete");

  for (int i = 0; i < 7; i++) {
    list = int_list_push(inputs[i], list);
  }

  int_list_print(list);

  list = int_list_delete(list);

  test_assert(int_list_is_empty(list), "list is empty after deleted");
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