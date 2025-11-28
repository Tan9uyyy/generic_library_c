#include <libellul/type/treap.h>

#define treap_datum_t int
#include <libellul/type/treap/treap-implementation.h>

#include <libellul.h>

void printer(int value){printf("%d", value);}

int comparator(int v1, int v2){return v1 - v2;}

int priority_func(int i){return i;}

void treap_NULL( void ) {
    treap_int_t treap = treap_int_new();

    treap_int_print(treap, printer); printf("\n");

    test_suite( "NULL as a treap" );

    test_assert( treap_int_is_empty( treap ), "NULL is an empty treap" );

    treap_int_delete( treap, NULL );
    test_assert( 1, "Can delete NULL as a treap" );

    free(treap);
}

void treap_tests(){
    test_suite("treap push one element");

    treap_int_t treap = treap_int_new();

    treap_int_print(treap, printer); printf("\n");

    int root = 42; int big = 102; int small = 6;
    treap = treap_int_push(treap, root, comparator, priority_func);

    treap_int_print(treap, printer); printf("\n");

    test_assert(!treap_int_is_empty(treap), "treap is not empty after push");
    test_assert(treap->value == root, "Root is the expected value");
    test_assert(treap_int_contains(treap, root, comparator), "treap contains root");

    test_suite("treap push multiple elements");

    treap = treap_int_push(treap, big, comparator, priority_func);
    treap = treap_int_push(treap, small, comparator, priority_func);

    treap_int_print(treap, printer); printf("\n");

    test_assert(treap->ls->value == small, "Left is the expected value");
    test_assert(treap_int_contains(treap, small, comparator), "treap contains small");

    test_assert(treap->rs->value == big, "Right is the expected value");
    test_assert(treap_int_contains(treap, big, comparator), "treap contains big");

    test_suite("treap pop small");

    int res_small; int res_big; int res_mid;
    treap = treap_int_pop_small(treap, &res_small);
    treap_int_print(treap, printer); printf("\n");

    treap = treap_int_pop_small(treap, &res_mid);
    treap_int_print(treap, printer); printf("\n");

    treap = treap_int_pop_small(treap, &res_big);
    treap_int_print(treap, printer); printf("\n");

    test_assert(res_small == small, "Small value is correctly popped");
    test_assert(res_mid == root, "Mid value is correctly popped");
    test_assert(res_big == big, "Big value is correctly popped");

    test_suite("treap pop big");

    treap = treap_int_push(treap, small, comparator, priority_func);
    treap = treap_int_push(treap, root, comparator, priority_func);
    treap = treap_int_push(treap, big, comparator, priority_func);

    treap = treap_int_pop_big(treap, &res_big);
    treap_int_print(treap, printer); printf("\n");

    treap = treap_int_pop_big(treap, &res_mid);
    treap_int_print(treap, printer); printf("\n");

    treap = treap_int_pop_big(treap, &res_small);
    treap_int_print(treap, printer); printf("\n");

    test_assert(res_small == small, "Small value is correctly popped");
    test_assert(res_mid == root, "Mid value is correctly popped");
    test_assert(res_big == big, "Big value is correctly popped");

    test_suite("treap delete");

    treap = treap_int_push(treap, small, comparator, priority_func);
    treap_int_print(treap, printer); printf("\n");

    treap = treap_int_push(treap, big, comparator, priority_func);
    treap_int_print(treap, printer); printf("\n");

    treap = treap_int_push(treap, root, comparator, priority_func);
    treap_int_print(treap, printer); printf("\n");

    treap = treap_int_delete(treap, NULL);

    test_assert(treap_int_is_empty(treap), "Deleted treap is empty");

    free(treap);
}

int main(int argc, char *argv[]){
    unit_test(argc, argv);

    test_suite("\n\n\n ================================================ TEST 08-treap.c =========================================================");

    treap_NULL();
    treap_tests();

    exit(EXIT_SUCCESS);
}