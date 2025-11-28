#ifndef DEQUE_IMPLEMENTATION_H__
#define DEQUE_IMPLEMENTATION_H__

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "deque-export-def.h"

#define T deque

typedef struct TYPE(link, datum_t) {
  struct TYPE(link, datum_t) * next;
  struct TYPE(link, datum_t) * prev;
  datum_t datum;
} TYPE(link, datum_t);

typedef struct TYPE(sentinel, datum_t) {
  struct TYPE(link, datum_t) * head;
  struct TYPE(link, datum_t) * queue;
  int length;
} TYPE(sentinel, datum_t);

TYPE(T, datum_t) METHOD(T, datum_t, new)(void) {
  TYPE(T, datum_t) deque = malloc(sizeof(*deque));
  assert(deque && "Allocation failed !");

  deque->head = NULL;
  deque->queue = NULL;
  deque->length = 0;

  return deque;
}

int METHOD(T, datum_t, is_empty)(TYPE(T, datum_t) deque) {return deque->length == 0;}

int METHOD(T, datum_t, length)(TYPE(T, datum_t) deque) { return deque->length; }

datum_t METHOD(T, datum_t, first)(TYPE(T, datum_t) deque) {
  assert(!METHOD(T, datum_t, is_empty)(deque) && "Deque is empty !");

  return deque->head->datum;
}

datum_t METHOD(T, datum_t, last)(TYPE(T, datum_t) deque) {
  assert(!METHOD(T, datum_t, is_empty)(deque) && "Deque is empty !");

  return deque->queue->datum;
}

datum_t METHOD(T, datum_t, get)(TYPE(T, datum_t) deque, int index) {
  assert(index >= 0 && index < deque->length && "Index out of range !");
  TYPE(link, datum_t) *iterator = deque->head;

  for (int i = 0; i < index; i++, iterator = iterator->next)
    ;

  return iterator->datum;
}

TYPE(T, datum_t) METHOD(T, datum_t, set)(datum_t value, TYPE(T, datum_t) deque, int index) {
  assert(index >= 0 && index < deque->length && "Index out of range !");
  TYPE(link, datum_t) *iterator = deque->head;

  for (int i = 0; i < index; i++, iterator = iterator->next)
    ;

  iterator->datum = value;
  return deque;
}

/*
 * Return a pointer to the new head of the deque which datum is the one given in
 * parameter
 */
TYPE(T, datum_t) METHOD(T, datum_t, push_front)(datum_t value, TYPE(T, datum_t) deque) {
  TYPE(link, datum_t) *new_head = malloc(sizeof(*new_head));
  assert(new_head && "Allocation failed !");

  new_head->datum = value;

  // Particular case if deque is empty
  if (METHOD(T, datum_t, is_empty)(deque)) {
    new_head->next = new_head;
    new_head->prev = new_head;

    deque->head = new_head;
    deque->queue = new_head;
    deque->length++;

    return deque;
  }

  // General case
  deque->head->prev = new_head;
  deque->queue->next = new_head;
  new_head->next = deque->head;
  new_head->prev = deque->queue;

  deque->head = new_head;
  deque->length++;

  return deque;
}

/*
 * Return a pointer to the same head as the change is the queue,
 * The datum of the queue is the one given in parameters
 */
TYPE(T, datum_t) METHOD(T, datum_t, push_back)(datum_t value, TYPE(T, datum_t) deque) {
  TYPE(link, datum_t) *new_queue = malloc(sizeof(*new_queue));
  assert(new_queue && "Allocation failed !");

  new_queue->datum = value;

  // Particular case if deque is empty
  if (METHOD(T, datum_t, is_empty)(deque)) {
    new_queue->next = new_queue;
    new_queue->prev = new_queue;

    deque->head = new_queue;
    deque->queue = new_queue;
    deque->length++;

    return deque;
  }

  // General case
  deque->head->prev = new_queue;
  deque->queue->next = new_queue;
  new_queue->next = deque->head;
  new_queue->prev = deque->queue;

  deque->queue = new_queue;
  deque->length++;

  return deque;
}

/*
 * Return a pointer to the new head of the deque,
 * The current head is freed and its value is stored inside the pointer given in
 * parameters
 */
TYPE(T, datum_t) METHOD(T, datum_t, pop_front)(datum_t *value, TYPE(T, datum_t) deque, void (*destructor)(datum_t)) {
  assert(!METHOD(T, datum_t, is_empty)(deque) && "Deque is empty !");

  // Only one element
  if (deque->length == 1) {
    *value = METHOD(T, datum_t, first)(deque);
    if(destructor) destructor(deque->head->datum);
    free(deque->head);
    deque->head = NULL;
    deque->queue = NULL;
    deque->length--;

    return deque;
  }

  // Multiple elements
  TYPE(link, datum_t) *new_head = deque->head->next;
  *value = METHOD(T, datum_t, first)(deque);
  if(destructor) destructor(deque->head->datum);

  new_head->prev = deque->queue;
  deque->queue->next = new_head;
  free(deque->head);
  deque->head = new_head;
  deque->length--;

  return deque;
}

/*
 * Return a pointer to the same head of the deque as the only change is the
 * queue, The current queue is freed and its value is stored inside the pointer
 * given in parameters
 */
TYPE(T, datum_t) METHOD(T, datum_t, pop_back)(datum_t *value, TYPE(T, datum_t) deque, void (*destructor)(datum_t)) {
  assert(!METHOD(T, datum_t, is_empty)(deque) && "Deque is empty !");

  // Only one element
  if (deque->length == 1) {
    *value = METHOD(T, datum_t, last)(deque);
    if(destructor) destructor(deque->queue->datum);
    free(deque->queue);
    deque->head = NULL;
    deque->queue = NULL;
    deque->length--;

    return deque;
  }

  // Multiple elements
  TYPE(link, datum_t) *new_queue = deque->queue->prev;
  *value = METHOD(T, datum_t, last)(deque);
  if(destructor) destructor(deque->queue->datum);

  new_queue->next = deque->head;
  deque->head->prev = new_queue;
  free(deque->queue);
  deque->queue = new_queue;
  deque->length--;

  return deque;
}

/* Return
 * 1 if deque contains obj
 * 0 if deque doesn't contain obj
 */
int METHOD(T, datum_t, contains)(TYPE(T, datum_t) deque, datum_t obj, int (*comparator)(datum_t val1, datum_t val2)) {
  if (METHOD(T, datum_t, is_empty)(deque))
    return 0;

  TYPE(link, datum_t) *iterator = deque->head;

  do {
    if (comparator(iterator->datum, obj)) {
      return 1;
    }
    iterator = iterator->next;
  } while (iterator != deque->head);

  return 0;
}

TYPE(T, datum_t)    METHOD(T, datum_t, remove)(datum_t value, TYPE(T, datum_t) deque, int (*comparator)(datum_t, datum_t), void (*destructor)(datum_t)) {
  datum_t storage;

  // Deque empty
  if (METHOD(T, datum_t, is_empty)(deque)) return NULL;
  
  // Only one element
  if (1 == deque->length && comparator(deque->head->datum, value)){return METHOD(T, datum_t, pop_back)(&storage, deque, destructor);}

  // Multiple elements
  TYPE(link, datum_t) *iterator = deque->head->next;

  while(0 != comparator(iterator->datum, value) && iterator != deque->head){iterator = iterator->next;}

  if (value != iterator->datum) {return NULL;} // Value not in deque
  if (iterator == deque->head)  {return METHOD(T, datum_t, pop_front) (&storage, deque, destructor);} // Value at front
  if (iterator == deque->queue) {return METHOD(T, datum_t, pop_back)  (&storage, deque, destructor);} // Value at back

  TYPE(link, datum_t) *deque_head = deque->head; // If value is neither at the front nor the back
  TYPE(link, datum_t) *deque_queue = deque->queue;
  deque->head = iterator; deque->queue = iterator->prev;

  deque = METHOD(T, datum_t, pop_front)(&storage, deque, destructor);
  deque->head = deque_head; deque->queue = deque_queue;

  return deque;
}


/*
 * Return a null pointer after freeing all the elements inside the deque
 * If the datum needs to be freed you need to give a destructor in parameter to
 * dodge leaks like in the matrix
 */
TYPE(T, datum_t) METHOD(T, datum_t, delete)(TYPE(T, datum_t) deque, void (*destructor)(datum_t)) {
  datum_t storage;
  while (!METHOD(T, datum_t, is_empty)(deque)) {
      deque = METHOD(T, datum_t, pop_back)(&storage, deque, destructor); // Use of pop_back so the deque head doesn't change
  }
  return deque;
}

/*
 * Print the deque like this { datum1 datum2 datum3 ...}
 */
void METHOD(T, datum_t, print)(TYPE(T, datum_t) deque) {
  printf("{ ");
  if (METHOD(T, datum_t, is_empty)(deque)) {
    printf("}\n");
    return;
  }

  struct TYPE(link, datum_t) *iterator = deque->head;

  do {
    printf("%d ", iterator->datum);
    iterator = iterator->next;
  } while (iterator != deque->head);

  printf("}\n");
}

#undef T
// #undef datum_t
// #undef TYPENAME
// #undef TYPE
// #undef METHOD

#endif