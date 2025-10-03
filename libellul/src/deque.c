#include <libellul/type/deque.h>

#include <libellul/memory.h>

#include <assert.h>
#include <string.h>

typedef struct {
    struct link_t   *next;
    void            *datum;
} link_t;

void *deque_new__(){
    // TO DO
    return NULL;
}

void deque_delete__(void *queue){
    // TO DO
}

int deque_is_empty__(void *queue){
    // TO DO

    return deque_new__() == queue;
}

void deque_push_front__(void *queue, void *element){
    // TO DO
}

void deque_push_back__(void *queue, void *element){
    // TO DO
}

void *deque_pop_front__(void *queue){
    // TO DO
}

void *deque_pop_back__(void *queue){
    // TO DO
}

