#define T_B_TREE
#define T_B_TREE_TAG int_b_tree
#define b_tree_datum_t int
#define T int_b_tree_t

#define PRINTER(value) printf("%d", value)
#define COMPARATOR(v1, v2) (v2 - v1)
#define DESTRUCTOR(val) NULL

#include <libellul/type/b-tree.h>
#include <libellul.h>

void tree_NULL( void ) {
    int_b_tree_t tree = int_b_tree_new();

    int_b_tree_print(tree); printf("\n");

    test_suite( "NULL as a tree" );

    test_assert( int_b_tree_is_empty( tree ), "NULL is an empty tree" );

    int_b_tree_delete(tree);
    test_assert( 1, "Can delete NULL as a tree" );

    free(tree);
}

void tree_tests(){
    test_suite("Tree push one element");

    int_b_tree_t tree = int_b_tree_new();

    int_b_tree_print(tree); printf("\n");

    int root = 42; int big = 102; int small = 6;
    tree = int_b_tree_push(tree, root);

    int_b_tree_print(tree); printf("\n");

    test_assert(!int_b_tree_is_empty(tree), "Tree is not empty after push");
    test_assert(tree->value == root, "Root is the expected value");
    test_assert(int_b_tree_contains(tree, root), "Tree contains root");

    test_suite("Tree push multiple elements");

    tree = int_b_tree_push(tree, big);
    tree = int_b_tree_push(tree, small);

    int_b_tree_print(tree); printf("\n");

    test_assert(tree->ls->value == small, "Left is the expected value");
    test_assert(int_b_tree_contains(tree, small), "Tree contains small");

    test_assert(tree->rs->value == big, "Right is the expected value");
    test_assert(int_b_tree_contains(tree, big), "Tree contains big");

    test_suite("Tree pop small");

    int res_small; int res_big; int res_mid;
    tree = int_b_tree_pop_small(tree, &res_small);
    int_b_tree_print(tree); printf("\n");

    tree = int_b_tree_pop_small(tree, &res_mid);
    int_b_tree_print(tree); printf("\n");

    tree = int_b_tree_pop_small(tree, &res_big);
    int_b_tree_print(tree); printf("\n");

    test_assert(res_small == small, "Small value is correctly popped");
    test_assert(res_mid == root, "Mid value is correctly popped");
    test_assert(res_big == big, "Big value is correctly popped");

    test_suite("Tree pop big");

    tree = int_b_tree_push(tree, small);
    tree = int_b_tree_push(tree, root);
    tree = int_b_tree_push(tree, big);

    tree = int_b_tree_pop_big(tree, &res_big);
    int_b_tree_print(tree); printf("\n");

    tree = int_b_tree_pop_big(tree, &res_mid);
    int_b_tree_print(tree); printf("\n");

    tree = int_b_tree_pop_big(tree, &res_small);
    int_b_tree_print(tree); printf("\n");

    test_assert(res_small == small, "Small value is correctly popped");
    test_assert(res_mid == root, "Mid value is correctly popped");
    test_assert(res_big == big, "Big value is correctly popped");

    test_suite("Tree pop precise elements");

    tree = int_b_tree_push(tree, small);
    tree = int_b_tree_push(tree, root);
    tree = int_b_tree_push(tree, big);
    int_b_tree_print(tree); printf("\n");

    tree = int_b_tree_pop(tree, root);
    int_b_tree_print(tree); printf("\n");

    tree = int_b_tree_pop(tree, small);
    int_b_tree_print(tree); printf("\n");

    tree = int_b_tree_pop(tree, big);
    int_b_tree_print(tree); printf("\n");

    test_assert(1, "Can pop precise values");

    test_suite("Tree delete");

    tree = int_b_tree_push(tree, small);
    int_b_tree_print(tree); printf("\n");

    tree = int_b_tree_push(tree, big);
    int_b_tree_print(tree); printf("\n");

    tree = int_b_tree_push(tree, root);
    int_b_tree_print(tree); printf("\n");

    tree = int_b_tree_delete(tree);

    test_assert(int_b_tree_is_empty(tree), "Deleted tree is empty");

    free(tree);
}

int main(int argc, char *argv[]){
    unit_test(argc, argv);

    test_suite("\n\n\n ================================================ TEST 07-tree.c =========================================================");

    tree_NULL();
    tree_tests();

    exit(EXIT_SUCCESS);
}