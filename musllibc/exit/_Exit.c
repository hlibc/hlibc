#include <stdlib.h>
#include "syscall.h"

void _Exit(int ec)
{
	syscall(SYS_exit_group, ec);
	syscall(SYS_exit, ec);
}
