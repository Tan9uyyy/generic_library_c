#define T_HEAP_TAG int_heap
#define heap_datum_t int

#define HEAP_DESTRUCTOR(val) NULL
#define HEAP_PRINTER(val) printf("%d", (val))
#define HEAP_COMPARATOR(val1, val2) ((val1)-(val2))

#include <libellul/type/heap.h>
#include <libellul.h>

void heap_NULL( void ) {
    int_heap_t heap = int_heap_new();

    int_heap_print(heap);

    test_suite( "NULL as a heap" );

    test_assert( int_heap_is_empty( heap ), "NULL is an empty heap" );

    int_heap_delete(heap);
    test_assert( 1, "Can delete NULL as a heap" );
}

void heap_tests(){
    test_suite("heap push one element");

    int_heap_t heap = int_heap_new();

    int_heap_print(heap);

    int root = 42; int big = 102; int small = 6;
    int_heap_push(heap, root);

    int_heap_print(heap);

    test_assert(!int_heap_is_empty(heap), "heap is not empty after push");
    test_assert(int_heap_root(heap) == root, "Root is the expected value");
    test_assert(int_heap_contains(heap, root), "heap contains root");

    test_suite("heap push multiple elements");

    int_heap_push(heap, big);
    int_heap_print(heap);
    int_heap_push(heap, small);
    int_heap_print(heap);

    test_assert(int_heap_contains(heap, small), "heap contains small");
    test_assert(int_heap_contains(heap, big), "heap contains big");

    test_suite("heap pop");

    int res_small; int res_big; int res_mid;
    int_heap_pop(heap, &res_small);
    int_heap_print(heap);

    int_heap_pop(heap, &res_mid);
    int_heap_print(heap);

    int_heap_pop(heap, &res_big);
    int_heap_print(heap);

    test_assert(res_small == small, "Small value is correctly popped");
    test_assert(res_mid == root, "Mid value is correctly popped");
    test_assert(res_big == big, "Big value is correctly popped");

    test_suite("heap delete");

    int_heap_push(heap, small);
    int_heap_print(heap);

    int_heap_push(heap, big);
    int_heap_print(heap);

    int_heap_push(heap, root);
    int_heap_print(heap);

    int_heap_delete(heap);

    test_assert(1, "Deleted heap is empty");
}

int main(int argc, char *argv[]){
    unit_test(argc, argv);

    test_suite("\n\n\n ================================================ TEST 13-heap.c =========================================================");

    heap_NULL();
    heap_tests();

    exit(EXIT_SUCCESS);
}