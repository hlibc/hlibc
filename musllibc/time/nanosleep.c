#include <unistd.h>
#include <time.h>
#include "syscall.h"
#include "libc.h"

int nanosleep(const struct timespec *req, struct timespec *rem)
{
	return syscall(SYS_nanosleep, req, rem);
}
