#ifndef _HEAP_H__
#define _HEAP_H__

#ifdef heap_datum_t
    #include "heap/heap-export-def.h"
    #undef heap_datum_t
#endif

#define heap_datum_t int
#include "heap/heap-export-def.h"


#endif