

T_TREAP_INTERFACE   T               TREAP_METHOD(new) (void);
T_TREAP_INTERFACE   int             TREAP_METHOD(is_empty) (T treap);
T_TREAP_INTERFACE   T               TREAP_METHOD(push) (T treap, treap_datum_t value);
T_TREAP_INTERFACE   treap_datum_t   TREAP_METHOD(min) (T treap);
T_TREAP_INTERFACE   treap_datum_t   TREAP_METHOD(max) (T treap);
T_TREAP_INTERFACE   T               TREAP_METHOD(pop_small) (T treap, treap_datum_t *value);
T_TREAP_INTERFACE   T               TREAP_METHOD(pop_big) (T treap, treap_datum_t *value);
T_TREAP_INTERFACE   int             TREAP_METHOD(contains) (T treap, treap_datum_t value);
T_TREAP_INTERFACE   T               TREAP_METHOD(delete) (T treap);
T_TREAP_INTERFACE   void            TREAP_METHOD(print) (T treap);