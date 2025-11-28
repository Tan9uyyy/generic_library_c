#include <../include/libellul/type/treap.h>

#ifdef treap_datum_t
    #include <../include/libellul/type/treap/treap-implementation.h>
    #undef treap_datum_t
#endif

#define treap_datum_t int
#include <../include/libellul/type/treap/treap-implementation.h>
