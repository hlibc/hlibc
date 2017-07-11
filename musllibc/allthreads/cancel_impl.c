#include "pthread_impl.h"

void __cancel()
{
}

long __syscall_cp_asm(volatile void *, long, long, long, long, long, long, long);

long (__syscall_cp)(long nr, long u, long v, long w, long x, long y, long z)
{
	return 0;
}

static void _sigaddset(sigset_t *set, int sig)
{ 
}

static void cancel_handler(int sig, siginfo_t *si, void *ctx)
{ 
}

void __testcancel()
{ 
}

static void init_cancellation()
{ 
}

int pthread_cancel(pthread_t t)
{
	return 0;
}
