/* Comparateur de couple utilisant le comparateur des clés */
int couple_comparator(COUPLE_TYPE couple1, COUPLE_TYPE couple2, int (*comparator)(T_MAP_KEY, T_MAP_KEY));
/* Destructeur de couple utilisant le destructeur des valeurs */
void couple_destructor(COUPLE_TYPE couple, void (*destructor)(T_MAP_VALUE));
/* retourne une hashmap en adressage fermé vide */
T_MAP_INTERFACE T METHOD(T, map_datum_t, new)(void);
/* retourne le nombre de couples à l'intérieur de la hashmap */
T_MAP_INTERFACE size_t METHOD(T, map_datum_t, length)(T hashtable);
/* supprime la hashmap */
T_MAP_INTERFACE void METHOD(T, map_datum_t, delete)(T *hashtable);
/* retourne 1 si la hashmap contient la clé et 0 sinon */
T_MAP_INTERFACE int METHOD(T, map_datum_t, contains)(T hashtable, T_MAP_KEY key, int (*comparator)(T_MAP_KEY, T_MAP_KEY));
#define MAP_METHOD( contains )( T map, T_MAP_KEY key ) MAP_METHOD( contains )( map, key, comparator )
/* Supprime le couple de clé key s'il existe et ne fait rien sinon */
T_MAP_INTERFACE void METHOD(T, map_datum_t, remove)(T hashtable, T_MAP_KEY key, int (*comparator)(T_MAP_KEY, T_MAP_KEY), void (*destructor)(T_MAP_VALUE));
#define MAP_METHOD( remove )( T *map, T_MAP_KEY key ) MAP_METHOD( remove )( map, key, comparator, destructor )
/* Rajoute le couple de clé key et de valeur value dans la hashmap */
T_MAP_INTERFACE int METHOD(T, map_datum_t, put)(T hashtable, T_MAP_KEY key, T_MAP_VALUE value);
/* Récupère la valeur associée à la clé key dans la hashmap */
T_MAP_INTERFACE int METHOD(T, map_datum_t, get)(T hashtable, T_MAP_KEY key, T_MAP_VALUE *value);