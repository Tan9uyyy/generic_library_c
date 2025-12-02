#ifndef _HEAP_IMPLEMENTATION_H__
#define _HEAP_IMPLEMENTATION_H__

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#ifndef heap_datum_t
    #error "Undefined datum type !"
#endif

#include "heap-export-def.h"

#ifdef T
#undef T
#endif
#define T heap

typedef heap_datum_t *TYPE(T, heap_datum_t);

#define FATHER(i) ((i - 1) / 2)
#define LEFT_SON(i) (2 * i + 1)
#define RIGHT_SON(i) (2 * i + 2)
#define HAS_SON(i, len) (LEFT_SON(i) >= len)

TYPE(T, heap_datum_t) METHOD(T, heap_datum_t, new) (){return array(heap_datum_t);}

int METHOD(T, heap_datum_t, is_empty) (TYPE(T, heap_datum_t) heap){return array_is_empty(heap);}

int METHOD(T, heap_datum_t, length) (TYPE(T, heap_datum_t) heap){return (int)array_length(heap);}

heap_datum_t METHOD(T, heap_datum_t, root) (TYPE(T, heap_datum_t) heap){return *heap;}

int METHOD(T, heap_datum_t, swap) (TYPE(T, heap_datum_t) heap, int src, int dst){
    assert((src < (int)array_length(heap)) && (dst < (int)array_length(heap)) && "Index out of range !");

    heap_datum_t temp = heap[dst];
    heap[dst] = heap[src]; heap[src] = temp;

    return 0;
}

int METHOD(T, heap_datum_t, push) (TYPE(T, heap_datum_t) heap, heap_datum_t value, int (*comparator) (heap_datum_t, heap_datum_t)){
    int index = (int)array_length(heap);
    array_push(&heap, value);

    while (comparator(heap[index], heap[FATHER(index)]) > 0 && index > 0){
        METHOD(T, heap_datum_t, swap) (heap, index, FATHER(index));
        index = FATHER(index);
    }

    return 0;
}

int METHOD(T, heap_datum_t, pop) (TYPE(T, heap_datum_t) heap, heap_datum_t* value, int (*comparator) (heap_datum_t, heap_datum_t)){
    assert(!array_is_empty(heap) && "Heap is empty !");

    METHOD(T, heap_datum_t, swap) (heap, 0, (int)array_length(heap)-1);
    array_pop(&heap, value);

    int index = 0; int len = (int)array_length(heap);
    while (HAS_SON(index, len)){
        if (RIGHT_SON(index) > len) METHOD(T, heap_datum_t, swap) (heap, index, LEFT_SON(index));
        if (comparator(heap[RIGHT_SON(index)], heap[LEFT_SON(index)]) > 0) METHOD(T, heap_datum_t, swap) (heap, index, RIGHT_SON(index));
        METHOD(T, heap_datum_t, swap) (heap, index, LEFT_SON(index));
    }

    return 0;
}

void METHOD(T, heap_datum_t, delete) (TYPE(T, heap_datum_t) heap){return array_delete(&heap);}








#endif