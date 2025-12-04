#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

T TREESET_METHOD(new)(void){return NULL;}

int TREESET_METHOD(is_empty)(T treeset){return NULL == treeset;}

int TREESET_METHOD(contains)(T treeset, treeset_datum_t value){return TREAP_METHOD(contains)(treeset, value);}

T TREESET_METHOD(add)(T treeset, treeset_datum_t value){
    if (TREESET_METHOD(contains)(treeset, value)){return treeset;}

    return TREAP_METHOD(push)(treeset, value);
}

treeset_datum_t TREESET_METHOD(upper_bound)(T treeset){return TREAP_METHOD(min)(treeset);}

treeset_datum_t TREESET_METHOD(lower_bound)(T treeset){return TREAP_METHOD(max)(treeset);}

T TREESET_METHOD(remove_max)(T treeset){treeset_datum_t buffer; return TREAP_METHOD(pop_big)(treeset, &buffer);}

T TREESET_METHOD(remove_min)(T treeset){treeset_datum_t buffer; return TREAP_METHOD(pop_small)(treeset, &buffer);}

T TREESET_METHOD(reu_copy)(T treeset1, T res){
    if (TREESET_METHOD(is_empty)(treeset1)) return res;
    res = TREESET_METHOD(add)(res, treeset1->value.value);

    res = TREESET_METHOD(reu_copy)(treeset1->ls, res);
    res = TREESET_METHOD(reu_copy)(treeset1->rs, res);

    return res;
}

T TREESET_METHOD(inter_copy)(T treeset1, T treeset2, T res){
    if (TREESET_METHOD(is_empty)(treeset1)) return res;
    if (TREESET_METHOD(contains)(treeset2, treeset1->value.value)) res = TREESET_METHOD(add)(res, treeset1->value.value);

    res = TREESET_METHOD(inter_copy)(treeset1->ls, treeset2, res);
    res = TREESET_METHOD(inter_copy)(treeset1->rs, treeset2, res);

    return res;
}

T TREESET_METHOD(reunion)(T treeset1, T treeset2){
    T res = TREESET_METHOD(new)();

    res = TREESET_METHOD(reu_copy)(treeset1, res);
    res = TREESET_METHOD(reu_copy)(treeset2, res);
    return res;
}

T TREESET_METHOD(inter)(T treeset1, T treeset2){
    T res = TREESET_METHOD(new)();

    res = TREESET_METHOD(inter_copy)(treeset1, treeset2, res);
    res = TREESET_METHOD(inter_copy)(treeset2, treeset1, res);
    return res;
}

T TREESET_METHOD(delete)(T treeset){return TREAP_METHOD(delete)(treeset);}

void TREESET_METHOD(print)(T treeset){TREAP_METHOD(print) (treeset);}








#undef T