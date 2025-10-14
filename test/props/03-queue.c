#include <libellul/type/queue.h>

#define datum_t int
#include <libellul/type/queue/queue-implementation.h>

#include <libellul.h>

void queue_NULL(void) {
    test_suite( "NULL as a queue" );

    queue_int_t queue = queue_int_new();

    test_assert( queue_int_is_empty( queue ), "NULL is an empty queue" );

    queue_int_print(queue);

    queue_int_delete( queue, NULL );
    test_assert( 1, "Can delete NULL as a queue" );
}

void queue_test(void){
    queue_int_t queue = queue_int_new();
    int input = 42;
    int output = 0;

    int inputs[7] = {1, 2, 3, -1, -2, 0, 87};
    int outputs[7] = {0, 0, 0, 0, 0, 0, 0};


    test_suite("Queue push one element");

    queue = queue_int_push(input, queue);

    queue_int_print(queue);

    test_assert(!queue_int_is_empty(queue), "Queue is not empty after push");

    test_assert(queue_int_first(queue) == input, "Correct push");


    test_suite("Queue pop one element");

    queue = queue_int_pop(&output, queue);

    queue_int_print(queue);

    test_assert(output == input, "Correct pop");

    test_assert(queue_int_is_empty(queue), "Queue is empty after fully popped");


    test_suite("Queue push multiple elements");

    for (int i = 0; i < 7; i++){
        queue = queue_int_push(inputs[i], queue);
        queue_int_print(queue);
        
        test_assert(queue_int_first(queue) == inputs[0], "First value is the first value pushed");
    }


    test_suite("Queue pop multiple elements");

    for (int i = 0; i < 7; i++){
        queue = queue_int_pop(&outputs[i], queue);
        queue_int_print(queue);
        
        test_assert(outputs[i] == inputs[i], "Popped value is correct");
    }

    test_assert(queue_int_is_empty(queue), "Queue is empty after fully popped");


    test_suite("Queue delete");

    for (int i = 0; i < 7; i++){queue = queue_int_push(inputs[i], queue);}

    queue = queue_int_delete(queue, NULL);

    test_assert(queue_int_is_empty(queue), "Queue is empty after deleted");
}

int main (int argc, char *argv[]){
    unit_test(argc, argv);

    test_suite("\n\n\n ================================================ TEST 03-queue.c =========================================================");

    queue_NULL();
    queue_test();

    exit(EXIT_SUCCESS);
}