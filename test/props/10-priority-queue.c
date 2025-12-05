#define T_PQ_TAG int_pq
#define pq_datum_t int

#define PQ_DESTRUCTOR(val) NULL
#define PQ_COMPARATOR(val1, val2) ((val1) - (val2))
#define PQ_PRINTER(val) printf("%d", val)
#define PQ_PRIORITY_FUNC(i) (i)

#include <libellul/type/priority-queue.h>
#include <libellul.h>

void printer(int value){printf("%d", value);}

void pq_NULL(void){
    int_pq_t pq = int_pq_new();

    int_pq_print(pq);

    test_suite("NULL as priority queue");

    test_assert(int_pq_is_empty(pq), "NULL is an empty priority queue");
    test_assert(0 == int_pq_length(pq), "NULL has length 0");

    int_pq_delete(pq);
    test_assert(1, "can delete NULL as a priority queue");
}

void pq_tests(void){
    int_pq_t pq = int_pq_new();

    int values[6] =     {1, 5, -3, 12, 0, 42};
    int priorities[6] = {2, 4, -1, 15, 3, -5};
    int corrects[6] =   {12, 5, 0, 1, -3, 42};

    int_pq_print(pq);

    test_suite("Add 1 element to pq");

    pq = int_pq_push(values[0], priorities[0], pq);
    int_pq_print(pq);

    test_assert(!int_pq_is_empty(pq), "pq is not empty after push");
    test_assert(values[0] == int_pq_peek(pq), "first value is correct");
    test_assert(1 == int_pq_length(pq), "pq has length 1");

    test_suite("Remove 1 element to pq");

    int results[6] = {0, 0, 0, 0, 0, 0};
    pq = int_pq_pop(&results[0], pq);
    int_pq_print(pq);
    printf("result = %d, expected = %d\n", results[0], values[0]);

    test_assert(int_pq_is_empty(pq), "pq is empty after pop the only element");
    test_assert(results[0] == values[0], "the pop element is correct");
    results[0] = 0;

    test_suite("Add multiple elements");

    for (int i = 0; i < 6; i++){
        int_pq_push(values[i], priorities[i], pq);
        int_pq_print(pq);
    }

    test_assert(values[3] == int_pq_peek(pq), "first value is correct");
    test_assert(6 == int_pq_length(pq), "pq has length 6");

    test_suite("Remove multiple elements");

    int test = 1;
    for (int i = 0; i < 6; i++){
        int_pq_pop(&results[i], pq);
        int_pq_print(pq);
        printf("result = %d, expected = %d\n", results[i], corrects[i]);
        if (results[i] != corrects[i]){test = 0;}
    }

    test_assert(test, "All values are correctly popped");
    test_assert(int_pq_is_empty(pq), "pq is empty after fully popped");

    test_suite("Delete pq");

    for (int i = 0; i < 6; i++){int_pq_push(values[i], priorities[i], pq);}
    int_pq_delete(pq);

    test_assert(1, "Deleted pq");
} 


int main(int argc, char *argv[]){
    unit_test(argc, argv);

    test_suite("\n\n\n ============================================= TEST 10-priority-queue.c ======================================================");

    pq_NULL();
    pq_tests();

    exit(EXIT_SUCCESS);
}


