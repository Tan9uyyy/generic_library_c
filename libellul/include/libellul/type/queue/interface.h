/* All queue implementations must provide these functions: */
/* Retourne une queue vide */
T_QUEUE_INTERFACE T             QUEUE_METHOD(new) (void);
/* Retourne 1 si la queue est vide, 0 sinon */
T_QUEUE_INTERFACE int           QUEUE_METHOD(is_empty) (T queue);
/* Retourne le nombre d'éléments dans la queue */
T_QUEUE_INTERFACE int           QUEUE_METHOD(length) (T queue);
/* Retourne le premier élément de la queue */
T_QUEUE_INTERFACE queue_datum_t QUEUE_METHOD(first) (T queue);
/* Insère l'élément à la fin de la queue et retourne la nouvelle queue */
T_QUEUE_INTERFACE T             QUEUE_METHOD(push) (queue_datum_t value, T queue);
/* Retire le premier élément de la queue, le stocke dans value et retourne la nouvelle queue */
T_QUEUE_INTERFACE T             QUEUE_METHOD(pop) (queue_datum_t *value, T queue);
/* Supprime la queue proprement en utilisant le destructeur sur chaque élément */
T_QUEUE_INTERFACE void          QUEUE_METHOD(delete) (T queue);
/* Affiche la queue en utilisant la fonction printer pour chaque élément */
T_QUEUE_INTERFACE void          QUEUE_METHOD(print) (T queue);