#include "closed-addressing-export-defs.h"

/*il y a surement un autre endroit ou mettre ça plus intelligemment*/
#ifndef HASH
#error "Undefined hash function!"
#endif

#include "../array.h"

int comparator_couple(COUPLE_TYPE couple1, COUPLE_TYPE couple2) {
  return couple1.key == couple2.key;
}

T *METHOD(T, map_datum_t, new)(void) { 
  T *hashtable = malloc(sizeof(T));
  hashtable->buckets = (T_L *) array(T_L);
  hashtable->count = 0;
  return hashtable;
}

size_t METHOD(T, map_datum_t, length)(T *hashtable) {
  // size_t compteur = 0;
  // for (int i = array_size(hashtable) - 1; i >= 0; i -= 1) {
  //   compteur += METHOD(list, map_datum_t, length)(((T_L *)hashtable)[i]);
  // } ancienne version
  return hashtable->count;
}

void METHOD(T, map_datum_t, delete)(T **hashtable) { 
  for(int i = METHOD(T, map_datum_t, length)(*hashtable) - 1; i >= 0; i -= 1){
    METHOD(list, list_datum_t, delete)((T_L *)((*hashtable)->buckets[i]), free);
  }
  array_delete(hashtable);
}

int METHOD(T, map_datum_t, contains)(T *hashtable, T_MAP_KEY key, (int)(*comparator)(T_MAP_KEY, T_MAP_KEY)) {
  int hash_code = HASH(key);
  return (METHOD(list, list_datum_t, contains)((T_L *)hashtable[hash_code], key, comparator));
}

void METHOD(T, map_datum_t, remove)(T *hashtable, T_MAP_KEY key) {
  int hash_code = HASH(key);
  METHOD(list, list_datum_t, remove)(key, (T_L *)hashtable[hash_code], comparator_couple, NULL);
  return void;
}

int METHOD(T, map_datum_t, put)(T *hashtable, T_MAP_KEY key, T_MAP_VALUE value) {
  return 0;
}

int METHOD(T, map_datum_t, get)(T *hashtable, T_MAP_KEY key, T_MAP_VALUE *value) {
  return 0;
}

int METHOD(T, map_datum_t, isEmpty)(T *hashtable) { return 0; }

#undef T
#undef T_MAP_KEY
#undef T_MAP_VALUE
#undef map_datum_t