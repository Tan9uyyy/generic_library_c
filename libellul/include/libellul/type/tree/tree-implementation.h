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
};

TYPE(T, datum_t) METHOD(T, new) (void){return NULL;}

int METHOD(T, is_empty) (TYPE(T, datum_t) tree){return NULL == tree;}

TYPE(T, datum_t) METHOD(T, rec_push) (TYPE(T, datum_t) tree, datum_t value, int (*comparator) (datum_t, datum_t)){
    if (METHOD(T, is_empty) (tree)){
        struct TYPE(node, datum_t) *new_node = malloc(sizeof(*new_node));
        assert(new_node && "Allocation failed !");

        new_node->value = value; new_node->ls = NULL; new_node->rs = NULL;
        return new_node;
    }

    if (comparator(value, tree->value) > 0){
        tree->rs = METHOD(T, rec_push) (tree->rs, value, *comparator);
        return tree;
    }

    tree->ls = METHOD(T, rec_push) (tree->ls, value, *comparator);
    return tree;
}

TYPE(T, datum_t) METHOD(T, push) (TYPE(T, datum_t) tree, datum_t value, int (*comparator) (datum_t, datum_t)){
    return METHOD(T, rec_push) (tree, value, comparator);
}

static inline TYPE(T, datum_t) METHOD(T, pop_small_rec) (TYPE(T, datum_t) tree, datum_t *value){
    if (METHOD(T, is_empty) (tree->ls)){
        *value = tree->value;

        TYPE(T, datum_t) new_root = tree->rs;
        free(tree);

        return new_root;
    }

    tree->ls = METHOD(T, pop_small_rec) (tree->ls, value);
    return tree;
}

TYPE(T, datum_t) METHOD(T, pop_small) (TYPE(T, datum_t) tree, datum_t *value){
    assert(!METHOD(T, is_empty) (tree) && "Tree is empty !");

    return METHOD(T, pop_small_rec(tree, value));
}

static inline TYPE(T, datum_t) METHOD(T, pop_big_rec) (TYPE(T, datum_t) tree, datum_t *value){
    if (METHOD(T, is_empty) (tree->rs)){
        *value = tree->value;

        TYPE(T, datum_t) new_root = tree->ls;
        free(tree);

        return new_root;
    }

    tree->rs = METHOD(T, pop_big_rec) (tree->rs, value);
    return tree;
}

TYPE(T, datum_t) METHOD(T, pop_big) (TYPE(T, datum_t) tree, datum_t *value){
    assert(!METHOD(T, is_empty) (tree) && "Tree is empty !");

    return METHOD(T, pop_big_rec(tree, value));
}

int METHOD(T, contains) (TYPE(T, datum_t) tree, datum_t value, int (*comparator)(datum_t, datum_t)){
    if (METHOD(T, is_empty) (tree)){return 0;}

    if (comparator(value, tree->value) == 0){return 1;}

    if (comparator(value, tree->value) > 0){return METHOD(T, contains) (tree->rs, value, *comparator);}

    return METHOD(T, contains) (tree->ls, value, *comparator);
}

TYPE(T, datum_t) METHOD(T, delete) (TYPE(T, datum_t) tree, void (*destructor)(datum_t)){
    if (METHOD(T, is_empty) (tree)){return NULL;}

    if (tree->ls){METHOD(T, delete) (tree->ls, *destructor);}

    if (tree->rs){METHOD(T, delete) (tree->rs, *destructor);}

    if (destructor){destructor(tree->value);}
    free(tree);

    return NULL;
}

void METHOD(T, print_rec) (TYPE(T, datum_t) tree, void (*printer)(datum_t)){
    if (!METHOD(T, is_empty) (tree->ls)){METHOD(T, print_rec) (tree->ls, *printer); printf(" ");}

    printer(tree->value);

    if (!METHOD(T, is_empty) (tree->rs)){printf(" "); METHOD(T, print_rec) (tree->rs, *printer);}
}

void METHOD(T, print) (TYPE(T, datum_t) tree, void (*printer)(datum_t)){
    printf("{");
    if (!METHOD(T, is_empty) (tree))METHOD(T, print_rec) (tree, *printer);
    printf("}");
}





#undef T

#endif