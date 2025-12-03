#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "deque-export-def.h"


T DEQUE_METHOD(new)(void) {
  T deque = malloc(sizeof(*deque));
  assert(deque && "Allocation failed !");

  deque->head = NULL;
  deque->queue = NULL;
  deque->length = 0;

  return deque;
}

int DEQUE_METHOD(is_empty)(T deque) {return deque->length == 0;}

int DEQUE_METHOD(length)(T deque) { return deque->length; }

deque_datum_t DEQUE_METHOD(first)(T deque) {
  assert(!DEQUE_METHOD(is_empty)(deque) && "Deque is empty !");

  return deque->head->datum;
}

deque_datum_t DEQUE_METHOD(last)(T deque) {
  assert(!DEQUE_METHOD(is_empty)(deque) && "Deque is empty !");

  return deque->queue->datum;
}

deque_datum_t DEQUE_METHOD(get)(T deque, int index) {
  assert(index >= 0 && index < deque->length && "Index out of range !");
  TYPE(node, deque_datum_t) *iterator = deque->head;

  for (int i = 0; i < index; i++, iterator = iterator->next)
    ;

  return iterator->datum;
}

T DEQUE_METHOD(set)(deque_datum_t value, T deque, int index) {
  assert(index >= 0 && index < deque->length && "Index out of range !");
  TYPE(node, deque_datum_t) *iterator = deque->head;

  for (int i = 0; i < index; i++, iterator = iterator->next)
    ;

  iterator->datum = value;
  return deque;
}

/*
 * Return a pointer to the new head of the deque which datum is the one given in
 * parameter
 */
T DEQUE_METHOD(push_front)(deque_datum_t value, T deque) {
  TYPE(node, deque_datum_t) *new_head = malloc(sizeof(*new_head));
  assert(new_head && "Allocation failed !");

  new_head->datum = value;

  // Particular case if deque is empty
  if (DEQUE_METHOD(is_empty)(deque)) {
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
T DEQUE_METHOD(push_back)(deque_datum_t value, T deque) {
  TYPE(node, deque_datum_t) *new_queue = malloc(sizeof(*new_queue));
  assert(new_queue && "Allocation failed !");

  new_queue->datum = value;

  // Particular case if deque is empty
  if (DEQUE_METHOD(is_empty)(deque)) {
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
T DEQUE_METHOD(pop_front)(deque_datum_t *value, T deque) {
  assert(!DEQUE_METHOD(is_empty)(deque) && "Deque is empty !");

  // Only one element
  if (deque->length == 1) {
    *value = DEQUE_METHOD(first)(deque);
    #ifdef DESTRUCTOR_IS_NULL
    #else
    DESTRUCTOR(deque->head->datum);
    #endif

    free(deque->head);
    deque->head = NULL;
    deque->queue = NULL;
    deque->length--;

    return deque;
  }

  // Multiple elements
  TYPE(node, deque_datum_t) *new_head = deque->head->next;
  *value = DEQUE_METHOD(first)(deque);
  if (DESTRUCTOR()) DESTRUCTOR(deque->head->datum);

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
T DEQUE_METHOD(pop_back)(deque_datum_t *value, T deque) {
  assert(!DEQUE_METHOD(is_empty)(deque) && "Deque is empty !");

  // Only one element
  if (deque->length == 1) {
    *value = DEQUE_METHOD(last)(deque);
    if (DESTRUCTOR()) DESTRUCTOR(deque->queue->datum);

    free(deque->queue);
    deque->head = NULL;
    deque->queue = NULL;
    deque->length--;

    return deque;
  }

  // Multiple elements
  TYPE(node, deque_datum_t) *new_queue = deque->queue->prev;
  *value = DEQUE_METHOD(last)(deque);
  if (DESTRUCTOR()) DESTRUCTOR(deque->queue->datum);

  new_queue->next = deque->head;
  deque->head->prev = new_queue;
  free(deque->queue);
  deque->queue = new_queue;
  deque->length--;

  return deque;
}

T DEQUE_METHOD(rotate)(int nb_rot, T deque){
  if (nb_rot > 0){
    for (int i = 0; i < nb_rot; i++){deque->head = deque->head->next; deque->queue = deque->queue->next;}

    return deque;
  }

  for (int i = 0; i < -nb_rot; i++){deque->queue = deque->queue->prev; deque->head = deque->head->prev;}

  return deque;
}

/* Return
 * 1 if deque contains obj
 * 0 if deque doesn't contain obj
 */
int DEQUE_METHOD(contains)(T deque, deque_datum_t obj) {
  if (DEQUE_METHOD(is_empty)(deque))
    return 0;

  TYPE(node, deque_datum_t) *iterator = deque->head;

  do {
    if (COMPARATOR(iterator->datum, obj)) {
      return 1;
    }
    iterator = iterator->next;
  } while (iterator != deque->head);

  return 0;
}

T    DEQUE_METHOD(remove)(deque_datum_t value, T deque) {
  deque_datum_t storage;

  // Deque empty
  if (DEQUE_METHOD(is_empty)(deque)) return NULL;
  
  // Only one element
  if ((1 == deque->length) && COMPARATOR(deque->head->datum, value)){return DEQUE_METHOD(pop_back)(&storage, deque);}

  // Multiple elements
  TYPE(node, deque_datum_t) *iterator = deque->head->next;

  while(!COMPARATOR(iterator->datum, value) && iterator != deque->head){iterator = iterator->next;}

  if (!COMPARATOR(iterator->datum, value)) {return deque;} // Value not in deque
  if (iterator == deque->head)  {return DEQUE_METHOD(pop_front) (&storage, deque);} // Value at front
  if (iterator == deque->queue) {return DEQUE_METHOD(pop_back)  (&storage, deque);} // Value at back

  TYPE(node, deque_datum_t) *deque_head = deque->head; // If value is neither at the front nor the back
  TYPE(node, deque_datum_t) *deque_queue = deque->queue;
  deque->head = iterator; deque->queue = iterator->prev;

  deque = DEQUE_METHOD(pop_front)(&storage, deque);
  deque->head = deque_head; deque->queue = deque_queue;

  return deque;
}


/*
 * Return a null pointer after freeing all the elements inside the deque
 * If the datum needs to be freed you need to give a DESTRUCTOR in parameter to
 * dodge leaks... like in the matrix
 */
T DEQUE_METHOD(delete)(T deque) {
  deque_datum_t storage;
  while (!DEQUE_METHOD(is_empty)(deque)) {
      deque = DEQUE_METHOD(pop_back)(&storage, deque); // Use of pop_back so the deque head doesn't change
  }
  return deque;
}

/*
 * Print the deque like this { datum1 datum2 datum3 ...}
 */
void DEQUE_METHOD(print)(T deque) {
  // Case Empty
  if (DEQUE_METHOD(is_empty)(deque)) {
    printf("{}\n"); 

    return;
  }

  // Case 1 element
  if (1 == DEQUE_METHOD(length)(deque)) { 
    printf("{");
    PRINTER(deque->head->datum);
    printf("}\n");

    return;
  };

  // Case multiple elements
  printf("{");
  PRINTER(deque->head->datum);

  TYPE(node, deque_datum_t) *iterator = deque->head->next;
  while(iterator != deque->head) {
    printf(", ");
    PRINTER(iterator->datum);
    iterator = iterator->next;
  }

  printf("}\n");
}