#include <assert.h>

T LIST_METHOD(new)(void) {
  return DEQUE_METHOD(new)();
}

int LIST_METHOD(is_empty)(T list) {
  return DEQUE_METHOD(is_empty)(list);
}

int LIST_METHOD(length)(T list) {
  return DEQUE_METHOD(length)(list);
}

list_datum_t LIST_METHOD(get)(T list, int index) {
  return DEQUE_METHOD(get)(list, index);
}

T
LIST_METHOD(set)(list_datum_t value, T list, int index) {
  return DEQUE_METHOD(set)(value, list, index);
}

T
LIST_METHOD(push)(list_datum_t value, T list) {
  return DEQUE_METHOD(push_back)(value, list);
}

T LIST_METHOD(pop)(list_datum_t *value, T list) {
  return DEQUE_METHOD(pop_back)(value, list);
}

T LIST_METHOD(remove)(list_datum_t value, T list) {
  return DEQUE_METHOD(remove)(value, list);
}

void LIST_METHOD(delete)(T list) {
  DEQUE_METHOD(delete)(list);
}

int LIST_METHOD(contains)(T list, list_datum_t value) {
  return DEQUE_METHOD(contains)(list, value);
}

void LIST_METHOD(print)(T list) {
  DEQUE_METHOD(print)(list);
}

#undef T