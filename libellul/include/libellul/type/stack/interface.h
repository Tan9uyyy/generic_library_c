/* All stack implementations must provide these functions: */
/* Retourne une stack vide */
T_STACK_INTERFACE T             STACK_METHOD(new) (void);
/* Retourne 1 si la stack est vide, 0 sinon */
T_STACK_INTERFACE int           STACK_METHOD(is_empty) (T stack);
/* Retourne le nombre d'éléments dans la stack */
T_STACK_INTERFACE int           STACK_METHOD(length) (T stack);
/* Retourne le premier élément de la stack */
T_STACK_INTERFACE stack_datum_t STACK_METHOD(first) (T stack);
/* Insère l'élément à la fin de la stack et retourne la nouvelle stack */
T_STACK_INTERFACE T             STACK_METHOD(push) (stack_datum_t value, T stack);
/* Retire le premier élément de la stack, le stocke dans value et retourne la nouvelle stack */
T_STACK_INTERFACE T             STACK_METHOD(pop) (stack_datum_t *value, T stack);
/* Supprime la stack proprement en utilisant le destructeur sur chaque élément */
T_STACK_INTERFACE T             STACK_METHOD(delete) (T stack);
/* Affiche la stack en utilisant la fonction printer pour chaque élément */
T_STACK_INTERFACE void          STACK_METHOD(print) (T stack);