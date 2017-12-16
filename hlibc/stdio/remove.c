#include <stdio.h>
#include <errno.h>
#include "syscall.h"

int remove(const char *path)
{
	unlink(path);
	return rmdir(path);
}
