#ifndef _LIST_H__
#define _LIST_H__

#ifdef list_datum_t
    #include "list/list-export-def.h"
    #undef list_datum_t
#endif

#define list_datum_t int
#include "list/list-export-def.h"


#endif