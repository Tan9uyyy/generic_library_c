#ifndef _PRIORITY_QUEUE_IMPLEMENTATION_H__
#define _PRIORITY_QUEUE_IMPLEMENTATION_H__

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#ifndef pq_datum_t
    #error "Undefined datum type !"
#endif

#include "priority-queue-export-def.h"

#define deque_datum_t pq_datum
#include "../deque/deque-implementation.h"
#undef deque_datum_t

#define T pq

typedef TYPE(deque, pq_datum) TYPE(T, pq_datum_t);

void printer_pq_datum(pq_datum node, void (*printer)(pq_datum_t)){
    printf("(%d, ", node.priority);
    printer(node.value);
    printf(")");
}

TYPE(T, pq_datum_t) METHOD(T, pq_datum_t, new)(void){return METHOD(deque, pq_datum, new)();}

int METHOD(T, pq_datum_t, is_empty)(TYPE(T, pq_datum_t) pq){return METHOD(deque, pq_datum, is_empty)(pq);}

int METHOD(T, pq_datum_t, length)(TYPE(T, pq_datum_t) pq){return METHOD(deque, pq_datum, length)(pq);}

pq_datum_t METHOD(T, pq_datum_t, peek)(TYPE(T, pq_datum_t) pq){return METHOD(deque, pq_datum, first)(pq).value;}

TYPE(T, pq_datum_t) METHOD(T, pq_datum_t, push)(pq_datum_t value, int priority, TYPE(T, pq_datum_t) pq){
    pq_datum *elem = malloc(sizeof(elem)); elem->value = value; elem->priority = priority; int count = 0;

    if (METHOD(T, pq_datum_t, is_empty)(pq)){return METHOD(deque, pq_datum, push_front)(*elem, pq);}

    if (METHOD(deque, pq_datum, first)(pq).priority < priority){return METHOD(deque, pq_datum, push_front)(*elem, pq);}
    if (METHOD(deque, pq_datum, last)(pq).priority > priority){return METHOD(deque, pq_datum, push_back)(*elem, pq);}

    while(METHOD(deque, pq_datum, first)(pq).priority > priority){pq = METHOD(deque, pq_datum, rotate)(1, pq); count++;}
    pq = METHOD(deque, pq_datum, push_front)(*elem, pq);
    pq = METHOD(deque, pq_datum, rotate)(-count, pq);

    return pq;
}

TYPE(T, pq_datum_t) METHOD(T, pq_datum_t, pop)(pq_datum_t *value, TYPE(T, pq_datum_t) pq, void (*destructor)(pq_datum_t)){
    pq_datum *elem = malloc(sizeof(elem));
    pq = METHOD(deque, pq_datum, pop_front)(elem, pq, NULL);

    *value = elem->value;
    if (destructor) destructor(elem->value);

    free(elem);
    return pq;
}

TYPE(T, pq_datum_t) METHOD(T, pq_datum_t, delete)(TYPE(T, pq_datum_t) pq, void (*destructor) (pq_datum_t)){
    pq_datum_t storage;
    while (!METHOD(T, pq_datum_t, is_empty)(pq)) {pq = METHOD(T, pq_datum_t, pop)(&storage, pq, destructor);}
    
    return pq;
}

void METHOD(T, pq_datum_t, print)(TYPE(T, pq_datum_t) pq, void (*printer) (pq_datum_t)){
    // Case Empty
    if (METHOD(T, pq_datum_t, is_empty)(pq)) {
        printf("{}\n"); 

        return;
    }

    // Case 1 element
    if (1 == METHOD(T, pq_datum_t, length)(pq)) { 
        printf("{");
        printer_pq_datum(pq->head->datum, printer);
        printf("}\n");

        return;
    };

    // Case multiple elements
    printf("{");
    printer_pq_datum(pq->head->datum, printer);

    TYPE(link, pq_datum) *iterator = pq->head->next;
    while(iterator != pq->head) {
        printf(", ");
        printer_pq_datum(iterator->datum, printer);
        iterator = iterator->next;
    }

    printf("}\n");
}




#undef T

#endif