#ifndef DEQUE_IMPLEMENTATION_H__
#define DEQUE_IMPLEMENTATION_H__

#ifndef datum_t
    #error "Undefined datum type !"
#endif

#define T deque
#include "../../interface.h"

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>



typedef struct TYPE(link, datum_t){
    struct TYPE(link, datum_t) *next;
    struct TYPE(link, datum_t) *prev;
    datum_t                     datum;
};

typedef struct TYPE(sentinel, datum_t){
    struct TYPE(link, datum_t) *head;
    struct TYPE(link, datum_t) *queue;
    int                         length;
};



TYPE(T, datum_t) METHOD(T, new) (void) {
    TYPE(T, datum_t) deque = malloc(sizeof(*deque));
    assert(deque && "Allocation failed !");

    deque->head = NULL; deque->queue = NULL; deque->length = 0;

    return deque;
}

int METHOD(T, is_empty) (TYPE(T, datum_t) deque){return deque->length == 0;}

int METHOD(T, length) (TYPE(T, datum_t) deque){return deque->length;}

datum_t METHOD(T, first) (TYPE(T, datum_t) deque){
    assert( !METHOD(T, is_empty) (deque) && "Deque is empty !");

    return deque->head->datum;
}

datum_t METHOD(T, last) (TYPE(T, datum_t) deque){
    assert( !METHOD(T, is_empty) (deque) && "Deque is empty !");

    return deque->queue->datum;
}

datum_t METHOD(T, get)(TYPE(T, datum_t) deque, int index){
    assert(index >= 0 && index < deque->length && "Index out of range !");
    struct TYPE(link, datum_t) *iterator = deque->head;

    for (int i = 0; i < index; i++, iterator = iterator->next);

    return iterator->datum;
}

TYPE(T, datum_t) METHOD(T, set)(datum_t value, TYPE(T, datum_t) deque, int index){
    assert(index >= 0 && index < deque->length && "Index out of range !");
    struct TYPE(link, datum_t) *iterator = deque->head;

    for (int i = 0; i < index; i++, iterator = iterator->next);

    iterator->datum = value;
    return deque;
}

/*
* Return a pointer to the new head of the deque which datum is the one given in parameter
*/
TYPE(T, datum_t) METHOD(T, push_front) (datum_t value, TYPE(T, datum_t) deque){
    struct TYPE(link, datum_t) *new_head = malloc(sizeof(*new_head));
    assert(new_head && "Allocation failed !");

    new_head->datum = value;

    // Particular case if deque is empty
    if (METHOD(T, is_empty) (deque)){
        new_head->next = new_head; new_head->prev = new_head;

        deque->head = new_head; deque->queue = new_head;
        deque->length++;

        return deque;
    }

    // General case
    deque->head->prev = new_head; deque->queue->next = new_head;
    new_head->next = deque->head; new_head->prev = deque->queue;

    deque->head = new_head;
    deque->length++;

    return deque;
}

/*
* Return a pointer to the same head as the change is the queue,
* The datum of the queue is the one given in parameters
*/
TYPE(T, datum_t) METHOD(T, push_back) (datum_t value, TYPE(T, datum_t) deque){
    struct TYPE(link, datum_t) *new_queue = malloc(sizeof(*new_queue));
    assert(new_queue && "Allocation failed !");

    new_queue->datum = value;

    // Particular case if deque is empty
    if (METHOD(T, is_empty) (deque)){
        new_queue->next = new_queue; new_queue->prev = new_queue;

        deque->head = new_queue; deque->queue = new_queue;
        deque->length++;

        return deque;
    }

    // General case
    deque->head->prev = new_queue; deque->queue->next = new_queue;
    new_queue->next = deque->head; new_queue->prev = deque->queue;

    deque->queue = new_queue;
    deque->length++;

    return deque;
}

/*
* Return a pointer to the new head of the deque,
* The current head is freed and its value is stored inside the pointer given in parameters
*/
TYPE(T, datum_t) METHOD(T, pop_front) (datum_t *value, TYPE(T, datum_t) deque){
    assert( !METHOD(T, is_empty) (deque) && "Deque is empty !");

    // Only one element
    if (deque->length == 1){
        *value = METHOD(T, first) (deque);
        free(deque->head); 
        deque->head = NULL; deque->queue = NULL; deque->length--;

        return deque;
    }

    // Multiple elements
    struct TYPE(link, datum_t) *new_head = deque->head->next;
    *value = METHOD(T, first) (deque);

    new_head->prev = deque->queue; deque->queue->next = new_head;
    free(deque->head); deque->head = new_head; deque->length--;

    return deque;
}

/*
* Return a pointer to the same head of the deque as the only change is the queue,
* The current queue is freed and its value is stored inside the pointer given in parameters
*/
TYPE(T, datum_t) METHOD(T, pop_back) (datum_t *value, TYPE(T, datum_t) deque){
    assert( !METHOD(T, is_empty) (deque) && "Deque is empty !");

    // Only one element
    if (deque->length == 1){
        *value = METHOD(T, last) (deque);
        free(deque->queue); 
        deque->head = NULL; deque->queue = NULL; deque->length--;

        return deque;
    }

    // Multiple elements
    struct TYPE(link, datum_t) *new_queue = deque->queue->prev;
    *value = METHOD(T, last) (deque);

    new_queue->next = deque->head; deque->head->prev = new_queue;
    free(deque->queue); deque->queue = new_queue; deque->length--;

    return deque;
}

/*
* Return a null pointer after freeing all the elements inside the deque
* If the datum needs to be freed you need to give a destructor in parameter to dodge leaks like in the matrix
*/
TYPE(T, datum_t) METHOD(T, delete) (TYPE(T, datum_t) deque, void (*destructor) (datum_t)){ datum_t storage;
    while (!METHOD(T, is_empty) (deque)){
        if (destructor){destructor(METHOD(T, first) (deque));} // If the datum needs to be freed we use the destructor given in parameters
        
        deque = METHOD(T, pop_front)(&storage, deque); // Use of pop_back so the deque head doesn't change
    }

    return deque;
}

/*
* Print the deque like this { datum1 datum2 datum3 ...}
*/
void METHOD(T, print) (TYPE(T, datum_t) deque){
    printf("{ ");
    if (METHOD(T, is_empty)(deque)){printf("}\n"); return;}

    struct TYPE(link, datum_t) *iterator = deque->head;

    do {
        printf("%d ", iterator->datum);
        iterator = iterator->next;
    }while (iterator != deque->head);

    printf("}\n");
}

#undef T
// #undef datum_t
// #undef TYPENAME
// #undef TYPE
// #undef METHOD


#endif