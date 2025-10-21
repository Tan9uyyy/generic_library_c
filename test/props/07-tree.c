#include <libellul/type/tree.h>

#define datum_t int
#include <libellul/type/tree/tree-implementation.h>

#include <libellul.h>

void printer(int value){printf("%d", value);}

int comparator(int v1, int v2){return v1 - v2;}

void tree_NULL( void ) {
    tree_int_t tree = tree_int_new();

    tree_int_print(tree, printer);

    test_suite( "NULL as a tree" );

    test_assert( tree_int_is_empty( tree ), "NULL is an empty tree" );

    deque_int_delete( tree, NULL );
    test_assert( 1, "Can delete NULL as a deque" );

    free(tree);
}

void tree_tests(){
    
}

int main(int argc, char *argv[]){
    unit_test(argc, argv);

    test_suite("\n\n\n ================================================ TEST 07-tree.c =========================================================");

    tree_NULL();
    tree_tests();

    exit(EXIT_SUCCESS);
}