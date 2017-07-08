#include <unistd.h>
#include "syscall.h"
#include "libc.h"

int pause(void)
{
	return syscall(SYS_pause);
}
