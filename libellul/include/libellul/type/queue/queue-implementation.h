#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

T_QUEUE_INTERFACE T QUEUE_METHOD(new) (void) {return DEQUE_METHOD(new) ();}

T_QUEUE_INTERFACE int QUEUE_METHOD(is_empty) (T queue) {return DEQUE_METHOD(is_empty) (queue);}

T_QUEUE_INTERFACE int QUEUE_METHOD(length) (T queue) {return DEQUE_METHOD(length) (queue);}

T_QUEUE_INTERFACE queue_datum_t QUEUE_METHOD(first) (T queue) {return DEQUE_METHOD(first) (queue);}

T_QUEUE_INTERFACE T QUEUE_METHOD(push) (queue_datum_t value, T queue) {
    return DEQUE_METHOD(push_back) (value, queue);
}

T_QUEUE_INTERFACE T QUEUE_METHOD(pop) (queue_datum_t *value, T queue) {
    return DEQUE_METHOD(pop_front) (value, queue);
}

T_QUEUE_INTERFACE T QUEUE_METHOD(delete) (T queue){
    return DEQUE_METHOD(delete) (queue);
}

T_QUEUE_INTERFACE void QUEUE_METHOD(print) (T queue){
    DEQUE_METHOD(print) (queue);
}


#undef T