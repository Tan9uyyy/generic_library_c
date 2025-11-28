#include <../include/libellul/type/treeset.h>

#ifdef treeset_datum_t
    #include <../include/libellul/type/treeset/treeset-implementation.h>
    #undef treeset_datum_t
#endif

#define treeset_datum_t int
#include <../include/libellul/type/treeset/treeset-implementation.h>