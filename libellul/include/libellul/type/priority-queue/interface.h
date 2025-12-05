
T           PQ_METHOD(new) (void);
int         PQ_METHOD(is_empty) (T pq);
int         PQ_METHOD(length) (T pq);
pq_datum_t  PQ_METHOD(peek) (T pq);
T           PQ_METHOD(push) (pq_datum_t value, int priority, T pq);
T           PQ_METHOD(pop) (pq_datum_t *value, T pq);
void        PQ_METHOD(delete) (T pq);
void        PQ_METHOD(print) (T pq);
