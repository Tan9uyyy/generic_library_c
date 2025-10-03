#include <libellul/type/deque.h>

#include <libellul/memory.h>

#include <assert.h>
#include <string.h>

typedef struct {
    struct link_t   *next;
    void            *datum;
} link_t;

void *dequeue_new__(){
    // TO DO
}

void dequeue_delete__(void *queue){
    // TO DO
}

size_t dequeue_size__(void *queue){
    // TO DO
}

int dequeue_is_empty__(void *queue){
    // TO DO
}

void dequeue_push_front__(void *queue, void *element){
    // TO DO
}

void dequeue_push_back__(void *queue, void *element){
    // TO DO
}

void *dequeue_pop_front__(void *queue){
    // TO DO
}

void *dequeue_pop_back__(void *queue){
    // TO DO
}

