T_MAP_INTERFACE T MAP_METHOD( new )( void ) {
    T hashtable = (T) malloc(sizeof(*hashtable));
    if (!hashtable) {
        printf("Error allocating memory for hashtable\n");
        return NULL;
    }
    hashtable->length = 0;
#if !defined ( T_IMPL_HASHTABLE_LINEAR_NO_TOMBSTONES )
    hashtable->tombstones = 0;
#endif
    T_MAP_KEY *bucket = (T_MAP_KEY *) array(T_MAP_KEY);
    hashtable->bucket = bucket;
#if !defined ( T_SET_ELEMENT )
    T_MAP_VALUE *value = (T_MAP_VALUE *) array(T_MAP_VALUE);
    hashtable->value = value;
#endif
    return hashtable;
}

T_MAP_INTERFACE size_t MAP_METHOD( length )( T hashtable ) {
  return hashtable->length;
}

T_MAP_INTERFACE void   MAP_METHOD( delete )( T *hashtable ) {
    if (!hashtable || !*hashtable) {
        return;
    }
    array_delete(&((*hashtable)->bucket));
#if !defined ( T_SET_ELEMENT )
    array_delete(&((*hashtable)->value));
#endif
    free(*hashtable);
}

/* retourne l'index dans la table de la key */
T_MAP_INTERFACE int    MAP_METHOD( contains )( T hashtable, T_MAP_KEY key ) {
    if (!hashtable) {
        return -1;
    }
    int hash_code = HASH(key) % array_length(hashtable->bucket);
    for (size_t i = 0; i < array_length(hashtable->bucket); i++) {
        if (KEY_COMPARATOR(hashtable->bucket[i], key)) {
            return 1;
        }
    }
    return 0;
}

T_MAP_INTERFACE int    MAP_METHOD( remove )( T *hashtable, T_MAP_KEY key ) {

}

#if defined( T_SET_ELEMENT )
T_MAP_INTERFACE int    MAP_METHOD( insert )( T *set, T_SET_ELEMENT element ) {

}
#else
T_MAP_INTERFACE int    MAP_METHOD( put )( T *hashtable, T_MAP_KEY key, T_MAP_VALUE value ) {

}

T_MAP_INTERFACE int    MAP_METHOD( get )( T hashtable, T_MAP_KEY key, T_MAP_VALUE *value ) {

}
#endif