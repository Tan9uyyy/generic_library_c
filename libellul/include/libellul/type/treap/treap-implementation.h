#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

T TREAP_METHOD(new) (void){return NULL;}

int TREAP_METHOD(is_empty) (T treap){return B_TREE_METHOD(is_empty)(treap);}

T TREAP_METHOD(rec_push) (T treap, treap_datum_t value, int priority){
    if (TREAP_METHOD(is_empty) (treap)){
        treap_couple new_node = {.value = value, .priority = priority};

        return B_TREE_METHOD(push)(treap, new_node);
    }

    // Use of priority_func to randomized the consequences of collisions to balance the tree
    if (0 == TREAP_COMPARATOR(value, treap->value.value)){
        if (priority > treap->value.priority){
            treap->rs = TREAP_METHOD(rec_push) (treap->rs, value, priority);
            return treap;
        }

        treap->ls = TREAP_METHOD(rec_push) (treap->ls, value, priority);
        return treap;
    }

    if (TREAP_COMPARATOR(value, treap->value.value) > 0){
        treap->rs = TREAP_METHOD(rec_push) (treap->rs, value, priority);
        return treap;
    }

    treap->ls = TREAP_METHOD(rec_push) (treap->ls, value, priority);
    return treap;
}

T TREAP_METHOD(push) (T treap, treap_datum_t value){return TREAP_METHOD(rec_push) (treap, value, TREAP_PRIORITY_FUNC(value));}

treap_datum_t TREAP_METHOD(min) (T treap){
    if (TREAP_METHOD(is_empty)(treap)) return NULL;
    if (TREAP_METHOD(is_empty)(treap->rs)) return treap->value.value;
    return TREAP_METHOD(min)(treap->rs);
}

treap_datum_t TREAP_METHOD(max) (T treap){
    if (TREAP_METHOD(is_empty)(treap)) return NULL;
    if (TREAP_METHOD(is_empty)(treap->ls)) return treap->value.value;
    return TREAP_METHOD(max)(treap->ls);
}

T TREAP_METHOD(pop_small) (T treap, treap_datum_t *value){
    treap_couple elem;
    treap = B_TREE_METHOD(pop_small) (treap, &elem);
    *value = elem.value;

    return treap;
}

T TREAP_METHOD(pop_big) (T treap, treap_datum_t *value){
    treap_couple elem;
    treap = B_TREE_METHOD(pop_big) (treap, &elem);
    *value = elem.value;

    return treap;
}

int TREAP_METHOD(contains) (T treap, treap_datum_t value){
    if (TREAP_METHOD(is_empty)(treap)) return 0;
    if (0 == TREAP_COMPARATOR(value, treap->value.value)) return 1;
    if (TREAP_COMPARATOR(value, treap->value.value) > 0) return TREAP_METHOD(contains)(treap->rs, value);
    return TREAP_METHOD(contains)(treap->ls, value);
}

T TREAP_METHOD(delete) (T treap){return B_TREE_METHOD(delete)(treap);}

void TREAP_METHOD(print_rec) (T treap){
    if (!TREAP_METHOD(is_empty)(treap->ls))TREAP_METHOD(print_rec)(treap->ls);
    printf("(%d, ", treap->value.priority);
    TREAP_PRINTER(treap->value.value);
    printf(") ");
    if (!TREAP_METHOD(is_empty)(treap->rs))TREAP_METHOD(print_rec)(treap->rs);
}

void TREAP_METHOD(print) (T treap){
    if (TREAP_METHOD(is_empty)(treap)) {printf("{}\n"); return;}

    printf("{ ");
    TREAP_METHOD(print_rec)(treap);
    printf("}\n");
}