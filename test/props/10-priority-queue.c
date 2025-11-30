#include <libellul/type/priority-queue.h>

#define pq_datum_t int
#include <libellul/type/priority-queue/priority-queue-implementation.h>

#include <libellul.h>

void printer(int value){printf("%d", value);}

void pq_NULL(void){
    pq_int_t pq = pq_int_new();

    pq_int_print(pq, printer);

    test_suite("NULL as priority queue");

    test_assert(pq_int_is_empty(pq), "NULL is an empty priority queue");
    test_assert(0 == pq_int_length(pq), "NULL has length 0");

    pq_int_delete(pq, NULL);
    test_assert(1, "can delete NULL as a priority queue");

    free(pq);
}

void pq_tests(void){
    pq_int_t pq = pq_int_new();

    int values[6] =     {1, 5, -3, 12, 0, 42};
    int priorities[6] = {2, 4, -1, 15, 3, -5};
    int corrects[6] =   {12, 5, 0, 1, -3, 42};

    pq_int_print(pq, printer);

    test_suite("Add 1 element to pq");

    pq = pq_int_push(values[0], priorities[0], pq);
    pq_int_print(pq, printer);

    test_assert(!pq_int_is_empty(pq), "pq is not empty after push");
    test_assert(values[0] == pq_int_peek(pq), "first value is correct");
    test_assert(1 == pq_int_length(pq), "pq has length 1");

    test_suite("Remove 1 element to pq");

    int results[6] = {0, 0, 0, 0, 0, 0};
    pq = pq_int_pop(&results[0], pq);
    pq_int_print(pq, printer);

    test_assert(pq_int_is_empty(pq), "pq is empty after pop the only element");
    test_assert(results[0] == values[0], "the pop element is correct");
    results[0] = 0;

    test_suite("Add multiple elements");

    for (int i = 0; i < 6; i++){
        pq_int_push(values[i], priorities[i], pq);
        pq_int_print(pq, printer);
    }

    test_assert(values[3] == pq_int_peek(pq), "first value is correct");
    test_assert(6 == pq_int_length(pq), "pq has length 6");

    test_suite("Remove multiple elements");

    for (int i = 5; i >= 0; i--){
        pq_int_pop(&results[i], pq);
        pq_int_print(pq, printer);
    }

    int test = 1;
    for (int i = 0; i < 6; i++){
        if (results[i] != corrects[i]){test = 0;}
    }
    test_assert(test, "All values are correctly popped");
    test_assert(pq_int_is_empty(pq), "pq is empty after fully popped");

    test_suite("Delete pq");

    for (int i = 0; i < 6; i++){pq_int_push(values[i], priorities[i], pq);}
    pq = pq_int_delete(pq, NULL);

    test_assert(pq_int_is_empty(pq), "Deleted pq is empty");
    
    free(pq);
}

int main(int argc, char *argv[]){
    unit_test(argc, argv);

    test_suite("\n\n\n ============================================= TEST 10-priority-queue.c ======================================================");

    pq_NULL();
    pq_tests();

    exit(EXIT_SUCCESS);
}


