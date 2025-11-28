#include <../include/libellul/type/queue.h>

#ifdef queue_datum_t
    #include <../include/libellul/type/queue/queue-implementation.h>
    #undef queue_datum_t
#endif

#define queue_datum_t int
#include <../include/libellul/type/queue/queue-implementation.h>