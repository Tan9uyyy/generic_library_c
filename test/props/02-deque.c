#include <libellul/type/deque.h>

#define datum_t int
#include <libellul/type/deque/deque-implementation.h>

#include <libellul.h>

void deque_NULL( void ) {
    deque_int_t deque = deque_int_new();

    deque_int_print(deque);

    test_suite( "NULL as a deque" );

    test_assert( deque_int_is_empty( deque ), "NULL is an empty deque" );

    deque_int_delete( deque, NULL ); free(deque);
    test_assert( 1, "Can delete NULL as a deque" );
}

void deque_tests( void ) {
    deque_int_t deque = deque_int_new();

    test_suite("Push front in deque");

    int *values = calloc(7, sizeof(values));
    values[0] = 42; values[1] = 1; values[2] = 2; values[3] = 3;
    values[4] = -39; values[5] = -1; values[6] = -2;

    deque = deque_int_push_front(values[0], deque);

    deque_int_print(deque);

    test_assert( !deque_int_is_empty(deque), "Deque is not empty");
    test_assert( values[0] == deque_int_first(deque), "Deque head is correct");

    for (int i = 1; i < 4; i++) deque = deque_int_push_front(values[i], deque);
    deque_int_print(deque);
    
    test_assert( !deque_int_is_empty(deque), "Push front multiple values");

    test_suite("Push back in deque");

    deque = deque_int_push_back(values[4], deque);
    deque_int_print(deque);

    test_assert( !deque_int_is_empty(deque), "Deque is still not empty");
    test_assert( values[4] == deque_int_last(deque), "Deque queue is correct");

    for (int i = 5; i < 7; i++) deque = deque_int_push_back(values[i], deque);
    deque_int_print(deque);

    test_assert( !deque_int_is_empty(deque), "Push back multiple values");

    test_suite("Pop front in deque");

    int value = 0;
    while(!deque_int_is_empty(deque)){
        deque = deque_int_pop_front(&value, deque);
        deque_int_print(deque);
        test_assert( value, "Pop front is correct");
    };

    test_suite("Pop back in deque");

    deque = deque_int_push_front(values[0], deque);
    deque = deque_int_push_front(values[1], deque);
    deque = deque_int_push_front(values[2], deque);
    deque = deque_int_push_front(values[3], deque);
    deque = deque_int_push_front(values[4], deque);
    deque = deque_int_push_front(values[5], deque);
    deque = deque_int_push_front(values[6], deque);
    deque_int_print(deque);

    while(!deque_int_is_empty(deque)){
        deque = deque_int_pop_back(&value, deque);
        deque_int_print(deque); printf("%d\n", value);
        test_assert( value, "Pop back is correct");
    };

    test_assert(deque_int_is_empty(deque), "Deque is empty after fully poped");

    test_suite("Deque delete");

    deque = deque_int_push_back(values[0], deque);
    deque = deque_int_push_back(values[1], deque);
    deque = deque_int_push_back(values[2], deque);
    deque = deque_int_push_back(values[3], deque);
    deque = deque_int_push_front(values[4], deque);
    deque = deque_int_push_front(values[5], deque);
    deque = deque_int_push_front(values[6], deque);

    deque = deque_int_delete(deque, NULL);
    test_assert(deque_int_is_empty(deque), "Deque is empty after delete");

    free(values);
}

int main (int argc, char *argv[]){
    unit_test(argc, argv);

    test_suite("\n\n\n ================================================ TEST 02-deque.c =========================================================");

    deque_NULL();
    deque_tests();

    exit(EXIT_SUCCESS);
}