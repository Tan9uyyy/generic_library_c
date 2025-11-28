#ifndef _PRIORITY_QUEUE_IMPLEMENTATION_H__
#define _PRIORITY_QUEUE_IMPLEMENTATION_H__

#ifndef datum_t
    #error "Undefined datum type !"
#endif

#define T priority_queue
#include "../../interface.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct TYPE(p_link, datum_t) {
  struct TYPE(p_link, datum_t) * next;
  struct TYPE(p_link, datum_t) * prev;
  datum_t datum;
  int priority;
} TYPE(p_link, datum_t);

typedef struct TYPE(p_sentinel, datum_t) {
  struct TYPE(p_link, datum_t) * head;
  int length;
} TYPE(p_sentinel, datum_t);


TYPE(T, datum_t) METHOD(T, datum_t, new)(void) {
  TYPE(T, datum_t) pq = malloc(sizeof(*pq));
  assert(pq && "Allocation failed !");

  pq->head = NULL;
  pq->length = 0;

  return pq;
}

int METHOD(T, datum_t, is_empty)(TYPE(T, datum_t) pq){return 0 == pq->length;}

int METHOD(T, datum_t, size)(TYPE(T, datum_t) pq){return pq->length;}

datum_t METHOD(T, datum_t, next)(TYPE(T, datum_t) pq){return pq->head->datum;}

TYPE(T, datum_t) METHOD(T, datum_t, push)(datum_t value, int priority, TYPE(T, datum_t) pq){
    struct TYPE(p_link, datum_t) *new_elem = malloc(sizeof(*new_elem));
    assert(new_elem && "Allocation failed !");

    new_elem->datum = value;
    new_elem->priority = priority;

    // Particular case if pq is empty
    if (METHOD(T, datum_t, is_empty)(pq)){
        new_elem->next = new_elem;
        new_elem->prev = new_elem;

        pq->head = new_elem;
        pq->length++;

        return pq;
    }

    TYPE(p_link, datum_t) *elem = pq->head;
    while (elem->next->priority > priority && pq->head != elem->next){elem = elem->next;}

    new_elem->next = elem->next;
    new_elem->prev = elem;
    elem->next->prev = new_elem;
    elem->next = new_elem;

    if (priority > pq->head->priority){pq->head = new_elem;}
    pq->length++;

    return pq;
}

TYPE(T, datum_t) METHOD(T, datum_t, pop)(datum_t *value, TYPE(T, datum_t) pq, void (*destructor)(datum_t)){
    assert(!METHOD(T, datum_t, is_empty) (pq) && "Priority queue is empty !");

    if (1 == pq->length){
        *value = pq->head->datum;
        if (destructor){destructor(pq->head->datum);}
        free(pq->head);
        pq->head = NULL;
        pq->length--;

        return pq;
    }

    TYPE(p_link, datum_t) *to_rem = pq->head;
    *value = to_rem->datum;
    to_rem->prev->next = to_rem->next;
    to_rem->next->prev = to_rem->prev;
    pq->head = to_rem->next;
    if (destructor){destructor(to_rem->datum);}
    free(to_rem);
    pq->length--;

    return pq;
}

TYPE(T, datum_t) METHOD(T, datum_t, delete)(TYPE(T, datum_t) pq, void (*destructor)(datum_t)){
  datum_t storage = 0;
  while (!METHOD(T, datum_t, is_empty) (pq)){pq = METHOD(T, datum_t, pop)(&storage, pq, destructor);}

  return pq;
}

void METHOD(T, datum_t, print)(TYPE(T, datum_t) pq, void (*printer)(datum_t)){
  printf("{");

  TYPE(p_link, datum_t) *elem = pq->head;
  for (int i = 0; i < pq->length; i++){
    printf(" (");
    printer(elem->datum);
    printf(", %d)", elem->priority);
    elem = elem->next;
  }

  printf("}\n");
}



#endif