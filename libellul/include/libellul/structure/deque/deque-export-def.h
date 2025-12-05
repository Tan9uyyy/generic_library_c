#ifndef deque_datum_t
    #error "Undefined datum type !"
#endif

/* retourne une nouvelle queue vide */
T               DEQUE_METHOD(new)(void);
/* retourne 1 si deque est vide 0 sinon */
int             DEQUE_METHOD(is_empty)(T deque);
/* retourne la longueur de la deque */
int             DEQUE_METHOD(length)(T deque);
/* retourne la valeur en tête de la deque */
deque_datum_t   DEQUE_METHOD(first)(T deque);
/* retourne la valeur en queue de la deque */
deque_datum_t   DEQUE_METHOD(last)(T deque);
/* retourne la valeur à l'index donné de la deque */
deque_datum_t   DEQUE_METHOD(get)(T deque, int index);
/* modifie la valeur à l'index donné de la deque et retourne la deque modifiée */
T               DEQUE_METHOD(set)(deque_datum_t value, T deque, int index);
/* insère une valeur en tête de la deque et retourne la nouvelle deque */
T               DEQUE_METHOD(push_front)(deque_datum_t value, T deque);
/* insère une valeur en queue de la deque et retourne la nouvelle deque */
T               DEQUE_METHOD(push_back)(deque_datum_t value, T deque);
/* retire la valeur en tête de la deque, la stocke dans value et retourne la nouvelle deque */
T               DEQUE_METHOD(pop_front)(deque_datum_t *value, T deque);
/* retire la valeur en queue de la deque, la stocke dans value et retourne la nouvelle deque */
T               DEQUE_METHOD(pop_back)(deque_datum_t *value, T deque);
/* effectue nb_rot rotations de la deque et retourne la deque modifiée */
T               DEQUE_METHOD(rotate)(int nb_rot, T deque);
/* retourne l'index de la value si la deque contient obj, -1 sinon */
int             DEQUE_METHOD(contains)(T deque, deque_datum_t value);
/* retire l'élément obj de la deque et retourne la nouvelle deque */
T               DEQUE_METHOD(remove)(deque_datum_t value, T deque);
/* supprime la deque proprement en utilisant le destructeur sur chaque élément */
void            DEQUE_METHOD(delete)(T deque);
/* affiche la deque en utilisant la fonction printer pour chaque élément */
void            DEQUE_METHOD(print)(T deque);