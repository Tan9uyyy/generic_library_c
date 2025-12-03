

T                   TREESET_METHOD(new) (void);
int                 TREESET_METHOD(is_empty) (T treeset);
T                   TREESET_METHOD(add) (T treeset, treeset_datum_t value);
treeset_datum_t     TREESET_METHOD(upper_bound) (T treeset);
treeset_datum_t     TREESET_METHOD(lower_bound) (T treeset);
T                   TREESET_METHOD(remove_max) (T treeset);
T                   TREESET_METHOD(remove_min) (T treeset);
int                 TREESET_METHOD(contains) (T treeset, treeset_datum_t value);
T                   TREESET_METHOD(reunion) (T *treeset_1, T *treeset_2);
T                   TREESET_METHOD(inter) (T *treeset_1, T *treeset_2);
T                   TREESET_METHOD(delete) (T treeset);
void                TREESET_METHOD(print) (T treeset);
