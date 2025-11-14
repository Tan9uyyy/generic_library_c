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

TYPE(T, datum_t) METHOD(T, datum_t, new)(){return NULL;}

int METHOD(T, datum_t, is_empty)(TYPE(T, datum_t) treeset){return NULL == treeset;}

int METHOD(T, datum_t, contains)(TYPE(T, datum_t) treeset, datum_t value, int (*comparator)(datum_t, datum_t)){
    if (NULL == treeset){return 0;}
    
    return METHOD(treap, datum_t, contains)(treeset, value, comparator);
}

TYPE(T, datum_t) METHOD(T, datum_t, add)(TYPE(T, datum_t) treeset, datum_t value, int (*comparator)(datum_t, datum_t), int (*priority_func)(datum_t)){
    if (!METHOD(T, datum_t, contains)(treeset, value, comparator)){
        return METHOD(treap, datum_t, push)(treeset, value, comparator, priority_func);
    }

    return treeset;
}

datum_t METHOD(T, datum_t, upper_bound)(TYPE(T, datum_t) treeset){return METHOD(treap, datum_t, max)(treeset);}

datum_t METHOD(T, datum_t, lower_bound)(TYPE(T, datum_t) treeset){return METHOD(treap, datum_t, min)(treeset);}

TYPE(T, datum_t) METHOD(T, datum_t, remove_max)(TYPE(T, datum_t) treeset){datum_t buffer = 0; return METHOD(treap, datum_t, pop_big) (treeset, &buffer);}

TYPE(T, datum_t) METHOD(T, datum_t, remove_min)(TYPE(T, datum_t) treeset){datum_t buffer = 0; return METHOD(treap, datum_t, pop_small) (treeset, &buffer);}

TYPE(T, datum_t) METHOD(T, datum_t, reunion)(TYPE(T, datum_t) *treeset1, TYPE(T, datum_t) *treeset2, int (*comparator)(datum_t, datum_t), int (*priority_func)(datum_t)){
    datum_t value;
    TYPE(T, datum_t) new_treeset1 = METHOD(T, datum_t, new)();
    TYPE(T, datum_t) new_treeset2 = METHOD(T, datum_t, new)();
    TYPE(T, datum_t) res_treeset = METHOD(T, datum_t, new)();

    while (!METHOD(T, datum_t, is_empty)(*treeset1)){
        *treeset1 = METHOD(treap, datum_t, pop_small) (*treeset1, &value);
        new_treeset1 = METHOD(T, datum_t, add) (new_treeset1, value, comparator, priority_func);

        res_treeset = METHOD(T, datum_t, add) (res_treeset, value, comparator, priority_func);
    }

    while (!METHOD(T, datum_t, is_empty)(*treeset2)){
        *treeset2 = METHOD(treap, datum_t, pop_big) (*treeset2, &value);
        new_treeset2 = METHOD(T, datum_t, add) (new_treeset2, value, comparator, priority_func);

        res_treeset = METHOD(T, datum_t, add) (res_treeset, value, comparator, priority_func);
    }

    *treeset1 = new_treeset1; *treeset2 = new_treeset2;
    return res_treeset;
}

TYPE(T, datum_t) METHOD(T, datum_t, inter)(TYPE(T, datum_t) *treeset1, TYPE(T, datum_t) *treeset2, int (*comparator)(datum_t, datum_t), int (*priority_func)(datum_t)){
    datum_t value;
    TYPE(T, datum_t) new_treeset2 = METHOD(T, datum_t, new)();
    TYPE(T, datum_t) res_treeset = METHOD(T, datum_t, new)();

    while (!METHOD(T, datum_t, is_empty)(*treeset2)){
        *treeset2 = METHOD(treap, datum_t, pop_small) (*treeset2, &value);
        new_treeset2 = METHOD(T, datum_t, add) (new_treeset2, value, comparator, priority_func);

        if (METHOD(T, datum_t, contains)(*treeset1, value, comparator)){
            res_treeset = METHOD(T, datum_t, add) (res_treeset, value, comparator, priority_func);
        }
    }

    *treeset2 = new_treeset2;
    return res_treeset;
}

TYPE(T, datum_t) METHOD(T, datum_t, delete)(TYPE(T, datum_t) treeset, void (*destructor)(datum_t)){return METHOD(treap, datum_t, delete)(treeset, destructor);}

void METHOD(T, datum_t, print)(TYPE(T, datum_t) treeset, void (*printer)(datum_t)){METHOD(treap, datum_t, print) (treeset, printer);}








#undef T

#endif