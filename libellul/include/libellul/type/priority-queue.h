/*
 * 'pq' abstract data type.
 *
 * Available type implementations:
 *
 * T_IMPL_DEQUE (default)
 * ...
 *
 */

#ifndef T_PQ_TAG
#error "Undefined T_PQ_TAG"
#endif

#ifndef pq_datum_t
#error "Undefined pq datum type !"
#endif

#include <libellul/type/prologue.h>

#if !defined(T_PQ_EXPORT_DEFS) && !defined(T_PQ_EXPORT_CODE)
#define T_PQ_INTERFACE static inline
#else
#define T_PQ_INTERFACE extern
#endif

#ifndef T
#define T GEN_SYM(T_PQ_TAG, t)
#define T_FLAG
#endif
#define PQ_METHOD(name) GEN_SYM(T_PQ_TAG, name)

#define T_PQ_IMPL_DEQUE

typedef struct pq_couple {
  pq_datum_t value;
  int priority;
} pq_couple;

#define deque_datum_t pq_couple
#define T_DEQUE_TAG GEN_SYM(deque_datum_t, deque)
#define DEQUE_METHOD(name) GEN_SYM(T_DEQUE_TAG, name)

#define DESTRUCTOR(val) NULL
#define COMPARATOR(val1, val2) (val1.value - val2.value)
#ifndef PQ_PRINTER
#error "Undefined PQ_PRINTER function!"
#endif
#define PRINTER(val)                                                           \
  (printf("(%d, ", val.priority), PQ_PRINTER(val.value), printf(")"))

#include <libellul/structure/deque.h>

#define T_INTERFACE T_TREESET_INTERFACE
#if defined(T_PQ_EXPORT_DEFS)
#define T_EXPORT_DEFS
#endif

#undef T_PQ_IMPL_DEQUE
#undef T_PQ_TAG
#undef T_PQ_INTERFACE
#undef T_PQ_EXPORT_DEFS
#undef T_PQ_EXPORT_CODE
#ifdef T_FLAG
#undef T
#undef T_FLAG
#endif
#undef PQ_METHOD
