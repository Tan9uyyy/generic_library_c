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



struct TYPE(link, datum_t){
    struct TYPE(link, datum_t) *next;
    struct TYPE(link, datum_t) *prev;
    datum_t                     datum;
};



TYPE(T, datum_t) METHOD(new) (void) {return NULL;}

int METHOD(is_empty) (TYPE(T, datum_t) deque){return METHOD(new) () == deque;}

datum_t METHOD(first) (TYPE(T, datum_t) deque){
    assert( !METHOD(is_empty) (deque) && "Deque is empty !");

    return deque->datum;
}

datum_t METHOD(last) (TYPE(T, datum_t) deque){
    assert( !METHOD(is_empty) (deque) && "Deque is empty !");

    return deque->prev->datum;
}

/*
* Return a pointer to the new head of the deque which datum is the one given in parameter
*/
TYPE(T, datum_t) METHOD(push_front) (datum_t value, TYPE(T, datum_t) deque){
    TYPE(T, datum_t) new_head = malloc(sizeof(*new_head));
    assert(new_head && "Allocation failed !");

    new_head->datum = value;

    // Particular case if deque is empty
    if (METHOD(is_empty) (deque)){
        new_head->next = new_head; new_head->prev = new_head;

        return new_head;
    }

    // General case
    new_head->next = deque; new_head->prev = deque->prev;
    deque->prev->next = new_head; deque->prev = new_head;

    return new_head;
}

/*
* Return a pointer to the same head as the change is the queue,
* The datum of the queue is the one given in parameters
*/
TYPE(T, datum_t) METHOD(push_back) (datum_t value, TYPE(T, datum_t) deque){
    TYPE(T, datum_t) new_queue = malloc(sizeof(*new_queue));
    assert(new_queue && "Allocation failed !");

    new_queue->datum = value;

    // Particular case if deque is empty
    if (METHOD(is_empty) (deque)){
        new_queue->next = new_queue; new_queue->prev = new_queue;
        return new_queue;
    }

    // General case
    new_queue->next = deque; new_queue->prev = deque->prev;
    deque->prev->next = new_queue; deque->prev = new_queue;

    return deque;
}

/*
* Return a pointer to the new head of the deque,
* The current head is freed and its value is stored inside the pointer given in parameters
*/
TYPE(T, datum_t) METHOD(pop_front) (datum_t *value, TYPE(T, datum_t) deque){
    assert( !METHOD(is_empty) (deque) && "Deque is empty !");

    // Only one element
    if (deque->next == deque){
        *value = deque->datum;
        free(deque); 
        return NULL;
    }

    // Multiple elements
    TYPE(T, datum_t) new_head = deque->next;
    *value = deque->datum;

    new_head->prev = deque->prev; deque->prev->next = new_head;
    free(deque);

    return new_head;
}

/*
* Return a pointer to the same head of the deque as the only change is the queue,
* The current queue is freed and its value is stored inside the pointer given in parameters
*/
TYPE(T, datum_t) METHOD(pop_back) (datum_t *value, TYPE(T, datum_t) deque){
    assert( !METHOD(is_empty) (deque) && "Deque is empty !");

    // Only one element
    if (deque->next == deque){
        *value = deque->datum;
        free(deque); 
        return NULL;
    }

    // Multiple elements
    TYPE(T, datum_t) queue = deque->prev;
    *value = queue->datum;

    deque->prev = queue->prev; queue->prev->next = deque;
    free(queue);

    return deque;
}

/*
* Return a null pointer after freeing all the elements inside the deque
* If the datum needs to be freed you need to give a destructor in parameter to dodge leaks like in the matrix
*/
TYPE(T, datum_t) METHOD(delete) (TYPE(T, datum_t) deque, void (*destructor) (datum_t)){ datum_t storage;
    while (!METHOD(is_empty) (deque)){
        if (destructor){destructor(deque->prev->datum);} // If the datum needs to be freed we use the destructor given in parameters
        
        deque = deque_int_pop_back(&storage, deque); // Use of pop_back so the deque head doesn't change
    } free(deque);

    return NULL;
}

/*
* Print the deque like this { datum1 datum2 datum3 ...}
*/
void METHOD(print) (TYPE(T, datum_t) deque){
    printf("{ ");
    if (METHOD(is_empty)(deque)){printf("}\n"); return;}

    TYPE(T, datum_t) first = deque;
    TYPE(T, datum_t) iterator = deque;

    do {
        printf("%d ", iterator->datum);
        iterator = iterator->next;
    }while (iterator != first);

    printf("}\n");
}

#undef T
#undef datum_t
// #undef TYPENAME
// #undef TYPE
// #undef METHOD


#endif