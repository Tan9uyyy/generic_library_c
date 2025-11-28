#include <../include/libellul/type/stack.h>

#ifdef stack_datum_t
    #include <../include/libellul/type/stack/stack-implementation.h>
    #undef stack_datum_t
#endif

#define stack_datum_t int
#include <../include/libellul/type/stack/stack-implementation.h>