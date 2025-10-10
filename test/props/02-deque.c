#include "libellul/type/deque.h"

#define datum_t int
#include "libellul/type/deque/deque-implementation.h"

#include <libellul.h>

void deque_NULL( void ) {
    deque_int_t deque = deque_int_new();

    test_suite( "NULL as a deque" );

    test_assert( deque_int_is_empty( deque ), "NULL is an empty deque" );

    deque_int_delete( deque, NULL ); free(deque);
    test_assert( 1, "Can delete NULL as a deque" );
}

int *rand_ints( size_t n ) {
  int *vec = calloc( n, sizeof( *vec ) );
  assert( vec );

  for ( size_t i = 0 ; i < n ; i++ ) vec[ i ] = rand() % 50;

  return vec;
}

void deque_tests( void ) {
    deque_int_t deque = deque_int_new();

    test_suite("Push front in deque");

    int *values_front = calloc(4, sizeof(values_front));
    values_front[0] = 42; values_front[1] = 1; values_front[2] = 2; values_front[3] = 3;

    deque = deque_int_push_front(values_front[0], deque);

    test_assert( !deque_int_is_empty(deque), "Deque is not empty");
    test_assert( values_front[0] == deque_int_first(deque), "Deque head is correct");

    for (int i = 1; i < 4; i++) deque = deque_int_push_front(values_front[i], deque);
    test_assert( !deque_int_is_empty(deque), "Push front multiple values");

    test_suite("Push back in deque");

    int *values_back = calloc(3, sizeof(values_back));
    values_back[0] = -39; values_back[1] = -1; values_back[2] = -2;

    deque = deque_int_push_back(values_back[0], deque);

    test_assert( !deque_int_is_empty(deque), "Deque is still not empty");
    test_assert( values_back[0] == deque_int_last(deque), "Deque queue is correct");

    for (int i = 1; i < 3; i++) deque = deque_int_push_back(values_back[i], deque);
    test_assert( !deque_int_is_empty(deque), "Push back multiple values");

    test_suite("Pop front in deque");

    int i = 3;
    while(deque->head != deque){
        int value_front;
        deque = deque_int_pop_front(&value_front, deque);
        test_assert( value_front == values_front[i], "Pop front is correct");
        i--;
    };

    test_suite("Pop back in deque");

    int value_back; int j = 2;
    while(deque->queue != deque){
        deque_int_pop_back(&value_back, deque);
        test_assert( value_back == values_back[j], "Pop back is correct");
        j--;
    }

    test_assert(deque_int_is_empty(deque), "Deque is empty after fully poped");

    test_suite("Deque delete");

    for (int i = 0; i < 3; i++) deque = deque_int_push_front(values_front[i], deque);
    for (int i = 0; i < 3; i++) deque = deque_int_push_back(values_back[i], deque);

    deque = deque_int_delete(deque, NULL);
    test_assert(deque_int_is_empty(deque), "Deque is empty after delete");

    free(deque);
    free(values_front);
    free(values_back);
}

int main (int argc, char *argv[]){
    unit_test(argc, argv);

    deque_NULL();
    deque_tests();

    exit(EXIT_SUCCESS);
}