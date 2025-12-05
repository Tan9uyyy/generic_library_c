/*
 * 'map' abstract data type.
 *
 * Available type implementations:
 *
 * T_IMPL_HASHTABLE (default)
 * T_IMPL_HASHTRIE
 * T_IMPL_TREAP
 * ...
 *
 * Type options:
 *
 * T_SET_ELEMENT <type>: The 'map' actually implements a 'set' of <type>'s.
 *
 */

#include <libellul/type/prologue.h>

/* on vérifie que tout ce qu'on a besoin est bien défini */
#ifndef HASH
#error "Undefined hash function!"
#endif
#ifndef KEY_COMPARATOR
#error "Undefined key_comparator function!"
#endif
#ifndef VALUE_DESTRUCTOR
#error "Undefined key_destructor function!"
#endif
#ifndef KEY_PRINTER
#error "Undefined key_printer function!"
#endif
#ifndef VALUE_PRINTER
#error "Undefined key_printer function!"
#endif

#if !defined(T_MAP_KEY)
#error "Undefined T_MAP_KEY"
#endif

#if !defined(T_MAP_VALUE) && !defined(T_SET_ELEMENT)
#error "Undefined T_MAP_VALUE"
#endif

#if (!defined(T_MAP_TAG) && !defined(T_SET_ELEMENT))
#define T_MAP_TAG GEN_SYM(T_MAP_KEY, GEN_SYM(T_MAP_VALUE, map))
#endif

/* On définit le type de la map en fonction du type des clés et des
 * valeurs */
#ifdef map_datum_t
#undef map_datum_t
#endif
#if !defined(T_SET_ELEMENT)
#define map_datum_t GEN_SYM(T_MAP_KEY, T_MAP_VALUE)
#else
#define map_datum_t T_MAP_KEY
#endif

#if !defined(T_MAP_EXPORT_DEFS) && !defined(T_MAP_EXPORT_CODE)
#define T_MAP_INTERFACE static inline
#else
#define T_MAP_INTERFACE extern
#endif

#ifdef T
#undef T
#endif
#define T GEN_SYM(T_MAP_TAG, t)
#define T_MAP GEN_SYM(T_MAP_TAG, t)
#define MAP_METHOD(name) GEN_SYM(T_MAP_TAG, name)

#if defined(T_IMPL_HASHTABLE)
#include <libellul/structure/hashtable/hashtable.h>
#elif defined(T_IMPL_HASHTRIE)
#include <libellul/structure/hashtrie.h>
#else /* Default data structure for a map is a hashtable */
#include <libellul/structure/hashtable/hashtable.h>
#endif

#if defined(T_SET_ELEMENT)
T_MAP_INTERFACE T MAP_METHOD(union)(T set1, T set2);
T_MAP_INTERFACE T MAP_METHOD(inter)(T set1, T set2);
T_MAP_INTERFACE T MAP_METHOD(diff)(T set1, T set2);
T_MAP_INTERFACE T MAP_METHOD(symdiff)(T set1, T set2);

#if !defined(T_MAP_EXPORT_DEFS)
/* A 'set' is built on top of the 'map' interface */
T_MAP_INTERFACE T MAP_METHOD(union)(T set1, T set2) {
  T new_set = MAP_METHOD(new)();

  MAP_METHOD(iterator_t) it = MAP_METHOD(iterator_new)(set1);
  // printf("Union: iterator 1 created\n");
  while (MAP_METHOD(iterator_has_next)(it)) {
    T_MAP_KEY key = MAP_METHOD(iterator_next)(it);
    MAP_METHOD(insert)(&new_set, key);
  }
  MAP_METHOD(iterator_delete)(&it);

  it = MAP_METHOD(iterator_new)(set2);
  while (MAP_METHOD(iterator_has_next)(it)) {
    T_MAP_KEY key = MAP_METHOD(iterator_next)(it);
    MAP_METHOD(insert)(&new_set, key);
  }
  MAP_METHOD(iterator_delete)(&it);

  return new_set;
}

T_MAP_INTERFACE T MAP_METHOD(inter)(T set1, T set2) {
  T new_set = MAP_METHOD(new)();

  MAP_METHOD(iterator_t) it = MAP_METHOD(iterator_new)(set1);
  while (MAP_METHOD(iterator_has_next)(it)) {
    T_MAP_KEY key = MAP_METHOD(iterator_next)(it);
    if (MAP_METHOD(contains)(set2, key)) {
      MAP_METHOD(insert)(&new_set, key);
    }
  }
  MAP_METHOD(iterator_delete)(&it);

  return new_set;
}

T_MAP_INTERFACE T MAP_METHOD(diff)(T set1, T set2) {
  T new_set = MAP_METHOD(new)();

  MAP_METHOD(iterator_t) it = MAP_METHOD(iterator_new)(set1);
  while (MAP_METHOD(iterator_has_next)(it)) {
    T_MAP_KEY key = MAP_METHOD(iterator_next)(it);
    if (!MAP_METHOD(contains)(set2, key)) {
      MAP_METHOD(insert)(&new_set, key);
    }
  }
  MAP_METHOD(iterator_delete)(&it);

  return new_set;
}

T_MAP_INTERFACE T MAP_METHOD(symdiff)(T set1, T set2) {
  T new_set = MAP_METHOD(new)();

  MAP_METHOD(iterator_t) it = MAP_METHOD(iterator_new)(set1);
  while (MAP_METHOD(iterator_has_next)(it)) {
    T_MAP_KEY key = MAP_METHOD(iterator_next)(it);
    if (!MAP_METHOD(contains)(set2, key)) {
      MAP_METHOD(insert)(&new_set, key);
    }
  }
  MAP_METHOD(iterator_delete)(&it);

  it = MAP_METHOD(iterator_new)(set2);
  while (MAP_METHOD(iterator_has_next)(it)) {
    T_MAP_KEY key = MAP_METHOD(iterator_next)(it);
    if (!MAP_METHOD(contains)(set1, key)) {
      MAP_METHOD(insert)(&new_set, key);
    }
  }
  MAP_METHOD(iterator_delete)(&it);

  return new_set;
}

T_MAP_INTERFACE int MAP_METHOD(compare)(void *_set1, void *_set2) {
  T *set1 = _set1;
  T *set2 = _set2;

  if (MAP_METHOD(length)(*set1) != MAP_METHOD(length)(*set2)) {
    return 1;
  }

  MAP_METHOD(iterator_t) it = MAP_METHOD(iterator_new)(*set1);
  while (MAP_METHOD(iterator_has_next)(it)) {
    T_MAP_KEY key = MAP_METHOD(iterator_next)(it);
    if (!MAP_METHOD(contains)(*set2, key)) {
      MAP_METHOD(iterator_delete)(&it);
      return 1;
    }
  }
  MAP_METHOD(iterator_delete)(&it);

  return 0;
}

#endif /* End of 'set' implementation */
#endif /* End of 'set' specialization  */

#undef T_INTERFACE
#define T_INTERFACE T_MAP_INTERFACE
#undef METHOD
#define METHOD MAP_METHOD
#if defined(T_MAP_EXPORT_DEFS)
#define T_EXPORT_DEFS
#endif

#if !defined(T)
#define T GEN_SYM(T_MAP_TAG, t)
#endif

#include <libellul/type/epilogue.h>

#ifdef LOAD_FACTOR
#undef LOAD_FACTOR
#endif
#undef T_MAP_KEY
#undef T_MAP_VALUE
#undef T_MAP_TAG
#undef T_MAP_INTERFACE
#undef T_MAP_EXPORT_DEFS
#undef T_MAP_EXPORT_CODE
#undef T_MAP
#undef MAP_METHOD
