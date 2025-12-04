#define T_TREAP_TAG int_treap
#define treap_datum_t int

#define TREAP_DESTRUCTOR(val) NULL
#define TREAP_COMPARATOR(val1, val2) ((val1) - (val2))
#define TREAP_PRINTER(val) printf("%d", val)
#define TREAP_PRIORITY_FUNC(i) (i)

#include <libellul/type/treap.h>
#include <libellul.h>

void treap_NULL( void ) {
    int_treap_t treap = int_treap_new();

    int_treap_print(treap);

    test_suite( "NULL as a treap" );

    test_assert( int_treap_is_empty( treap ), "NULL is an empty treap" );

    int_treap_delete( treap );
    test_assert( 1, "Can delete NULL as a treap" );

    free(treap);
}

void treap_tests(){
    test_suite("treap push one element");

    int_treap_t treap = int_treap_new();

    int_treap_print(treap);

    int root = 42; int big = 102; int small = 6;
    treap = int_treap_push(treap, root);

    int_treap_print(treap);

    test_assert(!int_treap_is_empty(treap), "treap is not empty after push");
    test_assert(treap->value.value == root, "Root is the expected value");
    test_assert(int_treap_contains(treap, root), "treap contains root");

    test_suite("treap push multiple elements");

    treap = int_treap_push(treap, big);
    treap = int_treap_push(treap, small);

    int_treap_print(treap);

    test_assert(treap->ls->value.value == small, "Left is the expected value");
    test_assert(int_treap_contains(treap, small), "treap contains small");

    test_assert(treap->rs->value.value == big, "Right is the expected value");
    test_assert(int_treap_contains(treap, big), "treap contains big");

    test_suite("treap pop small");

    int res_small; int res_big; int res_mid;
    treap = int_treap_pop_small(treap, &res_small);
    int_treap_print(treap);

    treap = int_treap_pop_small(treap, &res_mid);
    int_treap_print(treap);

    treap = int_treap_pop_small(treap, &res_big);
    int_treap_print(treap);

    test_assert(res_small == small, "Small value is correctly popped");
    test_assert(res_mid == root, "Mid value is correctly popped");
    test_assert(res_big == big, "Big value is correctly popped");

    test_suite("treap pop big");

    treap = int_treap_push(treap, small);
    treap = int_treap_push(treap, root);
    treap = int_treap_push(treap, big);
    int_treap_print(treap);

    treap = int_treap_pop_big(treap, &res_big);
    int_treap_print(treap);

    treap = int_treap_pop_big(treap, &res_mid);
    int_treap_print(treap);

    treap = int_treap_pop_big(treap, &res_small);
    int_treap_print(treap);

    test_assert(res_small == small, "Small value is correctly popped");
    test_assert(res_mid == root, "Mid value is correctly popped");
    test_assert(res_big == big, "Big value is correctly popped");

    test_suite("treap delete");

    treap = int_treap_push(treap, small);
    int_treap_print(treap);

    treap = int_treap_push(treap, big);
    int_treap_print(treap);

    treap = int_treap_push(treap, root);
    int_treap_print(treap);

    treap = int_treap_delete(treap );

    test_assert(int_treap_is_empty(treap), "Deleted treap is empty");

    free(treap);
}

int main(int argc, char *argv[]){
    unit_test(argc, argv);

    test_suite("\n\n\n ================================================ TEST 08-treap.c =========================================================");

    treap_NULL();
    treap_tests();

    exit(EXIT_SUCCESS);
}