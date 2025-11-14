#ifndef _TREE_IMPLEMENTATION_H__
#define _TREE_IMPLEMENTATION_H__

#ifndef datum_t
    #error "Undefined datum type !"
#endif

#define T binary_tree
#include "../../interface.h"

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

typedef struct TYPE(node, datum_t){
    struct TYPE(node, datum_t) *ls;
    struct TYPE(node, datum_t) *rs;
    datum_t value;
} TYPE(node, datum_t);

TYPE(T, datum_t) METHOD(T, datum_t, new) (void){return NULL;}

int METHOD(T, datum_t, is_empty) (TYPE(T, datum_t) tree){return NULL == tree;}

TYPE(T, datum_t) METHOD(T, datum_t, rec_push) (TYPE(T, datum_t) tree, datum_t value, int (*comparator) (datum_t, datum_t)){
    if (METHOD(T, datum_t, is_empty) (tree)){
        struct TYPE(node, datum_t) *new_node = malloc(sizeof(*new_node));
        assert(new_node && "Allocation failed !");

        new_node->value = value;
        new_node->ls = NULL; new_node->rs = NULL;

        return new_node;
    }

    if (comparator(value, tree->value) > 0){
        tree->rs = METHOD(T, datum_t, rec_push) (tree->rs, value, *comparator);
        return tree;
    }

    tree->ls = METHOD(T, datum_t, rec_push) (tree->ls, value, *comparator);
    return tree;
}

TYPE(T, datum_t) METHOD(T, datum_t, push) (TYPE(T, datum_t) tree, datum_t value, int (*comparator) (datum_t, datum_t)){
    return METHOD(T, datum_t, rec_push) (tree, value, comparator);
}

static inline TYPE(T, datum_t) METHOD(T, datum_t, pop_small_rec) (TYPE(T, datum_t) tree, datum_t *value){
    if (METHOD(T, datum_t, is_empty) (tree->ls)){
        *value = tree->value;

        TYPE(T, datum_t) new_root = tree->rs;
        free(tree);

        return new_root;
    }

    tree->ls = METHOD(T, datum_t, pop_small_rec) (tree->ls, value);
    return tree;
}

TYPE(T, datum_t) METHOD(T, datum_t, pop_small) (TYPE(T, datum_t) tree, datum_t *value){
    assert(!METHOD(T, datum_t, is_empty) (tree) && "Tree is empty !");

    return METHOD(T, datum_t, pop_small_rec(tree, value));
}

static inline TYPE(T, datum_t) METHOD(T, datum_t, pop_big_rec) (TYPE(T, datum_t) tree, datum_t *value){
    if (METHOD(T, datum_t, is_empty) (tree->rs)){
        *value = tree->value;

        TYPE(T, datum_t) new_root = tree->ls;
        free(tree);

        return new_root;
    }

    tree->rs = METHOD(T, datum_t, pop_big_rec) (tree->rs, value);
    return tree;
}

TYPE(T, datum_t) METHOD(T, datum_t, pop_big) (TYPE(T, datum_t) tree, datum_t *value){
    assert(!METHOD(T, datum_t, is_empty) (tree) && "Tree is empty !");

    return METHOD(T, datum_t, pop_big_rec(tree, value));
}

int METHOD(T, datum_t, contains) (TYPE(T, datum_t) tree, datum_t value, int (*comparator)(datum_t, datum_t)){
    if (METHOD(T, datum_t, is_empty) (tree)){return 0;}

    if (comparator(value, tree->value) == 0){return 1;}

    if (comparator(value, tree->value) > 0){return METHOD(T, datum_t, contains) (tree->rs, value, *comparator);}

    return METHOD(T, datum_t, contains) (tree->ls, value, *comparator);
}

TYPE(T, datum_t) METHOD(T, datum_t, delete) (TYPE(T, datum_t) tree, void (*destructor)(datum_t)){
    if (METHOD(T, datum_t, is_empty) (tree)){return NULL;}

    if (tree->ls){METHOD(T, datum_t, delete) (tree->ls, *destructor);}

    if (tree->rs){METHOD(T, datum_t, delete) (tree->rs, *destructor);}

    if (destructor){destructor(tree->value);}
    free(tree);

    return NULL;
}

void METHOD(T, datum_t, print_rec) (TYPE(T, datum_t) tree, void (*printer)(datum_t)){
    if (!METHOD(T, datum_t, is_empty) (tree->ls)){METHOD(T, datum_t, print_rec) (tree->ls, printer); printf(" ");}

    printer(tree->value);

    if (!METHOD(T, datum_t, is_empty) (tree->rs)){printf(" "); METHOD(T, datum_t, print_rec) (tree->rs, printer);}
}

void METHOD(T, datum_t, print) (TYPE(T, datum_t) tree, void (*printer)(datum_t)){
    printf("{");
    if (!METHOD(T, datum_t, is_empty) (tree))METHOD(T, datum_t, print_rec) (tree, printer);
    printf("}");
}





#undef T

#endif