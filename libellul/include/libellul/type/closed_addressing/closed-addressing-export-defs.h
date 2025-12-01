#include "../../structure/hashtable/closed_addressing.h"

// typedef TYPE(map, map_datum_t) TYPE(T, map_datum_t);

#ifdef T
#undef T
#endif
#define T closed_addressing_hashtable

/* retourne une hashmap en adressage fermé vide */
T *METHOD(T, map_datum_t, new)(void);
/* retourne le nombre de couples à l'intérieur de la hashmap */
size_t METHOD(T, map_datum_t, length)(T *hashtable);
/* supprime la hashmap */
void METHOD(T, map_datum_t, delete)(T **hashtable);
/* retourne 1 si la hashmap contient la clé et 0 sinon */
int METHOD(T, map_datum_t, contains)(T *hashtable, T_MAP_KEY key, (int)(*comparator)(T_MAP_KEY, T_MAP_KEY));
/* Supprime le couple de clé key s'il existe et ne fait rien sinon */
void METHOD(T, map_datum_t, remove)(T *hashtable, T_MAP_KEY key);
/* Rajoute le couple de clé key et de valeur value dans la hashmap */
int METHOD(T, map_datum_t, put)(T *hashtable, T_MAP_KEY key, T_MAP_VALUE value);
/* Récupère la valeur associée à la clé key dans la hashmap */
int METHOD(T, map_datum_t, get)(T *hashtable, T_MAP_KEY key, T_MAP_VALUE *value);
/* retourne 1 si la hashmap est vide et 0 sinon */
int METHOD(T, map_datum_t, isEmpty)(T *hashtable);