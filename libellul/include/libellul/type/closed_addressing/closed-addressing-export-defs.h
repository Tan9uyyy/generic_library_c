#include "../../structure/hashtable/closed_addressing.h"

#ifndef T
#define T closed_addressing_hashtable
#endif

// typedef TYPE(map, datum_t) TYPE(T, datum_t);

/* retourne une hashmap en adressage fermé vide */
T *METHOD(T, datum_t, new)(void);
/* retourne le nombre de couples à l'intérieur de la hashmap */
size_t METHOD(T, datum_t, length)(T *hashtable);
/* supprime la hashmap */
void METHOD(T, datum_t, delete)(T *hashtable);
/* retourne 1 si la hashmap contient la clé et 0 sinon */
int METHOD(T, datum_t, contains)(T *hashtable, T_MAP_KEY key, (int)(*comparator)(T_MAP_KEY, T_MAP_KEY));
/* Supprime le couple de clé key s'il existe et ne fait rien sinon */
void METHOD(T, datum_t, remove)(T *hashtable, T_MAP_KEY key);
/* Rajoute le couple de clé key et de valeur value dans la hashmap */
int METHOD(T, datum_t, put)(T *hashtable, T_MAP_KEY key, T_MAP_VALUE value);
/* Récupère la valeur associée à la clé key dans la hashmap */
int METHOD(T, datum_t, get)(T *hashtable, T_MAP_KEY key, T_MAP_VALUE *value);
/* retourne 1 si la hashmap est vide et 0 sinon */
int METHOD(T, datum_t, isEmpty)(T *hashtable);

#undef T
#undef T_MAP_KEY
#undef T_MAP_VALUE
#undef datum_t