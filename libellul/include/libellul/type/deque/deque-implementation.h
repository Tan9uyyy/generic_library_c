#ifndef DEQUE_IMPLEMENTATION_H__
#define DEQUE_IMPLEMENTATION_H__

#ifndef datum_t
    #error "Undefined datum type !"
#endif

#define T deque
#include "interface.h"

#include <stdlib.h>
#include <assert.h>

struct TYPE(link, datum_t){
    struct TYPE(link, datum_t)  *next;
    datum_t                     datum;
};

struct TYPE(sentinel, datum_t){
    struct TYPE(link, datum_t) *head;
    struct TYPE(link, datum_t) *queue;
};

TYPE(T, datum_t) METHOD(new) (void) {
    TYPE(T, datum_t) new_sentinel = malloc(sizeof(*new_sentinel));
    new_sentinel->head = new_sentinel;
    new_sentinel->queue = new_sentinel;

    return new_sentinel;
}

int METHOD(is_empty) (TYPE(T, datum_t) deque){
    return (deque->head == deque && deque->queue == deque);
}

datum_t METHOD(first) (TYPE(T, datum_t) deque){
    assert( !METHOD(is_empty) (deque) && "Deque is empty !");

    return deque->head->datum;
}

TYPE(T, datum_t) METHOD(last) (TYPE(T, datum_t) deque){
    assert( !METHOD(is_empty) (deque) && "Deque is empty !");

    return deque->queue->datum;
}

TYPE(T, datum_t) METHOD(push_front) (datum_t value, TYPE(T, datum_t) deque){
    TYPE(link, datum_t) *new_head = malloc(sizeof(*new_head));
    assert(new_head && "Allocation failed !");

    new_head->datum = value;
    new_head->next = deque->head;

    deque->head = new_head;

    return deque;
}

TYPE(T, datum_t) METHOD(push_back) (datum_t value, TYPE(T, datum_t) deque){
    TYPE(link, datum_t) *new_queue = malloc(sizeof(*new_queue));
    assert(new_queue && "Allocation failed !");

    new_queue->datum = value;
    new_queue->next = deque->queue;

    deque->queue = new_queue;

    return deque;
}

TYPE(T, datum_t) METHOD(pop_front) (datum_t *value, TYPE(T, datum_t) deque){
    assert( !METHOD(is_empty) (deque) && "Deque is empty !");

    TYPE(link, datum_t) *head_to_pop = deque->head;
    *value = head_to_pop->datum;

    deque->head = head_to_pop->next;
    free(head_to_pop);

    return deque;
}

TYPE(T, datum_t) METHOD(pop_back) (datum_t *value, TYPE(T, datum_t) deque){
    assert( !METHOD(is_empty) (deque) && "Deque is empty !");

    TYPE(link, datum_t) *queue_to_pop = deque->queue;
    *value = queue_to_pop->datum;

    deque->queue = queue_to_pop->next;
    free(queue_to_pop);

    return value;
}

TYPE(T, datum_t) METHOD(delete) (TYPE(T, datum_t) deque, void (*destructor) (datum_t)){
    while (!METHOD(is_empty) (deque)){
        TYPE(link, datum_t) *next_head = deque->head->next;
        TYPE(link, datum_t) *next_queue = deque->queue->next;
        if (destructor){destructor(deque->head->datum); destructor(deque->queue->datum);}
        free(deque->head);
        free(deque->queue);
        deque->head = next_head; deque->queue = next_queue;

    }

    return deque;
}

#undef T
#undef datum_t
// #undef TYPENAME
// #undef TYPE
// #undef METHOD


#endif