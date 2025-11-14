#include <libellul/type/treeset.h>

#define datum_t int
#include <libellul/type/treeset/treeset-implementation.h>

#include <libellul.h>



void printer(int value){printf("%d", value);}

int comparator(int v1, int v2){return v1 - v2;}

int priority_func(int i){return i;}



void treeset_NULL( void ) {
    treeset_int_t treeset = treeset_int_new();

    treeset_int_print(treeset, printer); printf("\n");

    test_suite( "NULL as a treeset" );

    test_assert( treeset_int_is_empty( treeset ), "NULL is an empty treeset" );

    treeset_int_delete( treeset, NULL );
    test_assert( 1, "Can delete NULL as a treeset" );

    free(treeset);
}

void treeset_tests(){
    treeset_int_t treeset1 = treeset_int_new();
    treeset_int_t treeset2 = treeset_int_new();

    int values1[5] = {1, 2, 3, 4, 5};
    int values2[5] = {4, 5, 6, 7, 8};

    test_suite("Treeset add 1 element");

    treeset1 = treeset_int_add(treeset1, values1[0], comparator, priority_func);
    treeset_int_print(treeset1, printer); printf("\n");

    test_assert(!treeset_int_is_empty(treeset1), "Treeset not empty after add");
    test_assert(treeset_int_contains(treeset1, values1[0], comparator), "Treeset contains the value added");

    test_suite("Treeset delete with 1 element");

    treeset1 = treeset_int_delete(treeset1, NULL);
    treeset_int_print(treeset1, printer); printf("\n");

    test_assert(treeset_int_is_empty(treeset1), "Treeset empty after delete");

    test_suite("Treeset add multiple elements");

    for (int i = 0; i < 5; i++){
        treeset1 = treeset_int_add(treeset1, values1[i], comparator, priority_func);
        treeset2 = treeset_int_add(treeset2, values2[i], comparator, priority_func);
    }

    printf("Treeset1 : "); treeset_int_print(treeset1, printer); printf("\n");
    printf("Treeset2 : "); treeset_int_print(treeset2, printer); printf("\n");

    test_assert(treeset_int_lower_bound(treeset1) == values1[0] && treeset_int_lower_bound(treeset2) == values2[0], "Lower bounds are correct ");
    test_assert(treeset_int_upper_bound(treeset1) == values1[4] && treeset_int_upper_bound(treeset2) == values2[4], "Upper bounds are correct ");

    test_suite("Treeset remove");

    treeset1 = treeset_int_remove_min(treeset1);
    treeset2 = treeset_int_remove_max(treeset2);

    printf("Treeset1 : "); treeset_int_print(treeset1, printer); printf("\n");
    printf("Treeset2 : "); treeset_int_print(treeset2, printer); printf("\n");

    test_assert(treeset_int_lower_bound(treeset1) == values1[1], "Lower bound is correct after removal");
    test_assert(treeset_int_upper_bound(treeset2) == values2[3], "Upper bound is correct after removal");

    test_suite("Treeset operations");

    treeset_int_t treeset_union = treeset_int_reunion(&treeset1, &treeset2, comparator, priority_func);

    printf("Treeset1 : "); treeset_int_print(treeset1, printer); printf("\n");
    printf("Treeset2 : "); treeset_int_print(treeset2, printer); printf("\n");
    printf("Treeset_union : "); treeset_int_print(treeset_union, printer); printf("\n");

    treeset_int_t treeset_inter = treeset_int_inter(&treeset1, &treeset2, comparator, priority_func);

    printf("Treeset1 : "); treeset_int_print(treeset1, printer); printf("\n");
    printf("Treeset2 : "); treeset_int_print(treeset2, printer); printf("\n");
    printf("Treeset_inter : "); treeset_int_print(treeset_inter, printer); printf("\n");

    printf("Union bounds : %d, %d\n", treeset_int_lower_bound(treeset_union), treeset_int_upper_bound(treeset_union));
    printf("Intersect bounds : %d, %d\n", treeset_int_lower_bound(treeset_inter), treeset_int_upper_bound(treeset_inter));

    test_assert(treeset_int_lower_bound(treeset_union) == values1[1] && treeset_int_upper_bound(treeset_union) == values2[3], "Treesets union is correct");
    test_assert(treeset_int_lower_bound(treeset_inter) == values1[3] && treeset_int_upper_bound(treeset_union) == values2[1], "Treesets intersection is correct");

    test_suite("Full treeset delete");

    treeset1 = treeset_int_delete(treeset1, NULL);
    treeset2 = treeset_int_delete(treeset2, NULL);
    treeset_union = treeset_int_delete(treeset_union, NULL);
    treeset_inter = treeset_int_delete(treeset_inter, NULL);

    free(treeset1); free(treeset2); free(treeset_union); free(treeset_inter);
}














int main(int argc, char *argv[]){
    unit_test(argc, argv);

    test_suite("\n\n\n ================================================ TEST 09-treeset.c =========================================================");

    treeset_NULL();
    treeset_tests();

    exit(EXIT_SUCCESS);
}