#include <sys/types.h>

#ifndef key_t
    #error "Undefined key type!"
#endif

#ifndef value_t
    #error "Undefined value type!"
#endif

#include "../../generics.h"
#include "../../interface.h"

#undef datum_t
#define datum_t TYPE(couple, GEN_SYM(key_t, value_t))

typedef struct GEN_SYM(couple, GEN_SYM(key_t, value_t)) {
  key_t key;
  value_t value;
} datum_t;

#ifndef T
#define T hashtable
#endif

// typedef TYPE(map, datum_t) TYPE(T, datum_t);

void *METHOD(T, datum_t, new)(void);
size_t METHOD(T, datum_t, length)(void *hashtable);
void METHOD(T, datum_t, delete)(void *hashtable);
int METHOD(T, datum_t, contains)(void *hashtable, key_t key, (int)(*comparator)(key_t, key_t));
void METHOD(T, datum_t, remove)(void *hashtable, key_t key);
int METHOD(T, datum_t, put)(void *hashtable, key_t key, value_t value);
int METHOD(T, datum_t, get)(void *hashtable, key_t key, value_t *value);
int METHOD(T, datum_t, isEmpty)(void *hashtable);

#undef T
#undef key_t
#undef value_t
#undef datum_t