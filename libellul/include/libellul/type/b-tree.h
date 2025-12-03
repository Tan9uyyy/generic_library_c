#ifndef _B_TREE_H__
#define _B_TREE_H__

#ifdef b_tree_datum_t
    #include "b-tree/b-tree-export-def.h"
    #include "b-tree/b-tree-implementation.h"
    #undef b_tree_datum_t
#endif

#define b_tree_datum_t int
#include "b-tree/b-tree-export-def.h"
#include "b-tree/b-tree-implementation.h"


#endif