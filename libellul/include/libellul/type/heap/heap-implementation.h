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
    int len = (int)array_length(heap);
    assert((src < len) && (dst < len) && "Index out of range !");

    heap_datum_t temp = heap[dst];
    heap[dst] = heap[src]; heap[src] = temp;

    return 0;
}

int METHOD(T, heap_datum_t, contains_rec) (TYPE(T, heap_datum_t) heap, heap_datum_t value, int (*comparator) (heap_datum_t, heap_datum_t), int index, int len){
    if (comparator(heap[index], value) < 0) return 0; // If root is bigger we stop
    if (0 == comparator(heap[index], value)) return 1; // If root is equal we return true

    if (LEFT_SON(index) > len) return 0; // If root has no son we stop
    int output = METHOD(T, heap_datum_t, contains_rec) (heap, value, comparator, LEFT_SON(index), len);

    if (RIGHT_SON(index) > len) return output; // If root has no right son we return the result on the left sub tree
    output |= METHOD(T, heap_datum_t, contains_rec) (heap, value, comparator, RIGHT_SON(index), len);

    return output;
}

int METHOD(T, heap_datum_t, contains) (TYPE(T, heap_datum_t) heap, heap_datum_t value, int (*comparator) (heap_datum_t, heap_datum_t)){
    return METHOD(T, heap_datum_t, contains_rec) (heap, value, comparator, 0, array_length(heap));
}

int METHOD(T, heap_datum_t, push) (TYPE(T, heap_datum_t) heap, heap_datum_t value, int (*comparator) (heap_datum_t, heap_datum_t)){
    int index = (int)array_length(heap);
    array_push(&heap, value);

    while (comparator(heap[index], heap[FATHER(index)]) > 0 && index != 0){
        METHOD(T, heap_datum_t, swap) (heap, index, FATHER(index));
        index = FATHER(index);
    }

    return 0;
}

int heap_smallest_son(TYPE(T, heap_datum_t) heap, int index, int (*comparator) (heap_datum_t, heap_datum_t)){
    int len = array_length(heap);
    if (LEFT_SON(index) >= len) return 0; // Case without any son
    if (RIGHT_SON(index) >= len) return LEFT_SON(index); // Cas with only left son

    if (comparator(heap[LEFT_SON(index)], heap[RIGHT_SON(index)]) >= 0) return LEFT_SON(index); // left son >= right son
    return RIGHT_SON(index); // right son >= left son
}

int METHOD(T, heap_datum_t, pop) (TYPE(T, heap_datum_t) heap, heap_datum_t* value, int (*comparator) (heap_datum_t, heap_datum_t)){
    assert(!array_is_empty(heap) && "Heap is empty !");

    int len = (int) array_length(heap);
    METHOD(T, heap_datum_t, swap) (heap, 0, len-1);
    array_pop(&heap, value); len--;

    int index = 0; int smallest_son = heap_smallest_son(heap, 0, comparator);
    while (smallest_son){
        if (comparator(heap[index], heap[smallest_son]) >= 0) break; // If smallest son bigger we stop swapping

        heap_int_swap(heap, index, smallest_son);
        index = smallest_son; smallest_son = heap_smallest_son(heap, index, comparator);
    }

    return 0;
}

void METHOD(T, heap_datum_t, delete) (TYPE(T, heap_datum_t) heap){return array_delete(&heap);}

void METHOD(T, heap_datum_t, print) (TYPE(T, heap_datum_t) heap, void (*printer) (heap_datum_t)){
    int len = array_length(heap);

    if (array_is_empty(heap)) {printf("{}\n"); return;} // Case empty
    if (1 == len) {printf("{"); printer(heap[0]); printf("}\n"); return;} // Case of 1 element

    printf("{"); printer(heap[0]); // Case of multiple elements
    for (int i = 1; i < len; i++) {printf(", "); printer(heap[i]);}
    printf("}\n");
}








#endif