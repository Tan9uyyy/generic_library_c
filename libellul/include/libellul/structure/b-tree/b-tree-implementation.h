#include <assert.h>
#include <stdio.h>
#include <stdlib.h>


T B_TREE_METHOD(new) (void){return NULL;}

int B_TREE_METHOD(is_empty) (T b_tree){return NULL == b_tree;}

T B_TREE_METHOD(push) (T b_tree, b_tree_datum_t value){
    if (B_TREE_METHOD(is_empty) (b_tree)){
        T new_node = malloc(sizeof(*new_node));
        assert(new_node && "Allocation failed !");

        new_node->value = value;
        new_node->ls = NULL; new_node->rs = NULL;

        return new_node;
    }

    if (COMPARATOR(value, b_tree->value) < 0){
        b_tree->rs = B_TREE_METHOD(push) (b_tree->rs, value);
        return b_tree;
    }

    b_tree->ls = B_TREE_METHOD(push) (b_tree->ls, value);
    return b_tree;
}

T B_TREE_METHOD(pop_cascade) (T b_tree){
    if (b_tree->rs){
        b_tree->value = b_tree->rs->value;
        b_tree->rs = B_TREE_METHOD(pop_cascade) (b_tree->rs);
        return b_tree;
    }

    if (b_tree->ls) return b_tree->ls;

    if (DESTRUCTOR()) DESTRUCTOR(b_tree->value);
    free(b_tree);
    return NULL;
}

T B_TREE_METHOD(pop) (T b_tree, b_tree_datum_t value){
    if (B_TREE_METHOD(is_empty) (b_tree)) return b_tree;

    if (COMPARATOR(value, b_tree->value) < 0) {
        b_tree->rs = B_TREE_METHOD(pop) (b_tree->rs, value);
        return b_tree;
    }

    if (COMPARATOR(value, b_tree->value) > 0) {
        b_tree->ls = B_TREE_METHOD(pop) (b_tree->ls, value);
        return b_tree;
    }

    return B_TREE_METHOD(pop_cascade) (b_tree);
}

T B_TREE_METHOD(pop_small_rec) (T b_tree, b_tree_datum_t *value){
    if (B_TREE_METHOD(is_empty) (b_tree->ls)){
        *value = b_tree->value;

        T new_root = b_tree->rs;
        free(b_tree);

        return new_root;
    }

    b_tree->ls = B_TREE_METHOD(pop_small_rec) (b_tree->ls, value);
    return b_tree;
}

T B_TREE_METHOD(pop_small) (T b_tree, b_tree_datum_t *value){
    assert(!B_TREE_METHOD(is_empty) (b_tree) && "b_Tree is empty !");

    return B_TREE_METHOD(pop_small_rec(b_tree, value));
}

T B_TREE_METHOD(pop_big_rec) (T b_tree, b_tree_datum_t *value){
    if (B_TREE_METHOD(is_empty) (b_tree->rs)){
        *value = b_tree->value;

        T new_root = b_tree->ls;
        free(b_tree);

        return new_root;
    }

    b_tree->rs = B_TREE_METHOD(pop_big_rec) (b_tree->rs, value);
    return b_tree;
}

T B_TREE_METHOD(pop_big) (T b_tree, b_tree_datum_t *value){
    assert(!B_TREE_METHOD(is_empty) (b_tree) && "b_Tree is empty !");

    return B_TREE_METHOD(pop_big_rec(b_tree, value));
}

int B_TREE_METHOD(contains) (T b_tree, b_tree_datum_t value){
    if (B_TREE_METHOD(is_empty) (b_tree)) return 0;

    if (COMPARATOR(value, b_tree->value) == 0) return 1;

    if (COMPARATOR(value, b_tree->value) < 0) return B_TREE_METHOD(contains) (b_tree->rs, value);

    return B_TREE_METHOD(contains) (b_tree->ls, value);
}

T B_TREE_METHOD(delete) (T b_tree){
    if (B_TREE_METHOD(is_empty) (b_tree)) return NULL;

    if (b_tree->ls) B_TREE_METHOD(delete) (b_tree->ls);

    if (b_tree->rs) B_TREE_METHOD(delete) (b_tree->rs);

    if (DESTRUCTOR()) DESTRUCTOR(b_tree->value); 
    free(b_tree);

    return NULL;
}

void B_TREE_METHOD(print_rec) (T b_tree){
    if (!B_TREE_METHOD(is_empty) (b_tree->ls)) {B_TREE_METHOD(print_rec) (b_tree->ls); printf(" ");}

    PRINTER(b_tree->value);
    printf(" ");

    if (!B_TREE_METHOD(is_empty) (b_tree->rs)) {printf(" "); B_TREE_METHOD(print_rec) (b_tree->rs);}
}

void B_TREE_METHOD(print) (T b_tree){
    printf("{ ");
    if (!B_TREE_METHOD(is_empty) (b_tree)) B_TREE_METHOD(print_rec) (b_tree);
    printf("}\n");
}