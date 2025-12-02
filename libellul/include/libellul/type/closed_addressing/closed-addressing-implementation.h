/*il y a surement un autre endroit ou mettre ça plus intelligemment*/
#ifndef HASH
#error "Undefined hash function!"
#endif
#ifndef COMPARATOR
#error "Undefined comparator function!"
#endif
#ifndef DESTRUCTOR
#error "Undefined destructor function!"
#endif

#include "../array.h"

/* Comparateur de couple utilisant le comparateur des clés */
int couple_comparator(COUPLE_TYPE *couple1, COUPLE_TYPE *couple2) {
  return COMPARATOR(couple1->key, couple2->key);
}

/* Destructeur de couple utilisant le destructeur des valeurs */
void couple_destructor(COUPLE_TYPE *couple) {
#if !defined( T_SET_ELEMENT )
  if(DESTRUCTOR != NULL){
    DESTRUCTOR(couple.value);
  }
  free(couple);
#endif
}

/* retourne une hashmap en adressage fermé vide */
T_MAP_INTERFACE T MAP_METHOD(T, map_datum_t, new)(void) { 
  T hashtable = malloc(sizeof(*T));
  hashtable->buckets = (T_L *) array(T_L);
  hashtable->count = 0;
  return hashtable;
}

/* retourne le nombre de couples à l'intérieur de la hashmap */
T_MAP_INTERFACE size_t MAP_METHOD(T, map_datum_t, length)(T hashtable) {
  return hashtable->count;
}

/* supprime la hashmap */
T_MAP_INTERFACE void MAP_METHOD(T, map_datum_t, delete)(T *hashtable) { 
  for(int i = MAP_METHOD(T, map_datum_t, length)(hashtable) - 1; i >= 0; i -= 1){
    METHOD(list, list_datum_t, delete)((T_L *)((hashtable)->buckets[i]), free);
  }
  array_delete(hashtable);
}

/* retourne 1 si la hashmap contient la clé et 0 sinon */
T_MAP_INTERFACE int MAP_METHOD(T, map_datum_t, contains)(T hashtable, T_MAP_KEY key) {
  COUPLE_TYPE *couple_exemple = (COUPLE_TYPE *)(sizeof(COUPLE_TYPE));
  couple_exemple->key = key;
  int hash_code = HASH(key);
  return (METHOD(list, list_datum_t, contains)((T_L *)hashtable[hash_code], couple_exemple, couple_comparator));
}

/* Supprime le couple de clé key s'il existe et ne fait rien sinon */
T_MAP_INTERFACE void MAP_METHOD(T, map_datum_t, remove)(T hashtable, T_MAP_KEY key) {
  COUPLE_TYPE *couple_exemple = (COUPLE_TYPE *)(sizeof(COUPLE_TYPE));
  couple_exemple->key = key;
  int hash_code = HASH(key);
  METHOD(list, list_datum_t, remove)(couple_exemple, (T_L *)hashtable[hash_code], couple_comparator, couple_destructor);
  return void;
}

/* Rajoute le couple de clé key et de valeur value dans la hashmap */
T_MAP_INTERFACE int MAP_METHOD(T, map_datum_t, put)(T hashtable, T_MAP_KEY key, T_MAP_VALUE value) {
  return 0;
}

/* Récupère la valeur associée à la clé key dans la hashmap */
T_MAP_INTERFACE int MAP_METHOD(T, map_datum_t, get)(T hashtable, T_MAP_KEY key, T_MAP_VALUE *value) {
  return 0;
}

#undef T
#undef T_MAP_KEY
#undef T_MAP_VALUE
#undef map_datum_t