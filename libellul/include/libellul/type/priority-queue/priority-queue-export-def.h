#ifndef _PRIORITY_QUEUE_EXPORT_DEF_H__
#define _PRIORITY_QUEUE_EXPORT_DEF_H__

#include "../../interface.h"

#ifndef pq_datum_t
    #error "Undefined datum type !"
#endif

typedef struct pq_datum{
    pq_datum_t value;
    int priority;
} pq_datum;

#define deque_datum_t pq_datum
#include "../deque.h"
#undef deque_datum_t

#define T pq

typedef TYPE(deque, pq_datum) TYPE(T, pq_datum_t);

TYPE(T, pq_datum_t)     METHOD(T, pq_datum_t, new) (void);
int                     METHOD(T, pq_datum_t, is_empty) (TYPE(T, pq_datum_t) pq);
int                     METHOD(T, pq_datum_t, length) (TYPE(T, pq_datum_t) pq);
pq_datum_t              METHOD(T, pq_datum_t, peek) (TYPE(T, pq_datum_t) pq);
TYPE(T, pq_datum_t)     METHOD(T, pq_datum_t, push) (pq_datum_t value, int priority, TYPE(T, pq_datum_t) pq);
TYPE(T, pq_datum_t)     METHOD(T, pq_datum_t, pop) (pq_datum_t *value, TYPE(T, pq_datum_t) pq, void (*destructor) (pq_datum_t));
TYPE(T, pq_datum_t)     METHOD(T, pq_datum_t, delete) (TYPE(T, pq_datum_t) pq, void (*destructor) (pq_datum_t));
void                    METHOD(T, pq_datum_t, print) (TYPE(T, pq_datum_t) pq, void (*printer) (pq_datum_t));


#undef T

#endif