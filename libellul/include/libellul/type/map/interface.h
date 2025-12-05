/* All map implementations must provide these functions: */
/* retourne une map vide */
T_MAP_INTERFACE T MAP_METHOD(new)(void);
/* retourne le nombre de couples à l'intérieur de la map */
T_MAP_INTERFACE size_t MAP_METHOD(length)(T map);
/* supprime la map passée en paramètre (la libère proprement) */
T_MAP_INTERFACE void MAP_METHOD(delete)(T *map);
/* renvoie 1 si la map contient la clé, 0 sinon*/
T_MAP_INTERFACE int MAP_METHOD(contains)(T map, T_MAP_KEY key);
/* Supprime le couple de clé key dans la map */
T_MAP_INTERFACE int MAP_METHOD(remove)(T *map, T_MAP_KEY key);

#if defined(T_SET_ELEMENT)
T_MAP_INTERFACE int MAP_METHOD(insert)(T *set, T_SET_ELEMENT element);
#define T_HAS_COMPARATOR
T_MAP_INTERFACE int MAP_METHOD(compare)(void *_set1, void *_set2);
#else
/* Rajoute le couple key,value dans la map */
T_MAP_INTERFACE int MAP_METHOD(put)(T *map, T_MAP_KEY key, T_MAP_VALUE value);
/* Stocke la valeur de value de la clé si le couple est bien dans la map */
T_MAP_INTERFACE int MAP_METHOD(get)(T map, T_MAP_KEY key, T_MAP_VALUE *value);
/* Affiche la map */
T_MAP_INTERFACE void MAP_METHOD(print)(T map);
#endif

/* Automatically constructed by type/map/epilogue.h: */
T_MAP_INTERFACE int MAP_METHOD(is_empty)(T map);

/* Iterator interface */
typedef struct MAP_METHOD(iterator) * MAP_METHOD(iterator_t);

T_MAP_INTERFACE MAP_METHOD(iterator_t) MAP_METHOD(iterator_new)(T map);
T_MAP_INTERFACE int MAP_METHOD(iterator_has_next)(MAP_METHOD(iterator_t) it);
T_MAP_INTERFACE T_MAP_KEY MAP_METHOD(iterator_next)(MAP_METHOD(iterator_t) it);
T_MAP_INTERFACE void MAP_METHOD(iterator_delete)(MAP_METHOD(iterator_t) * it);
