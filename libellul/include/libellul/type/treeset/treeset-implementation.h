#ifndef _TREESET_IMPLEMENTATION_H__
#define _TREESET_IMPLEMENTATION_H__

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#include "treeset-export-def.h"

#ifdef T
#undef T
#endif
#define T treeset

typedef TYPE(treap, treeset_datum_t) TYPE(T, treeset_datum_t);

TYPE(T, treeset_datum_t) METHOD(T, treeset_datum_t, new)(){return NULL;}

int METHOD(T, treeset_datum_t, is_empty)(TYPE(T, treeset_datum_t) treeset){return NULL == treeset;}

int METHOD(T, treeset_datum_t, contains)(TYPE(T, treeset_datum_t) treeset, treeset_datum_t value, int (*comparator)(treeset_datum_t, treeset_datum_t)){
    if (NULL == treeset){return 0;}
    
    return METHOD(treap, treeset_datum_t, contains)(treeset, value, comparator);
}

TYPE(T, treeset_datum_t) METHOD(T, treeset_datum_t, add)(TYPE(T, treeset_datum_t) treeset, treeset_datum_t value, int (*comparator)(treeset_datum_t, treeset_datum_t), int (*priority_func)(treeset_datum_t)){
    if (!METHOD(T, treeset_datum_t, contains)(treeset, value, comparator)){
        return METHOD(treap, treeset_datum_t, push)(treeset, value, comparator, priority_func);
    }

    return treeset;
}

treeset_datum_t METHOD(T, treeset_datum_t, upper_bound)(TYPE(T, treeset_datum_t) treeset){return METHOD(treap, treeset_datum_t, max)(treeset);}

treeset_datum_t METHOD(T, treeset_datum_t, lower_bound)(TYPE(T, treeset_datum_t) treeset){return METHOD(treap, treeset_datum_t, min)(treeset);}

TYPE(T, treeset_datum_t) METHOD(T, treeset_datum_t, remove_max)(TYPE(T, treeset_datum_t) treeset){treeset_datum_t buffer = 0; return METHOD(treap, treeset_datum_t, pop_big) (treeset, &buffer);}

TYPE(T, treeset_datum_t) METHOD(T, treeset_datum_t, remove_min)(TYPE(T, treeset_datum_t) treeset){treeset_datum_t buffer = 0; return METHOD(treap, treeset_datum_t, pop_small) (treeset, &buffer);}

TYPE(T, treeset_datum_t) METHOD(T, treeset_datum_t, reunion)(TYPE(T, treeset_datum_t) *treeset1, TYPE(T, treeset_datum_t) *treeset2, int (*comparator)(treeset_datum_t, treeset_datum_t), int (*priority_func)(treeset_datum_t)){
    treeset_datum_t value;
    TYPE(T, treeset_datum_t) new_treeset1 = METHOD(T, treeset_datum_t, new)();
    TYPE(T, treeset_datum_t) new_treeset2 = METHOD(T, treeset_datum_t, new)();
    TYPE(T, treeset_datum_t) res_treeset = METHOD(T, treeset_datum_t, new)();

    while (!METHOD(T, treeset_datum_t, is_empty)(*treeset1)){
        *treeset1 = METHOD(treap, treeset_datum_t, pop_small) (*treeset1, &value);
        new_treeset1 = METHOD(T, treeset_datum_t, add) (new_treeset1, value, comparator, priority_func);

        res_treeset = METHOD(T, treeset_datum_t, add) (res_treeset, value, comparator, priority_func);
    }

    while (!METHOD(T, treeset_datum_t, is_empty)(*treeset2)){
        *treeset2 = METHOD(treap, treeset_datum_t, pop_big) (*treeset2, &value);
        new_treeset2 = METHOD(T, treeset_datum_t, add) (new_treeset2, value, comparator, priority_func);

        res_treeset = METHOD(T, treeset_datum_t, add) (res_treeset, value, comparator, priority_func);
    }

    *treeset1 = new_treeset1; *treeset2 = new_treeset2;
    return res_treeset;
}

TYPE(T, treeset_datum_t) METHOD(T, treeset_datum_t, inter)(TYPE(T, treeset_datum_t) *treeset1, TYPE(T, treeset_datum_t) *treeset2, int (*comparator)(treeset_datum_t, treeset_datum_t), int (*priority_func)(treeset_datum_t)){
    treeset_datum_t value;
    TYPE(T, treeset_datum_t) new_treeset2 = METHOD(T, treeset_datum_t, new)();
    TYPE(T, treeset_datum_t) res_treeset = METHOD(T, treeset_datum_t, new)();

    while (!METHOD(T, treeset_datum_t, is_empty)(*treeset2)){
        *treeset2 = METHOD(treap, treeset_datum_t, pop_small) (*treeset2, &value);
        new_treeset2 = METHOD(T, treeset_datum_t, add) (new_treeset2, value, comparator, priority_func);

        if (METHOD(T, treeset_datum_t, contains)(*treeset1, value, comparator)){
            res_treeset = METHOD(T, treeset_datum_t, add) (res_treeset, value, comparator, priority_func);
        }
    }

    *treeset2 = new_treeset2;
    return res_treeset;
}

TYPE(T, treeset_datum_t) METHOD(T, treeset_datum_t, delete)(TYPE(T, treeset_datum_t) treeset, void (*destructor)(treeset_datum_t)){return METHOD(treap, treeset_datum_t, delete)(treeset, destructor);}

void METHOD(T, treeset_datum_t, print)(TYPE(T, treeset_datum_t) treeset, void (*printer)(treeset_datum_t)){METHOD(treap, treeset_datum_t, print) (treeset, printer);}








#undef T

#endif