#ifndef _QUEUE_EXPORT_DEF_H__
#define _QUEUE_EXPORT_DEF_H__

#ifndef datum_t
    #error "Undefined datum type !"
#endif

#define T queue
#include "../../interface.h"

typedef struct TYPE(T, datum_t);

TYPE(T, datum_t)    METHOD(new) (void);
int                 METHOD(is_empty) (TYPE(T, datum_t));

#endif