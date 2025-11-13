#ifndef _TREAP_IMPLEMENTATION_H__
#define _TREAP_IMPLEMENTATION_H__

#ifndef datum_t
    #error "Undefined datum type !"
#endif

#define T treap
#include "../../interface.h"

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

typedef struct TYPE(node, datum_t){
    struct TYPE(node, datum_t) *ls;
    struct TYPE(node, datum_t) *rs;
    datum_t value;
    int priority;
} TYPE(node, datum_t);

TYPE(T, datum_t) METHOD(T, new) (void){return NULL;}

int METHOD(T, is_empty) (TYPE(T, datum_t) treap){return NULL == treap;}

TYPE(T, datum_t) METHOD(T, rec_push) (TYPE(T, datum_t) treap, datum_t value, int priority, int (*comparator)(datum_t, datum_t)){
    if (METHOD(T, is_empty) (treap)){
        struct TYPE(node, datum_t) *new_node = malloc(sizeof(*new_node));
        assert(new_node && "Allocation failed !");

        new_node->value = value; new_node->priority = priority;
        new_node->ls = NULL; new_node->rs = NULL;

        return new_node;
    }

    // Use of priority_func to randomized the consequences of collisions to balance the tree
    if (0 == comparator(value, treap->value)){
        if (priority > treap->priority){
            treap->rs = METHOD(T, rec_push) (treap->rs, value, priority, comparator);
            return treap;
        }

        treap->ls = METHOD(T, rec_push) (treap->ls, value, priority, comparator);
        return treap;
    }

    if (comparator(value, treap->value) > 0){
        treap->rs = METHOD(T, rec_push) (treap->rs, value, priority, comparator);
        return treap;
    }

    treap->ls = METHOD(T, rec_push) (treap->ls, value, priority, comparator);
    return treap;
}

TYPE(T, datum_t) METHOD(T, push) (TYPE(T, datum_t) treap, datum_t value, int (*comparator)(datum_t, datum_t), int (*priority_func)(datum_t)){
    return METHOD(T, rec_push) (treap, value, priority_func(value), comparator);
}

TYPE(T, datum_t) METHOD(T, pop_small_rec) (TYPE(T, datum_t) treap, datum_t *value){
    if (METHOD(T, is_empty) (treap->ls)){
        *value = treap->value;

        TYPE(T, datum_t) new_root = treap->rs;
        free(treap);

        return new_root;
    }

    treap->ls = METHOD(T, pop_small_rec) (treap->ls, value);
    return treap;
}

TYPE(T, datum_t) METHOD(T, pop_small) (TYPE(T, datum_t) treap, datum_t *value){
    assert(!METHOD(T, is_empty) (treap) && "Treap is empty !");

    return METHOD(T, pop_small_rec) (treap, value);
}

TYPE(T, datum_t) METHOD(T, pop_big_rec) (TYPE(T, datum_t) treap, datum_t *value){
    if (METHOD(T, is_empty) (treap->rs)){
        *value = treap->value;

        TYPE(T, datum_t) new_root = treap->ls;
        free(treap);

        return new_root;
    }

    treap->rs = METHOD(T, pop_big_rec) (treap->rs, value);
    return treap;
}

TYPE(T, datum_t) METHOD(T, pop_big) (TYPE(T, datum_t) treap, datum_t *value){
    assert(!METHOD(T, is_empty) (treap) && "Treap is empty !");

    return METHOD(T, pop_big_rec) (treap, value);
}

int METHOD(T, contains) (TYPE(T, datum_t) treap, datum_t value, int (*comparator)(datum_t, datum_t)){
    if (METHOD(T, is_empty) (treap)){return 0;}

    if (0 == comparator(value, treap->value)){return 1;}

    if (comparator(value, treap->value) > 0){return METHOD(T, contains) (treap->rs, value, comparator);}

    return METHOD(T, contains) (treap->ls, value, comparator);
}

TYPE(T, datum_t) METHOD(T, delete) (TYPE(T, datum_t) treap, void (*destructor)(datum_t)){
    if (METHOD(T, is_empty) (treap)){return NULL;}

    if (!METHOD(T, is_empty) (treap->ls)){METHOD(T, delete) (treap->ls, destructor);}

    if (!METHOD(T, is_empty) (treap->rs)){METHOD(T, delete) (treap->rs, destructor);}

    if (destructor){destructor(treap->value);}
    free(treap);

    return NULL;
}

void METHOD(T, print_rec) (TYPE(T, datum_t) treap, void (*printer)(datum_t)){
    if (!METHOD(T, is_empty) (treap->ls)){METHOD(T, print_rec) (treap->ls, printer); printf(" ");}

    printer(treap->value);

    if (!METHOD(T, is_empty) (treap->rs)){printf(" "); METHOD(T, print_rec) (treap->rs, printer);}
}

void METHOD(T, print) (TYPE(T, datum_t) treap, void (*printer)(datum_t)){
    printf("{");
    if (!METHOD(T, is_empty) (treap)){METHOD(T, print_rec) (treap, printer);}
    printf("}");
}










#undef T

#endif