#ifndef _HEAP_EXPORT_DEF_H__
#define _HEAP_EXPORT_DEF_H__

#include "../../interface.h"
#include <libellul.h>

#ifndef heap_datum_t
    #error "Undefined datum type !"
#endif

#ifdef T
#undef T
#endif
#define T heap

typedef heap_datum_t *TYPE(T, heap_datum_t);

TYPE(T, heap_datum_t)   METHOD(T, heap_datum_t, new) (void);
int                     METHOD(T, heap_datum_t, is_empty) (TYPE(T, heap_datum_t) heap);
int                     METHOD(T, heap_datum_t, length) (TYPE(T, heap_datum_t) heap);
heap_datum_t            METHOD(T, heap_datum_t, root) (TYPE(T, heap_datum_t) heap);
int                     METHOD(T, heap_datum_t, push) (TYPE(T, heap_datum_t) heap, heap_datum_t value, int (*comparator) (heap_datum_t, heap_datum_t));
int                     METHOD(T, heap_datum_t, pop) (TYPE(T, heap_datum_t) heap, heap_datum_t* value, int (*comparator) (heap_datum_t, heap_datum_t));
void                     METHOD(T, heap_datum_t, delete) (TYPE(T, heap_datum_t) heap);

#undef T

#endif