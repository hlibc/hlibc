#include <unistd.h>
#include "syscall.h"

int rename(const char *o, const char *n)
{
	return syscall(SYS_rename, o, n);
}

