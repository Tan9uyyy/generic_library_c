

T PQ_METHOD(new)(void){return DEQUE_METHOD(new)();}

int PQ_METHOD(is_empty)(T pq){return DEQUE_METHOD(is_empty)(pq);}

int PQ_METHOD(length)(T pq){return DEQUE_METHOD(length)(pq);}

pq_datum_t PQ_METHOD(peek)(T pq){return DEQUE_METHOD(first)(pq).value;}

T PQ_METHOD(push)(pq_datum_t value, int priority, T pq){
    pq_couple elem = { .value = value, .priority = priority };

    if (PQ_METHOD(is_empty)(pq)){return DEQUE_METHOD(push_front)(elem, pq);}

    if (DEQUE_METHOD(first)(pq).priority < priority){return DEQUE_METHOD(push_front)(elem, pq);}
    if (DEQUE_METHOD(last)(pq).priority > priority){return DEQUE_METHOD(push_back)(elem, pq);}

    int count = 0;
    while(DEQUE_METHOD(first)(pq).priority > priority){pq = DEQUE_METHOD(rotate)(1, pq); count++;}
    pq = DEQUE_METHOD(push_front)(elem, pq);
    pq = DEQUE_METHOD(rotate)(-count, pq);

    return pq;
}

T PQ_METHOD(pop)(pq_datum_t *value, T pq){
    assert(!PQ_METHOD(is_empty)(pq) && "Pq is empty !");
    if (PQ_DESTRUCTOR()) PQ_DESTRUCTOR(pq->head->datum.value);

    // Only one element
    if (1 == PQ_METHOD(length)(pq)) {
        *value = PQ_METHOD(peek)(pq);
        if (PQ_DESTRUCTOR()) PQ_DESTRUCTOR(pq->head->datum.value);

        free(pq->head);
        pq->length--;

        return pq;
    }

    // Multiple elements
    struct node_pq_couple_t *new_head = pq->head->next;
    *value = PQ_METHOD(peek)(pq);
    if (PQ_DESTRUCTOR()) PQ_DESTRUCTOR(pq->head->datum.value);

    new_head->prev = pq->queue;
    pq->queue->next = new_head;

    free(pq->head);
    pq->head = new_head;
    pq->length--;

    return pq;
}

T PQ_METHOD(delete)(T pq){
    pq_datum_t storage;
    while (!PQ_METHOD(is_empty)(pq)) {pq = PQ_METHOD(pop)(&storage, pq);}
    
    return pq;
}

void PQ_METHOD(print)(T pq){
    // Case Empty
    if (PQ_METHOD(is_empty)(pq)) {
        printf("{}\n"); 

        return;
    }

    // Case 1 element
    if (1 == PQ_METHOD(length)(pq)) { 
        printf("{");
        PRINTER(pq->head->datum);
        printf("}\n");

        return;
    };

    // Case multiple elements
    printf("{");
    PRINTER(pq->head->datum);

    struct node_pq_couple_t *iterator = pq->head->next;
    while(iterator != pq->head) {
        printf(", ");
        PRINTER(iterator->datum);
        iterator = iterator->next;
    }

    printf("}\n");
}




#undef T
