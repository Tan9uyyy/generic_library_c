
#if defined( T_IMPL_HASHTABLE_LINEAR ) || defined( T_IMPL_HASHTABLE_LINEAR_NO_TOMBSTONES )
#include <libellul/structure/hashtable/linear.h>
#elif defined( T_IMPL_HASHTABLE_ROBIN_HOOD )
#include <libellul/structure/hashtable/robin-hood.h>
#elif defined( T_IMPL_HASHTABLE_CLOSED_ADDRESSING ) || defined( T_IMPL_HASHTABLE_CLOSED_ADDRESSING_MOVE_TO_FRONT )
#include <libellul/structure/hashtable/closed_addressing.h>
#else /* Default hashtable */
#include <libellul/structure/hashtable/linear.h>
#endif

/* Add any other prototypes below depending on the data structure capabilities */



#undef T_IMPL_HASHTABLE
