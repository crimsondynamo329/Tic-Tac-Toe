#ifndef DEBUG_UTILS
#define DEBUG_UTILS

// Define debug output methods or leave empty
#ifdef DEBUG
    #define ANY_DEBUG
    #define DBG_OUT( arg )  cerr << arg
    #define DBGV_OUT( arg ) 
#elif defined DEBUGV
    #define ANY_DEBUG
    #define DBG_OUT( arg )  cerr << arg
    #define DBGV_OUT( arg ) cerr << arg
#else
    #define DBG_OUT( arg )
    #define DBGV_OUT( arg )
#endif

#endif
