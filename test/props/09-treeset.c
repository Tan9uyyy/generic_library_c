#define T_TREESET_TAG int_treeset
#define treeset_datum_t int

#define TREESET_DESTRUCTOR(val) NULL
#define TREESET_COMPARATOR(val1, val2) ((val1) - (val2))
#define TREESET_PRINTER(val) printf("%d", val)
#define TREESET_PRIORITY_FUNC(i) (i)

#include <libellul/type/treeset.h>
#include <libellul.h>



void treeset_NULL( void ) {
    int_treeset_t treeset = int_treeset_new();

    int_treeset_print(treeset); printf("\n");

    test_suite( "NULL as a treeset" );

    test_assert( int_treeset_is_empty( treeset ), "NULL is an empty treeset" );

    int_treeset_delete( treeset );
    test_assert( 1, "Can delete NULL as a treeset" );

    free(treeset);
}



void treeset_tests(){
    int_treeset_t treeset1 = int_treeset_new();
    int_treeset_t treeset2 = int_treeset_new();

    int values1[5] = {1, 2, 3, 4, 5};
    int values2[5] = {4, 5, 6, 7, 8};

    test_suite("Treeset add 1 element");

    treeset1 = int_treeset_add(treeset1, values1[0]);
    int_treeset_print(treeset1); printf("\n");

    test_assert(!int_treeset_is_empty(treeset1), "Treeset not empty after add");
    test_assert(int_treeset_contains(treeset1, values1[0]), "Treeset contains the value added");

    test_suite("Treeset delete with 1 element");

    treeset1 = int_treeset_delete(treeset1, NULL);
    int_treeset_print(treeset1); printf("\n");

    test_assert(int_treeset_is_empty(treeset1), "Treeset empty after delete");

    test_suite("Treeset add multiple elements");

    for (int i = 0; i < 5; i++){
        treeset1 = int_treeset_add(treeset1, values1[i]);
        treeset2 = int_treeset_add(treeset2, values2[i]);
    }

    printf("Treeset1 : "); int_treeset_print(treeset1); printf("\n");
    printf("Treeset2 : "); int_treeset_print(treeset2); printf("\n");

    test_assert(int_treeset_lower_bound(treeset1) == values1[0] && int_treeset_lower_bound(treeset2) == values2[0], "Lower bounds are correct ");
    test_assert(int_treeset_upper_bound(treeset1) == values1[4] && int_treeset_upper_bound(treeset2) == values2[4], "Upper bounds are correct ");

    test_suite("Treeset remove");

    treeset1 = int_treeset_remove_min(treeset1);
    treeset2 = int_treeset_remove_max(treeset2);

    printf("Treeset1 : "); int_treeset_print(treeset1); printf("\n");
    printf("Treeset2 : "); int_treeset_print(treeset2); printf("\n");

    test_assert(int_treeset_lower_bound(treeset1) == values1[1], "Lower bound is correct after removal");
    test_assert(int_treeset_upper_bound(treeset2) == values2[3], "Upper bound is correct after removal");

    test_suite("Treeset operations");

    int_treeset_t treeset_union = int_treeset_reunion(&treeset1, &treeset2);

    printf("Treeset1 : "); int_treeset_print(treeset1); printf("\n");
    printf("Treeset2 : "); int_treeset_print(treeset2); printf("\n");
    printf("Treeset_union : "); int_treeset_print(treeset_union); printf("\n");

    int_treeset_t int_treeseter = int_treeset_inter(&treeset1, &treeset2);

    printf("Treeset1 : "); int_treeset_print(treeset1); printf("\n");
    printf("Treeset2 : "); int_treeset_print(treeset2); printf("\n");
    printf("Treeset_inter : "); int_treeset_print(int_treeseter); printf("\n");

    printf("Union bounds : %d, %d\n", int_treeset_lower_bound(treeset_union), int_treeset_upper_bound(treeset_union));
    printf("Expected bounds : %d, %d\n", values1[1], values2[3]);
    printf("Intersect bounds : %d, %d\n", int_treeset_lower_bound(int_treeseter), int_treeset_upper_bound(int_treeseter));
    printf("Expected bounds : %d, %d\n", values1[3], values2[1]);

    test_assert(int_treeset_lower_bound(treeset_union) == values1[1] && int_treeset_upper_bound(treeset_union) == values2[3], "Treesets union is correct");
    test_assert(int_treeset_lower_bound(int_treeseter) == values1[3] && int_treeset_upper_bound(int_treeseter) == values2[1], "Treesets intersection is correct");

    test_suite("Full treeset delete");

    treeset1 = int_treeset_delete(treeset1, NULL);
    treeset2 = int_treeset_delete(treeset2, NULL);
    treeset_union = int_treeset_delete(treeset_union, NULL);
    int_treeseter = int_treeset_delete(int_treeseter, NULL);

    test_assert(int_treeset_is_empty(treeset1), "treeset1 deleted");
    test_assert(int_treeset_is_empty(treeset2), "treeset1 deleted");
    test_assert(int_treeset_is_empty(treeset_union), "treeset_union deleted");
    test_assert(int_treeset_is_empty(int_treeseter), "int_treeseter deleted");

    free(treeset1); free(treeset2); free(treeset_union); free(int_treeseter);
}



int main(int argc, char *argv[]){
    unit_test(argc, argv);

    test_suite("\n\n\n ================================================ TEST 09-treeset.c =========================================================");

    treeset_NULL();
    treeset_tests();

    return 1;
}