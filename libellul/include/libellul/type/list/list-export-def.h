#ifndef _LIST_EXPORT_DEF_H__
#define _LIST_EXPORT_DEF_H__

#include "../../interface.h"
#include "../deque.h"

#ifndef list_datum_t
#error "Undefined datum type !"
#endif

#define T list

typedef TYPE(deque, list_datum_t) TYPE(T, list_datum_t);

TYPE(T, list_datum_t) METHOD(T, list_datum_t, new)(void);
int METHOD(T, list_datum_t, is_empty)(TYPE(T, list_datum_t) list);
int METHOD(T, list_datum_t, length)(TYPE(T, list_datum_t) list);
list_datum_t METHOD(T, list_datum_t, get)(TYPE(T, list_datum_t) list, int index);
TYPE(T, list_datum_t)
METHOD(T, list_datum_t, set)(list_datum_t value, TYPE(T, list_datum_t) list, int index);
TYPE(T, list_datum_t) METHOD(T, list_datum_t, push)(list_datum_t value, TYPE(T, list_datum_t) list);
TYPE(T, list_datum_t) METHOD(T, list_datum_t, pop)(list_datum_t *value, TYPE(T, list_datum_t) list, void (*destructor)(list_datum_t));
TYPE(T, list_datum_t) METHOD(T, list_datum_t, remove)(list_datum_t value, TYPE(T, list_datum_t) list, int (*comparator)(list_datum_t val1, list_datum_t val2), void (*destructor)(list_datum_t));
TYPE(T, list_datum_t) METHOD(T, list_datum_t, delete)(TYPE(T, list_datum_t) list, void (*destructor)(list_datum_t));
int METHOD(T, list_datum_t, contains)(TYPE(T, list_datum_t) list, list_datum_t value, int (*comparator)(list_datum_t val1, list_datum_t val2));
void METHOD(T, list_datum_t, print)(TYPE(T, list_datum_t) list);

#undef T

#endif