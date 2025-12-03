#include <assert.h>

T_STACK_INTERFACE T STACK_METHOD(new) (void) {return DEQUE_METHOD(new) ();}

T_STACK_INTERFACE int STACK_METHOD(is_empty) (T stack) {return DEQUE_METHOD(is_empty) (stack);}

T_STACK_INTERFACE int STACK_METHOD(length) (T stack) {return DEQUE_METHOD(length) (stack);}

T_STACK_INTERFACE stack_datum_t STACK_METHOD(first) (T stack) {return DEQUE_METHOD(first) (stack);}

T_STACK_INTERFACE T STACK_METHOD(push) (stack_datum_t value, T stack) {
    return DEQUE_METHOD(push_front) (value, stack);
}

T_STACK_INTERFACE T STACK_METHOD(pop) (stack_datum_t *value, T stack) {
    return DEQUE_METHOD(pop_front) (value, stack);
}

T_STACK_INTERFACE T STACK_METHOD(delete) (T stack){
    return DEQUE_METHOD(delete) (stack);
}

T_STACK_INTERFACE void STACK_METHOD(print) (T stack){
    DEQUE_METHOD(print) (stack);
}


#undef T