#ifndef deque_datum_t
    #error "Undefined datum type !"
#endif

T               DEQUE_METHOD(new)(void);
int             DEQUE_METHOD(is_empty)(T deque);
int             DEQUE_METHOD(length)(T deque);
deque_datum_t   DEQUE_METHOD(first)(T deque);
deque_datum_t   DEQUE_METHOD(last)(T deque);
deque_datum_t   DEQUE_METHOD(get)(T deque, int index);
T               DEQUE_METHOD(set)(deque_datum_t value, T deque, int index);
T               DEQUE_METHOD(push_front)(deque_datum_t value, T deque);
T               DEQUE_METHOD(push_back)(deque_datum_t value, T deque);
T               DEQUE_METHOD(pop_front)(deque_datum_t *value, T deque);
T               DEQUE_METHOD(pop_back)(deque_datum_t *value, T deque);
T               DEQUE_METHOD(rotate)(int nb_rot, T deque);
int             DEQUE_METHOD(contains)(T deque, deque_datum_t value);
T               DEQUE_METHOD(remove)(deque_datum_t value, T deque);
T               DEQUE_METHOD(delete)(T deque);
void            DEQUE_METHOD(print)(T deque);