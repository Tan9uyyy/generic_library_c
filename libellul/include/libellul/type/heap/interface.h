

T_HEAP_INTERFACE T               HEAP_METHOD(new) (void);
T_HEAP_INTERFACE int             HEAP_METHOD(is_empty) (T heap);
T_HEAP_INTERFACE int             HEAP_METHOD(length) (T heap);
T_HEAP_INTERFACE heap_datum_t    HEAP_METHOD(root) (T heap);
T_HEAP_INTERFACE int             HEAP_METHOD(swap) (T heap, int src, int dst);
T_HEAP_INTERFACE int             HEAP_METHOD(contains) (T heap, heap_datum_t value);
T_HEAP_INTERFACE int             HEAP_METHOD(push) (T heap, heap_datum_t value);
T_HEAP_INTERFACE int             HEAP_METHOD(pop) (T heap, heap_datum_t* value);
T_HEAP_INTERFACE void            HEAP_METHOD(delete) (T heap);
T_HEAP_INTERFACE void            HEAP_METHOD(print) (T heap);