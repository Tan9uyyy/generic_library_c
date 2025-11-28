#ifndef _QUEUE_H__
#define _QUEUE_H__

#ifdef queue_datum_t
    #include "queue/queue-export-def.h"
    #undef queue_datum_t
#endif

#define queue_datum_t int
#include "queue/queue-export-def.h"

#endif