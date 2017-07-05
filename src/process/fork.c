#include <unistd.h>
#include "syscall.h"
#include "libc.h"
#include "pthread_impl.h"

static void dummy(int x)
{
}

weak_alias(dummy, __fork_handler);

pid_t fork(void)
{
	pid_t ret;
	__fork_handler(-1);
	ret = syscall(SYS_fork);
	/* removed thrd stuff here CM Graff */






	__fork_handler(!ret);
	return ret;
}
