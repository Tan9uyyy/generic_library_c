#ifndef _LIST_EXPORT_DEF_H__
#define _LIST_EXPORT_DEF_H__

#include "../../interface.h"
#include "../deque.h"

#ifndef datum_t
#error "Undefined datum type !"
#endif

#define T list

typedef TYPE(deque, datum_t) TYPE(T, datum_t);

TYPE(T, datum_t) METHOD(T, datum_t, new)(void);
int METHOD(T, datum_t, is_empty)(TYPE(T, datum_t) list);
int METHOD(T, datum_t, length)(TYPE(T, datum_t) list);
datum_t METHOD(T, datum_t, get)(TYPE(T, datum_t) list, int index);
TYPE(T, datum_t)
METHOD(T, datum_t, set)(datum_t value, TYPE(T, datum_t) list, int index);
TYPE(T, datum_t) METHOD(T, datum_t, push)(datum_t value, TYPE(T, datum_t) list);
TYPE(T, datum_t) METHOD(T, datum_t, pop)(datum_t *value, TYPE(T, datum_t) list);
TYPE(T, datum_t)
METHOD(T, datum_t, delete)(TYPE(T, datum_t) list, void (*destructor)(datum_t));
int METHOD(T, datum_t, contains)(TYPE(T, datum_t) list, datum_t value,
                                 int (*comparator)(datum_t val1, datum_t val2));
void METHOD(T, datum_t, print)(TYPE(T, datum_t) list);

#undef T

#endif