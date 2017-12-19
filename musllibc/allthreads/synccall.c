#include "pthread_impl.h"
#include <semaphore.h>

static struct chain {
	struct chain *next;
	sem_t sem, sem2;
} *head, *cur;

static void (*callback)(void *), *context;
static int chainlen;
static sem_t chainlock, chaindone;

static void handler(int sig, siginfo_t *si, void *ctx)
{
}

void __synccall_wait()
{ 
}

void __synccall(void (*func)(void *), void *ctx)
{
}

void __synccall_lock()
{ 
}

void __synccall_unlock()
{ 
}
