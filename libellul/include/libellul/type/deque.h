#ifndef _DEQUE_H__
#define _DEQUE_H__

#include <stddef.h>

void *deque_new__(size_t size);

void deque_delete__(void *queue);

size_t deque_size__(void *queue);

int deque_is_empty__(void *queue);

void deque_push_front__(void *queue, void *element);

void deque_push_back__(void *queue, void *element);

void *deque_pop_front__(void *queue);

void *deque_pop_back__(void *queue);

#endif