#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

T TREESET_METHOD(new)(){return NULL;}

int TREESET_METHOD(is_empty)(T treeset){return NULL == treeset;}

int TREESET_METHOD(contains)(T treeset, treeset_datum_t value){return METHOD(treap, treeset_datum_t, contains)(treeset, value);}

T TREESET_METHOD(add)(T treeset, treeset_datum_t value){
    if (TREESET_METHOD(contains)(treeset, value)){return treeset;}

    return METHOD(treap, treeset_datum_t, push)(treeset, value);
}

treeset_datum_t TREESET_METHOD(upper_bound)(T treeset){return METHOD(treap, treeset_datum_t, max)(treeset);}

treeset_datum_t TREESET_METHOD(lower_bound)(T treeset){return METHOD(treap, treeset_datum_t, min)(treeset);}

T TREESET_METHOD(remove_max)(T treeset){treeset_datum_t buffer; return METHOD(treap, treeset_datum_t, pop_big) (treeset, &buffer);}

T TREESET_METHOD(remove_min)(T treeset){treeset_datum_t buffer; return METHOD(treap, treeset_datum_t, pop_small) (treeset, &buffer);}

T TREESET_METHOD(reunion)(T *treeset1, T *treeset2){
    treeset_datum_t value;
    T new_treeset1 = TREESET_METHOD(new)();
    T new_treeset2 = TREESET_METHOD(new)();
    T res_treeset = TREESET_METHOD(new)();

    while (!TREESET_METHOD(is_empty)(*treeset1)){
        *treeset1 = METHOD(treap, treeset_datum_t, pop_small) (*treeset1, &value);
        new_treeset1 = TREESET_METHOD(add) (new_treeset1, value);

        res_treeset = TREESET_METHOD(add) (res_treeset, value);
    }

    while (!TREESET_METHOD(is_empty)(*treeset2)){
        *treeset2 = METHOD(treap, treeset_datum_t, pop_big) (*treeset2, &value);
        new_treeset2 = TREESET_METHOD(add) (new_treeset2, value);

        res_treeset = TREESET_METHOD(add) (res_treeset, value);
    }

    *treeset1 = new_treeset1; *treeset2 = new_treeset2;
    return res_treeset;
}

T TREESET_METHOD(inter)(T *treeset1, T *treeset2){
    treeset_datum_t value;
    T new_treeset2 = TREESET_METHOD(new)();
    T res_treeset = TREESET_METHOD(new)();

    while (!TREESET_METHOD(is_empty)(*treeset2)){
        *treeset2 = METHOD(treap, treeset_datum_t, pop_small) (*treeset2, &value);
        new_treeset2 = TREESET_METHOD(add) (new_treeset2, value);

        if (TREESET_METHOD(contains)(*treeset1, value)) res_treeset = TREESET_METHOD(add) (res_treeset, value);
    }

    *treeset2 = new_treeset2;
    return res_treeset;
}

T TREESET_METHOD(delete)(T treeset){return METHOD(treap, treeset_datum_t, delete)(treeset);}

void TREESET_METHOD(print)(T treeset){METHOD(treap, treeset_datum_t, print) (treeset);}








#undef T

#endif