#include <pthread.h>
#include <time.h>
#include <errno.h>
#include "futex.h"
#include "syscall.h"

static int do_wait(volatile int *addr, int val,
	clockid_t clk, const struct timespec *at, int priv)
{ 
	return 0;
}

int __timedwait(volatile int *addr, int val,
	clockid_t clk, const struct timespec *at,
	void (*cleanup)(void *), void *arg, int priv)
{
	return 0;
}
