#include <libellul/type/array.h>

/* retourne une hashmap en adressage fermé vide de taille hashtable_size*/
T_MAP_INTERFACE T MAP_METHOD(new__)(int hashtable_size) {
  T hashtable = (T) malloc(sizeof(*hashtable));
  if (!hashtable) {
    printf("Error allocating hashtable\n");
    return NULL;
  }
  hashtable->count = 0;
  hashtable->length = hashtable_size;
  hashtable->buckets = (T_L *) malloc(sizeof(T_L) * hashtable_size);
  for (int i = hashtable->length - 1; i >= 0; i -= 1) {
    hashtable->buckets[i] = LIST_METHOD(new)();
  }
  return hashtable;
}

/* retourne une hashmap en adressage fermé vide */
T_MAP_INTERFACE T MAP_METHOD(new)(void){
  return MAP_METHOD(new__)(HASHTABLE_SIZE);
}

/* retourne le nombre de couples à l'intérieur de la hashmap */
T_MAP_INTERFACE size_t MAP_METHOD(length)(T hashtable) {
  if (!hashtable) {
    return 0;
  }
  return hashtable->count;
}

/* supprime la hashmap */
T_MAP_INTERFACE void MAP_METHOD(delete)(T *hashtable) {
  if (!hashtable || !*hashtable) {
    return;
  }
  for (int i = (*hashtable)->length - 1; i >= 0; i -= 1) {
    (*hashtable)->buckets[i] = LIST_METHOD(delete)(((*hashtable)->buckets)[i]);
  }
  free((*hashtable)->buckets);
  free(*hashtable);
  *hashtable = NULL;
}

/* retourne 1 si la hashmap contient la clé et 0 sinon */
T_MAP_INTERFACE int MAP_METHOD(contains)(T hashtable, T_MAP_KEY key) {
  if (!hashtable || !hashtable->buckets)
    return 0;
  COUPLE_TYPE couple_exemple;
  couple_exemple.key = key;
  int hash_code = HASH(key)%(hashtable->length);
  int contains = LIST_METHOD(contains)(hashtable->buckets[hash_code], couple_exemple);
  if (contains >= 0)
    return 1;
  else
    return 0;
}

/* Supprime le couple de clé key s'il existe et ne fait rien sinon */
T_MAP_INTERFACE int MAP_METHOD(remove)(T *hashtable, T_MAP_KEY key) {
  if (!hashtable || !(*hashtable) || !((*hashtable)->buckets))
    return -1;
  COUPLE_TYPE couple_exemple;
  couple_exemple.key = key;
  int hash_code = HASH(key)%((*hashtable)->length);
  (*hashtable)->buckets[hash_code] = LIST_METHOD(remove)(couple_exemple, (*hashtable)->buckets[hash_code]);
  (*hashtable)->count--;
  return 0;
}

/* Rajoute le couple de clé key et de valeur value dans la hashmap */
T_MAP_INTERFACE int MAP_METHOD(put)(T *hashtable, T_MAP_KEY key, T_MAP_VALUE value) {
  /* on vérifie qu'on a accès à la table */
  if (!hashtable || !*hashtable)
    return -1;
  /* on crée le couple à ajouter */
  COUPLE_TYPE new_couple;
  new_couple.key = key;
  #if !defined(T_SET_ELEMENT)
  new_couple.value = value;
  #endif
  /* on vérifie le load factor avant d'ajouter */
  float current_load_factor = (float)(*hashtable)->count / (float)(*hashtable)->length;
  if (current_load_factor < LOAD_FACTOR) {
    int hash_code = HASH(key)%((*hashtable)->length);
    (*hashtable)->buckets[hash_code] = LIST_METHOD(push)(new_couple, (*hashtable)->buckets[hash_code]);
  } else {
    /* on doit redimensionner la table */
    T new_hashtable = MAP_METHOD(new__)((*hashtable)->length * 2);
    /* on réinsère tous les anciens éléments */
    COUPLE_TYPE old_couple;
    for (size_t i = 0; i < (*hashtable)->length; i++) {
      T_L old_list = (*hashtable)->buckets[i];
      size_t old_list_length = LIST_METHOD(length)(old_list);
      for (size_t j = 0; j < old_list_length; j++) {
        LIST_METHOD(pop)(&old_couple, old_list);
        MAP_METHOD(put)(&new_hashtable, old_couple.key, old_couple.value);
      }
    }
    MAP_METHOD(delete)(hashtable);
    *hashtable = new_hashtable;
    /* on ajoute le nouveau couple */
    int hash_code = HASH(key)%((*hashtable)->length);
    (*hashtable)->buckets[hash_code] = LIST_METHOD(push)(new_couple, (*hashtable)->buckets[hash_code]);
  }
  (*hashtable)->count++;
  return 0;
}

/* Récupère la valeur associée à la clé key dans la hashmap */
T_MAP_INTERFACE int MAP_METHOD(get)(T hashtable, T_MAP_KEY key, T_MAP_VALUE *value) {
  if (!hashtable || !hashtable->buckets)
    return -1;
  int hash_code = HASH(key)%(hashtable->length);
  COUPLE_TYPE saved_couple;
  int index = LIST_METHOD(contains)(hashtable->buckets[hash_code], (COUPLE_TYPE){.key = key});
  if (index < 0) {
    return -1;
  }
  saved_couple = LIST_METHOD(get)(hashtable->buckets[hash_code], index);
#if !defined(T_SET_ELEMENT)
  *value = saved_couple.value;
#endif
  return 0;
}

T_MAP_INTERFACE void MAP_METHOD(print)(T hashtable) {
  if (!hashtable) {
    printf("NULL hashtable\n");
    return;
  }
  printf("Hashtable with %zu elements:\n", hashtable->count);
  for (size_t i = 0; i < hashtable->length; i++) {
    printf("Bucket %d: ", i);
    LIST_METHOD(print)(hashtable->buckets[i]);
  }
}

#undef T
#undef T_MAP_KEY
#undef T_MAP_VALUE
#undef map_datum_t