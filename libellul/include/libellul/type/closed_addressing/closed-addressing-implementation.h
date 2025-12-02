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
int couple_comparator(COUPLE_TYPE couple1, COUPLE_TYPE couple2) {
  return COMPARATOR(couple1.key, couple2.key);
}

/* Destructeur de couple utilisant le destructeur des valeurs */
void couple_destructor(COUPLE_TYPE couple) {
#if !defined(T_SET_ELEMENT)
  void *dest_result = DESTRUCTOR(couple.value);
  if (dest_result != NULL) {
    /* DESTRUCTOR a fait quelque chose */
  }
#endif
  /* Note: on ne peut pas free couple car c'est une valeur passée par copie */
}

/* retourne une hashmap en adressage fermé vide */
T_MAP_INTERFACE T MAP_METHOD(new)(void) {
  T hashtable = malloc(sizeof(*hashtable));
  hashtable->buckets = (T_L *)array(T_L);
  hashtable->count = 0;
  return hashtable;
}

/* retourne le nombre de couples à l'intérieur de la hashmap */
T_MAP_INTERFACE size_t MAP_METHOD(length)(T hashtable) {
  return hashtable->count;
}

/* supprime la hashmap */
T_MAP_INTERFACE void MAP_METHOD(delete)(T *hashtable) {
  if (!hashtable || !*hashtable)
    return;
  for (int i = MAP_METHOD(length)(*hashtable) - 1; i >= 0; i -= 1) {
    METHOD(list, list_datum_t, delete)((T_L *)((*hashtable)->buckets[i]),
                                       couple_destructor);
  }
  array_delete(*hashtable);
  *hashtable = NULL;
}

/* retourne 1 si la hashmap contient la clé et 0 sinon */
T_MAP_INTERFACE int MAP_METHOD(contains)(T hashtable, T_MAP_KEY key) {
  COUPLE_TYPE couple_exemple;
  couple_exemple.key = key;
  int hash_code = HASH(key);
  int contains = (METHOD(list, list_datum_t, contains)(
      (T_L *)hashtable->buckets[hash_code], couple_exemple, couple_comparator));
  return contains;
}

/* Supprime le couple de clé key s'il existe et ne fait rien sinon */
T_MAP_INTERFACE int MAP_METHOD(remove)(T *hashtable, T_MAP_KEY key) {
  if (!hashtable || !*hashtable)
    return -1;
  COUPLE_TYPE couple_exemple;
  couple_exemple.key = key;
  int hash_code = HASH(key);
  METHOD(list, list_datum_t, remove)(couple_exemple,
                                     (T_L *)(*hashtable)->buckets[hash_code],
                                     couple_comparator, couple_destructor);
  return 0;
}

/* Rajoute le couple de clé key et de valeur value dans la hashmap */
T_MAP_INTERFACE int MAP_METHOD(put)(T *hashtable, T_MAP_KEY key,
                                    T_MAP_VALUE value) {
  if (!hashtable || !*hashtable)
    return -1;
  return 0;
}

/* Récupère la valeur associée à la clé key dans la hashmap */
T_MAP_INTERFACE int MAP_METHOD(get)(T hashtable, T_MAP_KEY key,
                                    T_MAP_VALUE *value) {
  return 0;
}

#undef T
#undef T_MAP_KEY
#undef T_MAP_VALUE
#undef map_datum_t