#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

T DEQUE_METHOD(new)(void) {return array(deque_datum_t);}

int DEQUE_METHOD(is_empty)(T deque) {return array_is_empty(deque);}

int DEQUE_METHOD(length)(T deque) {return (int)array_length(deque);}

deque_datum_t DEQUE_METHOD(first)(T deque) {return deque[0];}

deque_datum_t DEQUE_METHOD(last)(T deque) {return deque[DEQUE_METHOD(length)(deque) - 1];}

deque_datum_t DEQUE_METHOD(get)(T deque, int index) {return deque[index];}

T DEQUE_METHOD(set)(deque_datum_t value, T deque, int index) {deque[index] = value; return deque;}

T DEQUE_METHOD(rotate)(int nb_rot, T deque) {
    int len = DEQUE_METHOD(length)(deque);
    deque_datum_t temp;

    if (nb_rot > 0){
        for (int i = 0; i < nb_rot; i++){
            temp = deque[0];
            for (int j = 0; j < len-1; j++) deque[j] = deque[j+1];
            deque[len-1] = temp;
        }

        return deque;
    }

    for (int i = 0; i < -nb_rot; i++){
        temp = deque[len-1];
        for (int j = len-1; j > 0; j--) deque[j] = deque[j-1];
        deque[0] = temp;
    }

    return deque;
}

T DEQUE_METHOD(push_back)(deque_datum_t value, T deque) {array_push(&deque, value); return deque;}

T DEQUE_METHOD(push_front)(deque_datum_t value, T deque) {DEQUE_METHOD(push_back)(value, deque); return DEQUE_METHOD(rotate)(-1, deque);}

T DEQUE_METHOD(pop_back)(deque_datum_t *value, T deque) {array_pop(&deque, value); return deque;}

T DEQUE_METHOD(pop_front)(deque_datum_t *value, T deque) {DEQUE_METHOD(rotate)(1, deque); return DEQUE_METHOD(pop_back)(value, deque);}

int DEQUE_METHOD(contains)(T deque, deque_datum_t value) {
    int len = DEQUE_METHOD(length)(deque);

    for (int i = 0; i < len; i++) if (COMPARATOR(deque[i], value)) return 1;
    return 0;
}

T DEQUE_METHOD(remove)(deque_datum_t value, T deque) {
    int len = DEQUE_METHOD(length)(deque); int remove_flag = 0; deque_datum_t storage;

    for (int i = 0; i < len; i++){
        if (!remove_flag && COMPARATOR(DEQUE_METHOD(last)(deque), value)) {
            DEQUE_METHOD(pop_back)(&storage, deque);
            remove_flag = 1;
        }
        DEQUE_METHOD(rotate)(1, deque);
    }

    return deque;
}

void DEQUE_METHOD(delete)(T deque){
    int len = DEQUE_METHOD(length)(deque);
    if (DESTRUCTOR()) for (int i = 0; i < len; i++) DESTRUCTOR(deque[i]);

    array_delete(&deque); 
}

void DEQUE_METHOD(print)(T deque){
    printf("{ "); int len = DEQUE_METHOD(length)(deque);
    for (int i = 0; i < len; i++) {PRINTER(deque[i]); printf(" ");}
    printf("}\n");
}