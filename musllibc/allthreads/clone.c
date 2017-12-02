#include <errno.h>
#include "libc.h"

int clone(int (*func)(void *), void *stack, int flags, void *arg, ...)
{
	errno = ENOSYS;
	return -1;
}

