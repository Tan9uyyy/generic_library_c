#include <libellul/type/stack.h>

#define stack_datum_t int
#include <libellul/type/stack/stack-implementation.h>

#include <libellul.h>

#define destructor NULL

void printer(int val){printf("%d", val);}

void stack_NULL(void) {
    test_suite( "NULL as a stack" );

    stack_int_t stack = stack_int_new();

    test_assert( stack_int_is_empty( stack ), "NULL is an empty stack" );
    test_assert( stack_int_length(stack) == 0, "NULL length is 0");

    stack_int_print(stack, printer);

    stack_int_delete(stack, NULL );
    test_assert( 1, "Can delete NULL as a stack" );

    free(stack);
}

void stack_test(void){
    stack_int_t stack = stack_int_new();
    int input = 42;
    int output = 0;

    int inputs[7] = {1, 2, 3, -1, -2, 0, 87};
    int outputs[7] = {0, 0, 0, 0, 0, 0, 0};


    test_suite("stack push one element");

    stack = stack_int_push(input, stack);

    stack_int_print(stack, printer);

    test_assert(!stack_int_is_empty(stack), "stack is not empty after push");
    test_assert( stack_int_length(stack) == 1, "Stack length is 1");

    test_assert(stack_int_first(stack) == input, "Correct push");


    test_suite("stack pop one element");

    stack = stack_int_pop(&output, stack, destructor);

    stack_int_print(stack, printer);

    test_assert(output == input, "Correct pop");

    test_assert(stack_int_is_empty(stack), "stack is empty after fully popped");


    test_suite("stack push multiple elements");

    for (int i = 0; i < 7; i++){
        stack = stack_int_push(inputs[i], stack);
        stack_int_print(stack, printer);
        
        test_assert(stack_int_first(stack) == inputs[i], "First value is the last value pushed");
    }

    test_assert( stack_int_length(stack) == 7, "Stack length is 7");


    test_suite("stack pop multiple elements");

    for (int i = 0; i < 7; i++){
        stack = stack_int_pop(&outputs[i], stack, destructor);
        stack_int_print(stack, printer);
        
        test_assert(outputs[i] == inputs[6 - i], "Popped value is correct");
    }

    test_assert(stack_int_is_empty(stack), "stack is empty after fully popped");


    test_suite("stack delete");

    for (int i = 0; i < 7; i++){stack = stack_int_push(inputs[i], stack);}

    stack_int_print(stack, printer);

    stack = stack_int_delete(stack, NULL);

    test_assert(stack_int_is_empty(stack), "stack is empty after deleted");

    free(stack);
}

int main (int argc, char *argv[]){
    unit_test(argc, argv);

    test_suite("\n\n\n ================================================ TEST 04-stack.c =========================================================");

    stack_NULL();
    stack_test();

    exit(EXIT_SUCCESS);
}