#ifndef _INTERFACE_H__
#define _INTERFACE_H__

#include "generics.h"

#define TYPENAME(T, datum_t)    GEN_SYM(T, datum_t)
#define TYPE(T, datum_t)        GEN_SYM(TYPENAME(T, datum_t), t)
#define METHOD(T, datum_t, name)            GEN_SYM(TYPENAME(T, datum_t), name)

#endif