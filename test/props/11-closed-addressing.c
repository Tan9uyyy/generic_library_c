#include <libellul.h>

#define T_IMPL_HASHTABLE
/* choix de l'implémentation : soit
* T_IMPL_HASHTABLE_CLOSED_ADDRESSING pour l'implémentation normale 
* T_IMPL_HASHTABLE_CLOSED_ADDRESSING_MOVE_TO_FRONT pour l'implé move_to_front */
#define T_IMPL_HASHTABLE_CLOSED_ADDRESSING
#define T_MAP_TAG int_int_closed_addressing_hashtable
#define T_MAP_KEY int
#define T_MAP_VALUE int

#define HASHTABLE_SIZE 13 
#define HASH(key) (key)
#define VALUE_DESTRUCTOR(val) NULL
#define DESTRUCTOR_IS_NULL // macro flag pour indiquer que le destructeur est NULL (ça me simplifie pour les if parce que sinonje comprends rien)
#define KEY_COMPARATOR(val1, val2) ((val1) == (val2))
#define KEY_PRINTER(val) printf("%d", (val))
#define VALUE_PRINTER(val) printf("%d", (val))

#include <libellul/type/map.h>

static void closed_addressing_NULL(void) {
  int_int_closed_addressing_hashtable_t hashtable = NULL;

  test_suite("NULL as an hashtable");

  test_assert(0 == int_int_closed_addressing_hashtable_length(NULL),
              "NULL is an hashtable of length zero");
  test_assert(int_int_closed_addressing_hashtable_is_empty(NULL),
              "NULL is an the empty hashtable");

  int_int_closed_addressing_hashtable_delete(NULL);
  test_assert(1, "Can delete NULL as an hashtable");

  test_suite("NULL variable as an hashtable");

  test_assert(0 == int_int_closed_addressing_hashtable_length(hashtable),
              "A NULL hashtable has length zero");
  test_assert(int_int_closed_addressing_hashtable_is_empty(hashtable),
              "A NULL hashtable is empty");

  int_int_closed_addressing_hashtable_delete(&hashtable);
  test_assert(NULL == hashtable, "Can delete a NULL hashtable");
}

int *rand_ints(size_t n) {
  int *vec = calloc(n, sizeof(*vec));
  assert(vec);

  for (size_t i = 0; i < n; i++)
    vec[i] = rand() % 50;

  return vec;
}

void int_int_closed_addressing_hashtable_stack(size_t n) {
  int *key = rand_ints(n);
  int *value = rand_ints(n);

  test_suite("Créer une nouvelle hashtable vide");

  int_int_closed_addressing_hashtable_t hashtable = int_int_closed_addressing_hashtable_new();
  int_int_closed_addressing_hashtable_print(hashtable);

  test_assert(int_int_closed_addressing_hashtable_is_empty(hashtable),
              "A new hashtable is empty");

  test_suite("Put des valeurs dans la hashtable");

  for (size_t i = 0; i < n; i++) {
    int_int_closed_addressing_hashtable_put(&hashtable, key[i], value[i]);
    int_int_closed_addressing_hashtable_print(hashtable);
    test_assert(int_int_closed_addressing_hashtable_contains(hashtable, key[i]),
                "Can push to hashtable");
  }

  test_suite("Get des valeurs dans la hashtable");

  for(size_t i = 0; i < 2; i++) {
    int retrieved_value = -1;
    int res = int_int_closed_addressing_hashtable_get(hashtable, key[i], &retrieved_value);
    int_int_couple get_couple = (int_int_couple){.key=key[i], .value=retrieved_value};
    PRINTER(get_couple);
    test_assert(0 == res, "Can get from hashtable");
  }
  printf("\n");
  test_assert( -1 == int_int_closed_addressing_hashtable_get(hashtable, -999, NULL),
               "Getting a non-existing key returns -1");

  test_suite("Pop des valeurs de la hashtable");

  for (size_t i = 0; (!int_int_closed_addressing_hashtable_is_empty(hashtable)) || (i < n); i++) {
    int_int_closed_addressing_hashtable_remove(&hashtable, key[i]);
    int_int_closed_addressing_hashtable_print(hashtable);
    test_assert(0 == int_int_closed_addressing_hashtable_contains(hashtable, key[i]), "Can pop from hashtable");
  }

  test_suite("Une hashtable complètement popée est vide");

  test_assert(int_int_closed_addressing_hashtable_is_empty(hashtable),
              "Empty, non-NULL hashtable at the end");


  test_suite("Suppression de la hashtable");

  int_int_closed_addressing_hashtable_delete(&hashtable);
  int_int_closed_addressing_hashtable_print(hashtable);
  test_assert(NULL == hashtable, "hashtable is NULL after delete");

  free(key);
  free(value);
}

int main(int argc, char *argv[]) {

  unit_test(argc, argv);

  test_suite("\n\n\n ================================================ TEST "
             "11-closed-addressing.c "
             "=========================================================");

  closed_addressing_NULL();
  int_int_closed_addressing_hashtable_stack(2 /* on met juste à deux pour gagner de la place sur le terminal */);

  exit(EXIT_SUCCESS);
}

#undef T_IMPL_HASHTABLE
#undef T_IMPL_HASHTABLE_CLOSED_ADDRESSING
#undef T_MAP_TAG
#undef T_MAP_KEY
#undef T_MAP_VALUE