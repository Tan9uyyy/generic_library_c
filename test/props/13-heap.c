#include <libellul/type/heap.h>

#define b_heap_datum_t int
#include <libellul/type/heap/heap-implementation.h>

#include <libellul.h>

void printer(int value){printf("%d", value);}
int comparator(int v1, int v2){return v2 - v1;}

void heap_NULL( void ) {
    heap_int_t heap = heap_int_new();

    heap_int_print(heap, printer);

    test_suite( "NULL as a heap" );

    test_assert( heap_int_is_empty( heap ), "NULL is an empty heap" );

    heap_int_delete(heap);
    test_assert( 1, "Can delete NULL as a heap" );
}

void heap_tests(){
    test_suite("heap push one element");

    heap_int_t heap = heap_int_new();

    heap_int_print(heap, printer);

    int root = 42; int big = 102; int small = 6;
    heap_int_push(heap, root, comparator);

    heap_int_print(heap, printer);

    test_assert(!heap_int_is_empty(heap), "heap is not empty after push");
    test_assert(heap_int_root(heap) == root, "Root is the expected value");
    test_assert(heap_int_contains(heap, root, comparator), "heap contains root");

    test_suite("heap push multiple elements");

    heap_int_push(heap, big, comparator);
    heap_int_print(heap, printer);
    heap_int_push(heap, small, comparator);
    heap_int_print(heap, printer);

    test_assert(heap_int_contains(heap, small, comparator), "heap contains small");
    test_assert(heap_int_contains(heap, big, comparator), "heap contains big");

    test_suite("heap pop");

    int res_small; int res_big; int res_mid;
    heap_int_pop(heap, &res_small, comparator);
    heap_int_print(heap, printer);

    heap_int_pop(heap, &res_mid, comparator);
    heap_int_print(heap, printer);

    heap_int_pop(heap, &res_big, comparator);
    heap_int_print(heap, printer);

    test_assert(res_small == small, "Small value is correctly popped");
    test_assert(res_mid == root, "Mid value is correctly popped");
    test_assert(res_big == big, "Big value is correctly popped");

    test_suite("heap delete");

    heap_int_push(heap, small, comparator);
    heap_int_print(heap, printer);

    heap_int_push(heap, big, comparator);
    heap_int_print(heap, printer);

    heap_int_push(heap, root, comparator);
    heap_int_print(heap, printer);

    heap_int_delete(heap);

    test_assert(1, "Deleted heap is empty");
}

int main(int argc, char *argv[]){
    unit_test(argc, argv);

    test_suite("\n\n\n ================================================ TEST 07-heap.c =========================================================");

    heap_NULL();
    heap_tests();

    exit(EXIT_SUCCESS);
}