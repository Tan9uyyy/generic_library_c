#include <libellul.h>

#define T_SET_ELEMENT int
#define T_SET_TAG int_set
#define T_IMPL_HASHTABLE
#define T_IMPL_HASHTABLE_CLOSED_ADDRESSING

#define HASHTABLE_SIZE 13
#define HASH(key) (key)
#define VALUE_DESTRUCTOR(val) NULL
#define DESTRUCTOR_IS_NULL
#define KEY_COMPARATOR(val1, val2) ((val1) == (val2))
#define KEY_PRINTER(val) printf("%d", (val))
#define VALUE_PRINTER(val) printf("%d", (val))

#include <libellul/type/set.h>

void test_set_operations(void) {
  test_suite("Set operations");

  int_set_t set1 = int_set_new();
  int_set_t set2 = int_set_new();

  int_set_insert(&set1, 1);
  int_set_insert(&set1, 2);
  int_set_insert(&set1, 3);

  int_set_insert(&set2, 3);
  int_set_insert(&set2, 4);
  int_set_insert(&set2, 5);

  test_assert(int_set_contains(set1, 1), "Set1 contains 1");
  test_assert(int_set_contains(set1, 2), "Set1 contains 2");
  test_assert(int_set_contains(set1, 3), "Set1 contains 3");
  test_assert(!int_set_contains(set1, 4), "Set1 does not contain 4");

  test_assert(int_set_contains(set2, 3), "Set2 contains 3");
  test_assert(int_set_contains(set2, 4), "Set2 contains 4");
  test_assert(int_set_contains(set2, 5), "Set2 contains 5");
  test_assert(!int_set_contains(set2, 1), "Set2 does not contain 1");

  /* Test Union: {1, 2, 3, 4, 5} */
  int_set_t set_union = int_set_union(set1, set2);
  test_assert(int_set_length(set_union) == 5, "Union length is 5");
  test_assert(int_set_contains(set_union, 1), "Union contains 1");
  test_assert(int_set_contains(set_union, 2), "Union contains 2");
  test_assert(int_set_contains(set_union, 3), "Union contains 3");
  test_assert(int_set_contains(set_union, 4), "Union contains 4");
  test_assert(int_set_contains(set_union, 5), "Union contains 5");

  /* Test Intersection: {3} */
  int_set_t set_inter = int_set_inter(set1, set2);
  test_assert(int_set_length(set_inter) == 1, "Intersection length is 1");
  test_assert(int_set_contains(set_inter, 3), "Intersection contains 3");
  test_assert(!int_set_contains(set_inter, 1),
              "Intersection does not contain 1");
  test_assert(!int_set_contains(set_inter, 4),
              "Intersection does not contain 4");

  /* Test Difference (set1 - set2): {1, 2} */
  int_set_t set_diff = int_set_diff(set1, set2);
  test_assert(int_set_length(set_diff) == 2, "Difference length is 2");
  test_assert(int_set_contains(set_diff, 1), "Difference contains 1");
  test_assert(int_set_contains(set_diff, 2), "Difference contains 2");
  test_assert(!int_set_contains(set_diff, 3), "Difference does not contain 3");

  /* Test Symmetric Difference: {1, 2, 4, 5} */
  int_set_t set_symdiff = int_set_symdiff(set1, set2);
  test_assert(int_set_length(set_symdiff) == 4, "SymDiff length is 4");
  test_assert(int_set_contains(set_symdiff, 1), "SymDiff contains 1");
  test_assert(int_set_contains(set_symdiff, 2), "SymDiff contains 2");
  test_assert(int_set_contains(set_symdiff, 4), "SymDiff contains 4");
  test_assert(int_set_contains(set_symdiff, 5), "SymDiff contains 5");
  test_assert(!int_set_contains(set_symdiff, 3), "SymDiff does not contain 3");

  /* Test Compare */
  test_assert(int_set_compare(&set1, &set1) == 0,
              "Self compare returns 0 (equal)");
  test_assert(int_set_compare(&set1, &set2) != 0,
              "Different sets compare returns non-0");

  int_set_t set3 = int_set_new();
  int_set_insert(&set3, 1);
  int_set_insert(&set3, 2);
  int_set_insert(&set3, 3);
  test_assert(int_set_compare(&set1, &set3) == 0,
              "Equal sets compare returns 0");

  int_set_delete(&set1);
  int_set_delete(&set2);
  int_set_delete(&set3);
  int_set_delete(&set_union);
  int_set_delete(&set_inter);
  int_set_delete(&set_diff);
  int_set_delete(&set_symdiff);
}

int main(int argc, char *argv[]) {
  unit_test(argc, argv);
  test_set_operations();
  exit(EXIT_SUCCESS);
}
