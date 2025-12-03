#ifndef _B_TREE_IMPLEMENTATION_H__
#define _B_TREE_IMPLEMENTATION_H__

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#ifdef T
#undef T
#endif
#define T b_tree

typedef struct TYPE(b_tree_node, b_tree_datum_t){
    struct TYPE(b_tree_node, b_tree_datum_t) *ls;
    struct TYPE(b_tree_node, b_tree_datum_t) *rs;
    b_tree_datum_t value;
} TYPE(b_tree_node, b_tree_datum_t);

TYPE(T, b_tree_datum_t) METHOD(T, b_tree_datum_t, new) (void){return NULL;}

int METHOD(T, b_tree_datum_t, is_empty) (TYPE(T, b_tree_datum_t) b_tree){return NULL == b_tree;}

TYPE(T, b_tree_datum_t) METHOD(T, b_tree_datum_t, push) (TYPE(T, b_tree_datum_t) b_tree, b_tree_datum_t value){
    if (METHOD(T, b_tree_datum_t, is_empty) (b_tree)){
        TYPE(b_tree_node, b_tree_datum_t) *new_node = malloc(sizeof(*new_node));
        assert(new_node && "Allocation failed !");

        new_node->value = value;
        new_node->ls = NULL; new_node->rs = NULL;

        return new_node;
    }

    if (COMPARATOR(value, b_tree->value) < 0){
        b_tree->rs = METHOD(T, b_tree_datum_t, push) (b_tree->rs, value);
        return b_tree;
    }

    b_tree->ls = METHOD(T, b_tree_datum_t, push) (b_tree->ls, value);
    return b_tree;
}

TYPE(T, b_tree_datum_t) METHOD(T, b_tree_datum_t, pop_cascade) (TYPE(T, b_tree_datum_t) b_tree){
    if (b_tree->rs){
        b_tree->value = b_tree->rs->value;
        b_tree->rs = METHOD(T, b_tree_datum_t, pop_cascade) (b_tree->rs);
        return b_tree;
    }

    if (b_tree->ls){
        b_tree->value = b_tree->ls->value;
        b_tree->ls = METHOD(T, b_tree_datum_t, pop_cascade) (b_tree->ls);
        return b_tree;
    }

    if (DESTRUCTOR()) DESTRUCTOR(b_tree->value);
    free(b_tree);
    return NULL;
}

TYPE(T, b_tree_datum_t) METHOD(T, b_tree_datum_t, pop) (TYPE(T, b_tree_datum_t) b_tree, b_tree_datum_t value){
    if (METHOD(T, b_tree_datum_t, is_empty) (b_tree)) return b_tree;

    if (COMPARATOR(value, b_tree->value) < 0) {
        b_tree->rs = METHOD(T, b_tree_datum_t, pop) (b_tree->rs, value);
        return b_tree;
    }

    if (COMPARATOR(value, b_tree->value) > 0) {
        b_tree->ls = METHOD(T, b_tree_datum_t, pop) (b_tree->ls, value);
        return b_tree;
    }

    return METHOD(T, b_tree_datum_t, pop_cascade) (b_tree);
}

TYPE(T, b_tree_datum_t) METHOD(T, b_tree_datum_t, pop_small_rec) (TYPE(T, b_tree_datum_t) b_tree, b_tree_datum_t *value){
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

TYPE(T, b_tree_datum_t) METHOD(T, b_tree_datum_t, pop_big_rec) (TYPE(T, b_tree_datum_t) b_tree, b_tree_datum_t *value){
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

int METHOD(T, b_tree_datum_t, contains) (TYPE(T, b_tree_datum_t) b_tree, b_tree_datum_t value){
    if (METHOD(T, b_tree_datum_t, is_empty) (b_tree)) return 0;

    if (COMPARATOR(value, b_tree->value) == 0) return 1;

    if (COMPARATOR(value, b_tree->value) < 0) return METHOD(T, b_tree_datum_t, contains) (b_tree->rs, value);

    return METHOD(T, b_tree_datum_t, contains) (b_tree->ls, value);
}

TYPE(T, b_tree_datum_t) METHOD(T, b_tree_datum_t, delete) (TYPE(T, b_tree_datum_t) b_tree){
    if (METHOD(T, b_tree_datum_t, is_empty) (b_tree)) return NULL;

    if (b_tree->ls) METHOD(T, b_tree_datum_t, delete) (b_tree->ls);

    if (b_tree->rs) METHOD(T, b_tree_datum_t, delete) (b_tree->rs);

    if (DESTRUCTOR()) DESTRUCTOR(b_tree->value); 
    free(b_tree);

    return NULL;
}

void METHOD(T, b_tree_datum_t, print_rec) (TYPE(T, b_tree_datum_t) b_tree){
    if (!METHOD(T, b_tree_datum_t, is_empty) (b_tree->ls)) {METHOD(T, b_tree_datum_t, print_rec) (b_tree->ls); printf(" ");}

    PRINTER(b_tree->value);

    if (!METHOD(T, b_tree_datum_t, is_empty) (b_tree->rs)) {printf(" "); METHOD(T, b_tree_datum_t, print_rec) (b_tree->rs);}
}

void METHOD(T, b_tree_datum_t, print) (TYPE(T, b_tree_datum_t) b_tree){
    printf("{");
    if (!METHOD(T, b_tree_datum_t, is_empty) (b_tree)) METHOD(T, b_tree_datum_t, print_rec) (b_tree);
    printf("}");
}





#undef T

#endif