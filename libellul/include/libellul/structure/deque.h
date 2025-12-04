/**
 * Deque.
 *
 * Variants:
 * T_IMPL_HASHTABLE_LINEAR_NO_TOMBSTONES: Use backward-shifting deletion.
 *
 */

//#if defined( T_LIST_EXPORT_DEFS ) || !defined( T_LIST_EXPORT_CODE )

typedef struct TYPE(node, deque_datum_t) {
  struct TYPE(node, deque_datum_t) * next;
  struct TYPE(node, deque_datum_t) * prev;
  deque_datum_t datum;
} TYPE(node, deque_datum_t);

typedef struct {
  struct TYPE(node, deque_datum_t) * head;
  struct TYPE(node, deque_datum_t) * queue;
  int length;
} *T;

//#endif
#ifdef T_DEQUE
#define DEQUE_METHOD( name ) GEN_SYM( T_DEQUE_TAG, name )
#elif defined( T_QUEUE_IMPL_DEQUE )
#include <libellul/type/queue/interface.h>
#elif defined( T_STACK_IMPL_DEQUE )
#include <libellul/type/stack/interface.h>
#elif defined( T_LIST_IMPL_DEQUE )
#include <libellul/type/list/list-export-def.h>
#elif defined(T_PQ_IMPL_DEQUE)
#include <libellul/type/priority-queue/interface.h>
#else
#error "Deque must implemente a abstract data type!"
#endif

//#if !defined( T_LIST_EXPORT_DEFS )
/* Code templating for the actual implementation starts here */

#include <libellul/memory.h>
#include <libellul/type/array.h>

/* on inclut deque afin de pouvoir créer les fonctions queue/list/stack grâce aux fonctions deque */
#include <libellul/structure/deque/deque-implementation.h>
/* on crée nos fonctions queue/list/stack */
#ifdef T_DEQUE
#elif defined (T_QUEUE_IMPL_DEQUE)
#include <libellul/type/queue/queue-implementation.h>
#elif defined( T_STACK_IMPL_DEQUE )
#include <libellul/type/stack/stack-implementation.h>
#elif defined( T_LIST_IMPL_DEQUE )
#include <libellul/type/list/list-implementation.h>
#elif defined( T_PQ_IMPL_DEQUE )
#include <libellul/type/priority-queue/priority-queue-implementation.h>
#else
#error "Deque must implemente a abstract data type!"
#endif

//#endif

#undef T_IMPL_DEQUE
