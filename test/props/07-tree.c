#include <libellul/type/tree.h>

#define datum_t int
#include <libellul/type/tree/tree-implementation.h>

#include <libellul.h>

void printer(int value){printf("%d", value);}

int comparator(int v1, int v2){return v1 - v2;}

void tree_NULL( void ) {
    binary_tree_int_t tree = binary_tree_int_new();

    binary_tree_int_print(tree, printer); printf("\n");

    test_suite( "NULL as a tree" );

    test_assert( binary_tree_int_is_empty( tree ), "NULL is an empty tree" );

    binary_tree_int_delete( tree, NULL );
    test_assert( 1, "Can delete NULL as a tree" );

    free(tree);
}

void tree_tests(){
    test_suite("Tree push one element");

    binary_tree_int_t tree = binary_tree_int_new();

    binary_tree_int_print(tree, printer); printf("\n");

    int root = 42; int big = 102; int small = 6;
    tree = binary_tree_int_push(tree, root, comparator);

    binary_tree_int_print(tree, printer); printf("\n");

    test_assert(!binary_tree_int_is_empty(tree), "Tree is not empty after push");
    test_assert(tree->value == root, "Root is the expected value");
    test_assert(binary_tree_int_contains(tree, root, comparator), "Tree contains root");

    test_suite("Tree push multiple elements");

    tree = binary_tree_int_push(tree, big, comparator);
    tree = binary_tree_int_push(tree, small, comparator);

    binary_tree_int_print(tree, printer); printf("\n");

    test_assert(tree->ls->value == small, "Left is the expected value");
    test_assert(binary_tree_int_contains(tree, small, comparator), "Tree contains small");

    test_assert(tree->rs->value == big, "Right is the expected value");
    test_assert(binary_tree_int_contains(tree, big, comparator), "Tree contains big");

    test_suite("Tree pop small");

    int res_small; int res_big; int res_mid;
    tree = binary_tree_int_pop_small(tree, &res_small);
    binary_tree_int_print(tree, printer); printf("\n");

    tree = binary_tree_int_pop_small(tree, &res_mid);
    binary_tree_int_print(tree, printer); printf("\n");

    tree = binary_tree_int_pop_small(tree, &res_big);
    binary_tree_int_print(tree, printer); printf("\n");

    test_assert(res_small == small, "Small value is correctly popped");
    test_assert(res_mid == root, "Mid value is correctly popped");
    test_assert(res_big == big, "Big value is correctly popped");

    test_suite("Tree pop big");

    tree = binary_tree_int_push(tree, small, comparator);
    tree = binary_tree_int_push(tree, root, comparator);
    tree = binary_tree_int_push(tree, big, comparator);

    tree = binary_tree_int_pop_big(tree, &res_big);
    binary_tree_int_print(tree, printer); printf("\n");

    tree = binary_tree_int_pop_big(tree, &res_mid);
    binary_tree_int_print(tree, printer); printf("\n");

    tree = binary_tree_int_pop_big(tree, &res_small);
    binary_tree_int_print(tree, printer); printf("\n");

    test_assert(res_small == small, "Small value is correctly popped");
    test_assert(res_mid == root, "Mid value is correctly popped");
    test_assert(res_big == big, "Big value is correctly popped");

    test_suite("Tree delete");

    tree = binary_tree_int_push(tree, small, comparator);
    binary_tree_int_print(tree, printer); printf("\n");

    tree = binary_tree_int_push(tree, big, comparator);
    binary_tree_int_print(tree, printer); printf("\n");

    tree = binary_tree_int_push(tree, root, comparator);
    binary_tree_int_print(tree, printer); printf("\n");

    tree = binary_tree_int_delete(tree, NULL);

    test_assert(binary_tree_int_is_empty(tree), "Deleted tree is empty");

    free(tree);
}

int main(int argc, char *argv[]){
    unit_test(argc, argv);

    test_suite("\n\n\n ================================================ TEST 07-tree.c =========================================================");

    tree_NULL();
    tree_tests();

    exit(EXIT_SUCCESS);
}