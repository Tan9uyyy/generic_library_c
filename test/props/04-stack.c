#define T_IMPL_DEQUE
#define T_STACK_TAG int_stack
#define stack_datum_t int

#define DESTRUCTOR(val) NULL
#define DESTRUCTOR_IS_NULL //macro flag pour indiquer que le destructeur est NULL (ça me simplifie pour les if parce que sinon je comprends rien)
#define COMPARATOR(val1, val2) ((val1) == (val2))
#define PRINTER(val) printf("%d", (val))

#include <libellul/type/stack.h>
#include <libellul.h>

void stack_NULL(void) {
    test_suite( "NULL as a stack" );

    int_stack_t stack = int_stack_new();

    test_assert( int_stack_is_empty( stack ), "NULL is an empty stack" );
    test_assert( int_stack_length(stack) == 0, "NULL length is 0");

    int_stack_print(stack);

    int_stack_delete(stack );
    test_assert( 1, "Can delete NULL as a stack" );

    free(stack);
}

void stack_test(void){
    int_stack_t stack = int_stack_new();
    int input = 42;
    int output = 0;

    int inputs[7] = {1, 2, 3, -1, -2, 0, 87};
    int outputs[7] = {0, 0, 0, 0, 0, 0, 0};


    test_suite("stack push one element");

    stack = int_stack_push(input, stack);

    int_stack_print(stack);

    test_assert(!int_stack_is_empty(stack), "stack is not empty after push");
    test_assert( int_stack_length(stack) == 1, "Stack length is 1");

    test_assert(int_stack_first(stack) == input, "Correct push");


    test_suite("stack pop one element");

    stack = int_stack_pop(&output, stack);

    int_stack_print(stack);

    test_assert(output == input, "Correct pop");

    test_assert(int_stack_is_empty(stack), "stack is empty after fully popped");


    test_suite("stack push multiple elements");

    for (int i = 0; i < 7; i++){
        stack = int_stack_push(inputs[i], stack);
        int_stack_print(stack);
        
        test_assert(int_stack_first(stack) == inputs[i], "First value is the last value pushed");
    }

    test_assert( int_stack_length(stack) == 7, "Stack length is 7");


    test_suite("stack pop multiple elements");

    for (int i = 0; i < 7; i++){
        stack = int_stack_pop(&outputs[i], stack);
        int_stack_print(stack);
        
        test_assert(outputs[i] == inputs[6 - i], "Popped value is correct");
    }

    test_assert(int_stack_is_empty(stack), "stack is empty after fully popped");


    test_suite("stack delete");

    for (int i = 0; i < 7; i++){stack = int_stack_push(inputs[i], stack);}

    int_stack_print(stack);

    stack = int_stack_delete(stack);

    test_assert(int_stack_is_empty(stack), "stack is empty after deleted");

    free(stack);
}

int main (int argc, char *argv[]){
    unit_test(argc, argv);

    test_suite("\n\n\n ================================================ TEST 04-stack.c =========================================================");

    stack_NULL();
    stack_test();

    exit(EXIT_SUCCESS);
}