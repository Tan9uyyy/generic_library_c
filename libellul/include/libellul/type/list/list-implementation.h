#ifndef _LIST_IMPLEMENTATION_H__
#define _LIST_IMPLEMENTATION_H__

#include "list-export-def.h"
#ifndef list_datum_t
#error "Undefined datum type !"
#endif

#define T list

#include "../../interface.h"
#include "../deque.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef TYPE(deque, list_datum_t) TYPE(T, list_datum_t);

TYPE(T, list_datum_t) METHOD(T, list_datum_t, new)(void) {
  return METHOD(deque, list_datum_t, new)();
}

int METHOD(T, list_datum_t, is_empty)(TYPE(T, list_datum_t) list) {
  return METHOD(deque, list_datum_t, is_empty)(list);
}

int METHOD(T, list_datum_t, length)(TYPE(T, list_datum_t) list) {
  return METHOD(deque, list_datum_t, length)(list);
}

list_datum_t METHOD(T, list_datum_t, get)(TYPE(T, list_datum_t) list, int index) {
  return METHOD(deque, list_datum_t, get)(list, index);
}

TYPE(T, list_datum_t)
METHOD(T, list_datum_t, set)(list_datum_t value, TYPE(T, list_datum_t) list, int index) {
  return METHOD(deque, list_datum_t, set)(value, list, index);
}

TYPE(T, list_datum_t)
METHOD(T, list_datum_t, push)(list_datum_t value, TYPE(T, list_datum_t) list) {
  return METHOD(deque, list_datum_t, push_back)(value, list);
}

TYPE(T, list_datum_t) METHOD(T, list_datum_t, pop)(list_datum_t *value, TYPE(T, list_datum_t) list, void (*destructor)(list_datum_t)) {
  return METHOD(deque, list_datum_t, pop_back)(value, list, destructor);
}

TYPE(T, list_datum_t) METHOD(T, list_datum_t, remove)(list_datum_t value, TYPE(T, list_datum_t) list, int (*comparator)(list_datum_t val1, list_datum_t val2), void (*destructor)(list_datum_t)) {
  return METHOD(deque, list_datum_t, remove)(value, list, comparator, destructor);
}

TYPE(T, list_datum_t)
METHOD(T, list_datum_t, delete)(TYPE(T, list_datum_t) list, void (*destructor)(list_datum_t)) {
  return METHOD(deque, list_datum_t, delete)(list, destructor);
}

int METHOD(T, list_datum_t, contains)(TYPE(T, list_datum_t) list, list_datum_t value, int (*comparator)(list_datum_t, list_datum_t)) {
  return METHOD(deque, list_datum_t, contains)(list, value, comparator);
}

void METHOD(T, list_datum_t, print)(TYPE(T, list_datum_t) list, void (*printer) (list_datum_t)) {
  METHOD(deque, list_datum_t, print)(list, printer);
}

#undef T

#endif