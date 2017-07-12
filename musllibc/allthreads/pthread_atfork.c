#include <pthread.h>
#include "libc.h"

static struct atfork_funcs {
	void (*prepare)(void);
	void (*parent)(void);
	void (*child)(void);
	struct atfork_funcs *prev, *next;
} *funcs;

static int lock[2];

void __fork_handler(int who)
{ 
}

int pthread_atfork(void (*prepare)(void), void (*parent)(void), void (*child)(void))
{ 
	return 0;
}
