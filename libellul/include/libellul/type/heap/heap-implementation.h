#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#define FATHER(i) ((i - 1) / 2)
#define LEFT_SON(i) (2 * i + 1)
#define RIGHT_SON(i) (2 * i + 2)
#define HAS_SON(i, len) (LEFT_SON(i) >= len)

T HEAP_METHOD(new) (){return array(heap_datum_t);}

int HEAP_METHOD(is_empty) (T heap){return array_is_empty(heap);}

int HEAP_METHOD(length) (T heap){return (int)array_length(heap);}

heap_datum_t HEAP_METHOD(root) (T heap){return *heap;}

int HEAP_METHOD(swap) (T heap, int src, int dst){
    int len = (int)array_length(heap);
    assert((src < len) && (dst < len) && "Index out of range !");

    heap_datum_t temp = heap[dst];
    heap[dst] = heap[src]; heap[src] = temp;

    return 0;
}

int HEAP_METHOD(contains_rec) (T heap, heap_datum_t value, int index, int len){
    if (HEAP_COMPARATOR(heap[index], value) > 0) return 0; // If root is bigger we stop
    if (0 == HEAP_COMPARATOR(heap[index], value)) return 1; // If root is equal we return true

    if (LEFT_SON(index) > len) return 0; // If root has no son we stop
    int output = HEAP_METHOD(contains_rec) (heap, value, LEFT_SON(index), len);

    if (RIGHT_SON(index) > len) return output; // If root has no right son we return the result on the left sub tree
    output |= HEAP_METHOD(contains_rec) (heap, value, RIGHT_SON(index), len);

    return output;
}

int HEAP_METHOD(contains) (T heap, heap_datum_t value){
    return HEAP_METHOD(contains_rec) (heap, value, 0, array_length(heap));
}

int HEAP_METHOD(push) (T heap, heap_datum_t value){
    int index = (int)array_length(heap);
    array_push(&heap, value);

    while (HEAP_COMPARATOR(heap[index], heap[FATHER(index)]) < 0 && index != 0){
        HEAP_METHOD(swap) (heap, index, FATHER(index));
        index = FATHER(index);
    }

    return 0;
}

int heap_smallest_son(T heap, int index){
    int len = array_length(heap);
    if (LEFT_SON(index) >= len) return 0; // Case without any son
    if (RIGHT_SON(index) >= len) return LEFT_SON(index); // Case with only left son

    if (HEAP_COMPARATOR(heap[LEFT_SON(index)], heap[RIGHT_SON(index)]) >= 0) return RIGHT_SON(index); // right son <= left son
    return LEFT_SON(index); // left son <= right son
}

int HEAP_METHOD(pop) (T heap, heap_datum_t* value){
    assert(!array_is_empty(heap) && "Heap is empty !");

    int len = (int) array_length(heap);
    HEAP_METHOD(swap) (heap, 0, len-1);
    array_pop(&heap, value); len--;

    int index = 0; int smallest_son = heap_smallest_son(heap, 0);
    while (smallest_son){
        if (HEAP_COMPARATOR(heap[index], heap[smallest_son]) < 0) break; // If smallest son bigger we stop swapping

        HEAP_METHOD(swap)(heap, index, smallest_son);
        index = smallest_son; smallest_son = heap_smallest_son(heap, index);
    }

    return 0;
}

void HEAP_METHOD(delete) (T heap){
    int len = array_length(heap);
    if (HEAP_DESTRUCTOR()) for (int i = 0; i < len; i++) HEAP_DESTRUCTOR(heap[i]);

    return array_delete(&heap);
}

void HEAP_METHOD(print) (T heap){
    int len = array_length(heap);

    if (array_is_empty(heap)) {printf("{}\n"); return;} // Case empty
    if (1 == len) {printf("{"); HEAP_PRINTER(heap[0]); printf("}\n"); return;} // Case of 1 element

    printf("{"); HEAP_PRINTER(heap[0]); // Case of multiple elements
    for (int i = 1; i < len; i++) {printf(", "); HEAP_PRINTER(heap[i]);}
    printf("}\n");
}