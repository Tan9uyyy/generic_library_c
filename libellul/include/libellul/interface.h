#ifndef _INTERFACE_H__
#define _INTERFACE_H__

#include "generics.h"

#ifndef T
    #error "Undefined data structure !"
#endif

#ifndef datum_t
    #error "Undefined datum type !"
#endif

#define TYPENAME(T, datum_t)    GEN_SYM(T, datum_t)
#define TYPE(T, datum_t)        GEN_SYM(TYPENAME(T, datum_t), t)
#define METHOD(T, name)            GEN_SYM(TYPENAME(T, datum_t), name)

#endif