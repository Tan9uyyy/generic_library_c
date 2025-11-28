#ifndef _B_TREE_IMPLEMENTATION_H__
#define _B_TREE_IMPLEMENTATION_H__

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#include "b-tree-export-def.h"

#define T binary_tree

typedef struct TYPE(node, b_tree_datum_t){
    struct TYPE(node, b_tree_datum_t) *ls;
    struct TYPE(node, b_tree_datum_t) *rs;
    b_tree_datum_t value;
} TYPE(node, b_tree_datum_t);

TYPE(T, b_tree_datum_t) METHOD(T, b_tree_datum_t, new) (void){return NULL;}

int METHOD(T, b_tree_datum_t, is_empty) (TYPE(T, b_tree_datum_t) b_tree){return NULL == b_tree;}

TYPE(T, b_tree_datum_t) METHOD(T, b_tree_datum_t, rec_push) (TYPE(T, b_tree_datum_t) b_tree, b_tree_datum_t value, int (*comparator) (b_tree_datum_t, b_tree_datum_t)){
    if (METHOD(T, b_tree_datum_t, is_empty) (b_tree)){
        struct TYPE(node, b_tree_datum_t) *new_node = malloc(sizeof(*new_node));
        assert(new_node && "Allocation failed !");

        new_node->value = value;
        new_node->ls = NULL; new_node->rs = NULL;

        return new_node;
    }

    if (comparator(value, b_tree->value) > 0){
        b_tree->rs = METHOD(T, b_tree_datum_t, rec_push) (b_tree->rs, value, *comparator);
        return b_tree;
    }

    b_tree->ls = METHOD(T, b_tree_datum_t, rec_push) (b_tree->ls, value, *comparator);
    return b_tree;
}

TYPE(T, b_tree_datum_t) METHOD(T, b_tree_datum_t, push) (TYPE(T, b_tree_datum_t) b_tree, b_tree_datum_t value, int (*comparator) (b_tree_datum_t, b_tree_datum_t)){
    return METHOD(T, b_tree_datum_t, rec_push) (b_tree, value, comparator);
}

static inline TYPE(T, b_tree_datum_t) METHOD(T, b_tree_datum_t, pop_small_rec) (TYPE(T, b_tree_datum_t) b_tree, b_tree_datum_t *value){
    if (METHOD(T, b_tree_datum_t, is_empty) (b_tree->ls)){
        *value = b_tree->value;

        TYPE(T, b_tree_datum_t) new_root = b_tree->rs;
        free(b_tree);

        return new_root;
    }

    b_tree->ls = METHOD(T, b_tree_datum_t, pop_small_rec) (b_tree->ls, value);
    return b_tree;
}

TYPE(T, b_tree_datum_t) METHOD(T, b_tree_datum_t, pop_small) (TYPE(T, b_tree_datum_t) b_tree, b_tree_datum_t *value){
    assert(!METHOD(T, b_tree_datum_t, is_empty) (b_tree) && "b_Tree is empty !");

    return METHOD(T, b_tree_datum_t, pop_small_rec(b_tree, value));
}

static inline TYPE(T, b_tree_datum_t) METHOD(T, b_tree_datum_t, pop_big_rec) (TYPE(T, b_tree_datum_t) b_tree, b_tree_datum_t *value){
    if (METHOD(T, b_tree_datum_t, is_empty) (b_tree->rs)){
        *value = b_tree->value;

        TYPE(T, b_tree_datum_t) new_root = b_tree->ls;
        free(b_tree);

        return new_root;
    }

    b_tree->rs = METHOD(T, b_tree_datum_t, pop_big_rec) (b_tree->rs, value);
    return b_tree;
}

TYPE(T, b_tree_datum_t) METHOD(T, b_tree_datum_t, pop_big) (TYPE(T, b_tree_datum_t) b_tree, b_tree_datum_t *value){
    assert(!METHOD(T, b_tree_datum_t, is_empty) (b_tree) && "b_Tree is empty !");

    return METHOD(T, b_tree_datum_t, pop_big_rec(b_tree, value));
}

int METHOD(T, b_tree_datum_t, contains) (TYPE(T, b_tree_datum_t) b_tree, b_tree_datum_t value, int (*comparator)(b_tree_datum_t, b_tree_datum_t)){
    if (METHOD(T, b_tree_datum_t, is_empty) (b_tree)){return 0;}

    if (comparator(value, b_tree->value) == 0){return 1;}

    if (comparator(value, b_tree->value) > 0){return METHOD(T, b_tree_datum_t, contains) (b_tree->rs, value, *comparator);}

    return METHOD(T, b_tree_datum_t, contains) (b_tree->ls, value, *comparator);
}

TYPE(T, b_tree_datum_t) METHOD(T, b_tree_datum_t, delete) (TYPE(T, b_tree_datum_t) b_tree, void (*destructor)(b_tree_datum_t)){
    if (METHOD(T, b_tree_datum_t, is_empty) (b_tree)){return NULL;}

    if (b_tree->ls){METHOD(T, b_tree_datum_t, delete) (b_tree->ls, *destructor);}

    if (b_tree->rs){METHOD(T, b_tree_datum_t, delete) (b_tree->rs, *destructor);}

    if (destructor){destructor(b_tree->value);}
    free(b_tree);

    return NULL;
}

void METHOD(T, b_tree_datum_t, print_rec) (TYPE(T, b_tree_datum_t) b_tree, void (*printer)(b_tree_datum_t)){
    if (!METHOD(T, b_tree_datum_t, is_empty) (b_tree->ls)){METHOD(T, b_tree_datum_t, print_rec) (b_tree->ls, printer); printf(" ");}

    printer(b_tree->value);

    if (!METHOD(T, b_tree_datum_t, is_empty) (b_tree->rs)){printf(" "); METHOD(T, b_tree_datum_t, print_rec) (b_tree->rs, printer);}
}

void METHOD(T, b_tree_datum_t, print) (TYPE(T, b_tree_datum_t) b_tree, void (*printer)(b_tree_datum_t)){
    printf("{");
    if (!METHOD(T, b_tree_datum_t, is_empty) (b_tree))METHOD(T, b_tree_datum_t, print_rec) (b_tree, printer);
    printf("}");
}





#undef T

#endif