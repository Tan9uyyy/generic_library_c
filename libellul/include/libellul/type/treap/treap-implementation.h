#ifndef _TREAP_IMPLEMENTATION_H__
#define _TREAP_IMPLEMENTATION_H__

#ifndef treap_datum_t
    #error "Undefined datum type !"
#endif

#define T treap
#include "../../interface.h"

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

typedef struct TYPE(node, treap_datum_t){
    struct TYPE(node, treap_datum_t) *ls;
    struct TYPE(node, treap_datum_t) *rs;
    treap_datum_t value;
    int priority;
} TYPE(node, treap_datum_t);

TYPE(T, treap_datum_t) METHOD(T, treap_datum_t, new) (void){return NULL;}

int METHOD(T, treap_datum_t, is_empty) (TYPE(T, treap_datum_t) treap){return NULL == treap;}

TYPE(T, treap_datum_t) METHOD(T, treap_datum_t, rec_push) (TYPE(T, treap_datum_t) treap, treap_datum_t value, int priority, int (*comparator)(treap_datum_t, treap_datum_t)){
    if (METHOD(T, treap_datum_t, is_empty) (treap)){
        struct TYPE(node, treap_datum_t) *new_node = malloc(sizeof(*new_node));
        assert(new_node && "Allocation failed !");

        new_node->value = value; new_node->priority = priority;
        new_node->ls = NULL; new_node->rs = NULL;

        return new_node;
    }

    // Use of priority_func to randomized the consequences of collisions to balance the tree
    if (0 == comparator(value, treap->value)){
        if (priority > treap->priority){
            treap->rs = METHOD(T, treap_datum_t, rec_push) (treap->rs, value, priority, comparator);
            return treap;
        }

        treap->ls = METHOD(T, treap_datum_t, rec_push) (treap->ls, value, priority, comparator);
        return treap;
    }

    if (comparator(value, treap->value) > 0){
        treap->rs = METHOD(T, treap_datum_t, rec_push) (treap->rs, value, priority, comparator);
        return treap;
    }

    treap->ls = METHOD(T, treap_datum_t, rec_push) (treap->ls, value, priority, comparator);
    return treap;
}

TYPE(T, treap_datum_t) METHOD(T, treap_datum_t, push) (TYPE(T, treap_datum_t) treap, treap_datum_t value, int (*comparator)(treap_datum_t, treap_datum_t), int (*priority_func)(treap_datum_t)){
    return METHOD(T, treap_datum_t, rec_push) (treap, value, priority_func(value), comparator);
}

treap_datum_t METHOD(T, treap_datum_t, max) (TYPE(T, treap_datum_t) treap){
    assert(!METHOD(T, treap_datum_t, is_empty) (treap) && "Treap is empty !");

    if (METHOD(T, treap_datum_t, is_empty) (treap->rs)){return treap->value;}
    return METHOD(T, treap_datum_t, max) (treap->rs);
}

treap_datum_t METHOD(T, treap_datum_t, min) (TYPE(T, treap_datum_t) treap){
    assert(!METHOD(T, treap_datum_t, is_empty) (treap) && "Treap is empty !");

    if (METHOD(T, treap_datum_t, is_empty) (treap->ls)){return treap->value;}
    return METHOD(T, treap_datum_t, min) (treap->ls);
}

TYPE(T, treap_datum_t) METHOD(T, treap_datum_t, pop_small_rec) (TYPE(T, treap_datum_t) treap, treap_datum_t *value){
    if (METHOD(T, treap_datum_t, is_empty) (treap->ls)){
        *value = treap->value;

        TYPE(T, treap_datum_t) new_root = treap->rs;
        free(treap);

        return new_root;
    }

    treap->ls = METHOD(T, treap_datum_t, pop_small_rec) (treap->ls, value);
    return treap;
}

TYPE(T, treap_datum_t) METHOD(T, treap_datum_t, pop_small) (TYPE(T, treap_datum_t) treap, treap_datum_t *value){
    assert(!METHOD(T, treap_datum_t, is_empty) (treap) && "Treap is empty !");

    return METHOD(T, treap_datum_t, pop_small_rec) (treap, value);
}

TYPE(T, treap_datum_t) METHOD(T, treap_datum_t, pop_big_rec) (TYPE(T, treap_datum_t) treap, treap_datum_t *value){
    if (METHOD(T, treap_datum_t, is_empty) (treap->rs)){
        *value = treap->value;

        TYPE(T, treap_datum_t) new_root = treap->ls;
        free(treap);

        return new_root;
    }

    treap->rs = METHOD(T, treap_datum_t, pop_big_rec) (treap->rs, value);
    return treap;
}

TYPE(T, treap_datum_t) METHOD(T, treap_datum_t, pop_big) (TYPE(T, treap_datum_t) treap, treap_datum_t *value){
    assert(!METHOD(T, treap_datum_t, is_empty) (treap) && "Treap is empty !");

    return METHOD(T, treap_datum_t, pop_big_rec) (treap, value);
}

int METHOD(T, treap_datum_t, contains) (TYPE(T, treap_datum_t) treap, treap_datum_t value, int (*comparator)(treap_datum_t, treap_datum_t)){
    if (METHOD(T, treap_datum_t, is_empty) (treap)){return 0;}

    if (0 == comparator(value, treap->value)){return 1;}

    if (comparator(value, treap->value) > 0){return METHOD(T, treap_datum_t, contains) (treap->rs, value, comparator);}

    return METHOD(T, treap_datum_t, contains) (treap->ls, value, comparator);
}

TYPE(T, treap_datum_t) METHOD(T, treap_datum_t, delete) (TYPE(T, treap_datum_t) treap, void (*destructor)(treap_datum_t)){
    if (METHOD(T, treap_datum_t, is_empty) (treap)){return NULL;}

    if (!METHOD(T, treap_datum_t, is_empty) (treap->ls)){METHOD(T, treap_datum_t, delete) (treap->ls, destructor);}

    if (!METHOD(T, treap_datum_t, is_empty) (treap->rs)){METHOD(T, treap_datum_t, delete) (treap->rs, destructor);}

    if (destructor){destructor(treap->value);}
    free(treap);

    return NULL;
}

void METHOD(T, treap_datum_t, print_rec) (TYPE(T, treap_datum_t) treap, void (*printer)(treap_datum_t)){
    if (!METHOD(T, treap_datum_t, is_empty) (treap->ls)){METHOD(T, treap_datum_t, print_rec) (treap->ls, printer); printf(" ");}

    printer(treap->value);

    if (!METHOD(T, treap_datum_t, is_empty) (treap->rs)){printf(" "); METHOD(T, treap_datum_t, print_rec) (treap->rs, printer);}
}

void METHOD(T, treap_datum_t, print) (TYPE(T, treap_datum_t) treap, void (*printer)(treap_datum_t)){
    printf("{");
    if (!METHOD(T, treap_datum_t, is_empty) (treap)){METHOD(T, treap_datum_t, print_rec) (treap, printer);}
    printf("}");
}










#undef T

#endif