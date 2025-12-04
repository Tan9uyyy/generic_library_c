T_MAP_INTERFACE T MAP_METHOD(new__)(size_t size) {
  T hashtable = (T)malloc(sizeof(*hashtable));
  if (!hashtable) {
    printf("Error allocating memory for hashtable\n");
    return NULL;
  }
  hashtable->length = 0;
#if !defined(T_IMPL_HASHTABLE_LINEAR_NO_TOMBSTONES)
  hashtable->tombstones = 0;
#endif
  T_MAP_KEY *bucket = (T_MAP_KEY *)array_strict(size, T_MAP_KEY);
  hashtable->bucket = bucket;
  int *occupied = (int *)array_strict(size, int);
  for (size_t i = 0; i < size; i++) {
    occupied[i] = 0;
  }
  hashtable->occupied = occupied;
#if !defined(T_SET_ELEMENT)
  T_MAP_VALUE *value = (T_MAP_VALUE *)array_strict(size, T_MAP_VALUE);
  hashtable->value = value;
#endif
  return hashtable;
}

T_MAP_INTERFACE T MAP_METHOD(new)(void) {
  return MAP_METHOD(new__)(ARRAY_ALLOC_MIN);
}

T_MAP_INTERFACE size_t MAP_METHOD(length)(T hashtable) {
  if (!hashtable) {
    return 0;
  }
  return hashtable->length;
}

T_MAP_INTERFACE void MAP_METHOD(delete)(T *hashtable) {
  if (!hashtable || !*hashtable) {
    return;
  }
  array_delete(&((*hashtable)->bucket));
  array_delete(&((*hashtable)->occupied));
#if !defined(T_SET_ELEMENT)
  array_delete(&((*hashtable)->value));
#endif
  free(*hashtable);
  *hashtable = NULL;
  return;
}

/* retourne l'index dans la table de la key */
T_MAP_INTERFACE int MAP_METHOD(contains)(T hashtable, T_MAP_KEY key) {
  if (!hashtable) {
    return -1;
  }
  int hash_code = HASH(key) % array_size(hashtable->bucket);
  while (hashtable->occupied[hash_code] != 0) {
    if (hashtable->occupied[hash_code] == 1 &&
        KEY_COMPARATOR(hashtable->bucket[hash_code], key)) {
      return hash_code;
    }
    hash_code = (hash_code + 1) % array_size(hashtable->bucket);
  }
  return -1; /* key not found */
}

T_MAP_INTERFACE int MAP_METHOD(remove)(T *hashtable, T_MAP_KEY key) {
    if (!hashtable || !*hashtable) {
        return 0;
    }
    int index = MAP_METHOD(contains)(*hashtable, key);
    if (index < 0) {
        return 0; /* key not found */
    }
    /* Dépend de l'implémentation */
#if !defined(T_IMPL_HASHTABLE_LINEAR_NO_TOMBSTONES)
    (*hashtable)->occupied[index] = 2; /* mark as tombstone */
    (*hashtable)->tombstones++;
#elif defined(T_IMPL_HASHTABLE_LINEAR_NO_TOMBSTONES)
    /* Backward-shifting deletion */
    int next_index = (index + 1) % array_size((*hashtable)->bucket);
    while ((*hashtable)->occupied[next_index] == 1) {
        int ideal_pos = HASH((*hashtable)->bucket[next_index]) % array_size((*hashtable)->bucket);
        /* Check if the element at next_index can be shifted back to hash_code */
        if ((ideal_pos <= index && index < next_index) ||
            (index < next_index && next_index < ideal_pos) ||
            (next_index < ideal_pos && ideal_pos <= index)) {
            /* Shift element back */
            (*hashtable)->bucket[index] = (*hashtable)->bucket[next_index];
        #if !defined(T_SET_ELEMENT)
            (*hashtable)->value[index] = (*hashtable)->value[next_index];
        #endif
            (*hashtable)->occupied[index] = 1; /* mark as occupied */
            }
            index = next_index;
            next_index = (index + 1) % array_size((*hashtable)->bucket);
        }
    /* Finally mark the last shifted position as empty */
    (*hashtable)->occupied[index] = 0;
#else
#endif

  (*hashtable)->length--;
  return 1;
}

#if defined(T_SET_ELEMENT)
T_MAP_INTERFACE int MAP_METHOD(insert)(T *set, T_SET_ELEMENT element) {}
#else
/* Rajoute le couple key,value dans la map et renvoie son index */
T_MAP_INTERFACE int MAP_METHOD(put)(T *hashtable, T_MAP_KEY key, T_MAP_VALUE value) {
  if (!hashtable || !*hashtable) {
    return -1;
  }
  /* Check load factor and resize if necessary */
  float current_length = (float)(*hashtable)->length;
#if !defined ( T_IMPL_HASHTABLE_LINEAR_NO_TOMBSTONES )
  current_length += (float)(*hashtable)->tombstones;
#endif
  float current_load_factor = current_length / (float)array_size((*hashtable)->bucket);
  if (current_load_factor >= LOAD_FACTOR) {
    T new_hashtable = MAP_METHOD(new__)(array_size((*hashtable)->bucket) * ARRAY_ALLOC_GEOM);
    /* Reinsert all existing elements */
    for (size_t i = 0; i < array_size((*hashtable)->bucket); i++) {
      if ((*hashtable)->occupied[i] == 1) {
        MAP_METHOD(put)(&new_hashtable, (*hashtable)->bucket[i], (*hashtable)->value[i]);
      }
    }
    /* Delete old hashtable */
    MAP_METHOD(delete)(hashtable);
    *hashtable = new_hashtable;
  }
  /* Insert new element */
  int hash_code = HASH(key) % array_size((*hashtable)->bucket);
  while (((*hashtable)->occupied)[hash_code] != 0) {
    if ((*hashtable)->occupied[hash_code] == 1 &&
        KEY_COMPARATOR((*hashtable)->bucket[hash_code], key)) {
      /* Key already exists, update value */
#if !defined(T_SET_ELEMENT)
      (*hashtable)->value[hash_code] = value;
#endif
      return hash_code;
    }
    hash_code = (hash_code + 1) % array_size((*hashtable)->bucket);
  }
  /* Found an empty slot */
  (*hashtable)->bucket[hash_code] = key;
  (*hashtable)->occupied[hash_code] = 1; /* mark as occupied */
#if !defined(T_SET_ELEMENT)
  (*hashtable)->value[hash_code] = value;
#endif
  (*hashtable)->length++;
  return hash_code;
}

T_MAP_INTERFACE int MAP_METHOD(get)(T hashtable, T_MAP_KEY key, T_MAP_VALUE *value) {
  if (!hashtable) {
    return 0;
  }
  int index = MAP_METHOD(contains)(hashtable, key);
  if (index < 0) {
    return 0; /* key not found */
  } else {
#if !defined(T_SET_ELEMENT)
    *value = hashtable->value[index];
#endif
    return 1;
  }
}
#endif

T_MAP_INTERFACE void MAP_METHOD(print)(T hashtable) {
  if (!hashtable) {
    printf("Hashtable is NULL\n");
    return;
  }
  printf("Hashtable with %zu elements:\n", hashtable->length);
  for (size_t i = 0; i < array_size(hashtable->bucket); i++) {
    printf("---");
  }
  printf("\n");
  for (size_t i = 0; i < array_size(hashtable->bucket); i++) {
    printf("|");
    if (hashtable->occupied[i] == 0)
      printf("  ");
    if (hashtable->occupied[i] == 1)
      KEY_PRINTER(hashtable->bucket[i]);
    if (hashtable->occupied[i] == 2)
      printf("X");
  }
  printf("\n");
  for (size_t i = 0; i < array_size(hashtable->bucket); i++) {
    printf("---");
  }
  printf("\n");
  for (size_t i = 0; i < array_size(hashtable->bucket); i++) {
    printf("|");
    if (hashtable->occupied[i] == 0) {
        printf("  ");
    } else if (hashtable->occupied[i] == 1) {
        VALUE_PRINTER(hashtable->value[i]);
    } else printf("X");
  }
    printf("\n");
    for(size_t i = 0; i < array_size(hashtable->bucket); i++) {
      printf("---");
    }
    printf("\n");
}