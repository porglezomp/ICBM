#ifndef DEBUG_H
#define DEBUG_H 1

#define	DEBUG_ENABLED	false

#if DEBUG_ENABLED
#define DEBUG(A)	{ A; }
#else
#define	DEBUG(A)
#endif

#endif
