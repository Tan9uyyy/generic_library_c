#ifndef _PRIORITY_QUEUE_EXPORT_DEF_H__
#define _PRIORITY_QUEUE_EXPORT_DEF_H__

#ifndef datum_t
    #error "Undefined datum type !"
#endif

#define T priority_queue
#include "../../interface.h"

typedef struct TYPE(p_sentinel, datum_t) *TYPE(T, datum_t);

TYPE(T, datum_t)    METHOD(T, datum_t, new)(void);
int                 METHOD(T, datum_t, is_empty)(TYPE(T, datum_t) deque);
int                 METHOD(T, datum_t, length)(TYPE(T, datum_t) deque);
datum_t             METHOD(T, datum_t, next)(TYPE(T, datum_t) deque);
TYPE(T, datum_t)    METHOD(T, datum_t, push)(datum_t value, int priority, TYPE(T, datum_t) deque);
TYPE(T, datum_t)    METHOD(T, datum_t, pop)(datum_t *value, TYPE(T, datum_t) deque);
TYPE(T, datum_t)    METHOD(T, datum_t, delete)(TYPE(T, datum_t) list, void (*destructor)(datum_t));
void                METHOD(T, datum_t, print)(TYPE(T, datum_t) deque);








#endif