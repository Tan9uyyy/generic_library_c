/* All list implementations must provide these functions: */
/* Retourne une list vide */
T_LIST_INTERFACE T              LIST_METHOD(new) (void);
/* Retourne 1 si la list est vide, 0 sinon */
T_LIST_INTERFACE int            LIST_METHOD(is_empty) (T list);
/* Retourne le nombre d'elements dans la list */
T_LIST_INTERFACE int            LIST_METHOD(length) (T list);
/* Retourne l'element nnoindex de la list */
T_LIST_INTERFACE list_datum_t   LIST_METHOD(get) (T list, int index);
/* Insere l'element a la place nnoindex de la list et retourne la nouvelle list */
T_LIST_INTERFACE T              LIST_METHOD(set) (list_datum_t value, T list, int index);
/* Insere l'element a la fin de la list et retourne la nouvelle list */
T_LIST_INTERFACE T              LIST_METHOD(push) (list_datum_t value, T list);
/* Retire le dernier element de la list, le stocke dans value et retourne la nouvelle list */
T_LIST_INTERFACE T              LIST_METHOD(pop) (list_datum_t *value, T list);
/* Retourne l'index de la value si la list contient obj, -1 sinon */
T_LIST_INTERFACE int            LIST_METHOD(contains) (T list, list_datum_t value);
/* Retire l'element obj de la list et retourne la nouvelle list */
T_LIST_INTERFACE T              LIST_METHOD(remove) (list_datum_t value, T list);
/* Supprime la list proprement en utilisant le destructeur sur chaque element */
T_LIST_INTERFACE void           LIST_METHOD(delete) (T list);
/* Affiche la list en utilisant la fonction printer pour chaque element */
T_LIST_INTERFACE void           LIST_METHOD(print) (T list);