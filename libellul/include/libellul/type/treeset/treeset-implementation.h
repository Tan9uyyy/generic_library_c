#ifndef _TREESET_IMPLEMENTATION_H__
#define _TREESET_IMPLEMENTATION_H__

#include "../treap.h"
#include "../../interface.h"

#ifndef datum_t
    #error "Undefined datum type !"
#endif

#define T treeset

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

typedef TYPE(treap, datum_t) TYPE(T, datum_t);

TYPE(T, datum_t) METHOD(T, new)(){return METHOD(treap, new)();}

int METHOD(T, is_empty)(TYPE(T, datum_t) treeset){return METHOD(treap, is_empty)(treeset);}

int METHOD(T, contains)(TYPE(T, datum_t) treeset, datum_t value, int (*comparator)(datum_t, datum_t)){return METHOD(treap, contains)(treeset, value, comparator);}

TYPE(T, datum_t) METHOD(T, add)(TYPE(T, datum_t) treeset, datum_t value, int (*comparator)(datum_t, datum_t), int (*priority_func)(datum_t)){
    if (!METHOD(T, contains)(treeset, value, comparator)){
        return METHOD(treap, push)(treeset, value, comparator, priority_func);
    }

    return treeset;
}

datum_t METHOD(T, upper_bound)(TYPE(T, datum_t) treeset){return METHOD(treap, max)(treeset);}

datum_t METHOD(T, lower_bound)(TYPE(T, datum_t) treeset){return METHOD(treap, min)(treeset);}

TYPE(T, datum_t) METHOD(T, remove_max)(TYPE(T, datum_t) treeset){datum_t buffer = 0; return METHOD(treap, pop_big) (treeset, &buffer);}

TYPE(T, datum_t) METHOD(T, remove_min)(TYPE(T, datum_t) treeset){datum_t buffer = 0; return METHOD(treap, pop_small) (treeset, &buffer);}

TYPE(T, datum_t) METHOD(T, reunion)(TYPE(T, datum_t) treeset1, TYPE(T, datum_t) treeset2, int (*comparator)(datum_t, datum_t), int (*priority_func)(datum_t)){
    datum_t value;
    TYPE(T, datum_t) new_treeset1;
    TYPE(T, datum_t) new_treeset2;
    TYPE(T, datum_t) res_treeset;

    while (!METHOD(T, is_empty)(treeset1)){
        treeset1 = METHOD(treap, pop_small) (treeset1, &value);
        new_treeset1 = METHOD(T, add) (treeset1, value, comparator, priority_func);

        res_treeset = METHOD(T, add) (res_treeset, value, comparator, priority_func);
    }

    while (!METHOD(T, is_empty)(treeset2)){
        treeset2 = METHOD(treap, pop_big) (treeset2, &value);
        new_treeset2 = METHOD(T, add) (treeset2, value, comparator, priority_func);

        res_treeset = METHOD(T, add) (res_treeset, value, comparator, priority_func);
    }

    treeset1 = new_treeset1; treeset2 = new_treeset2;
    return res_treeset;
}

TYPE(T, datum_t) METHOD(T, inter)(TYPE(T, datum_t) treeset1, TYPE(T, datum_t) treeset2, int (*comparator)(datum_t, datum_t), int (*priority_func)(datum_t)){
    datum_t value;
    TYPE(T, datum_t) new_treeset2;
    TYPE(T, datum_t) res_treeset;

    while (!METHOD(T, is_empty)(treeset2)){
        treeset2 = METHOD(treap, pop_small) (treeset2, &value);
        new_treeset2 = METHOD(T, add) (treeset1, value, comparator, priority_func);

        if (METHOD(T, contains)(treeset1, value, comparator)){
            res_treeset = METHOD(T, add) (res_treeset, value, comparator, priority_func);
        }
    }

    treeset2 = new_treeset2;
    return res_treeset;
}

TYPE(T, datum_t) METHOD(T, delete)(TYPE(T, datum_t) treeset, void (*destructor)(datum_t)){return METHOD(treap, delete)(treeset, destructor);}

void METHOD(T, print)(TYPE(T, datum_t) treeset, void (*printer)(datum_t)){METHOD(treap, print) (treeset, printer);}








#undef T

#endif