#include <stdlib.h>
#include <signal.h>
#include <errno.h>
#include "syscall.h"
#include "libc.h"

void __restore(), __restore_rt();

int __libc_sigaction(int sig, const struct sigaction *sa, struct sigaction *old)
{ 
	return 0;
}

int __sigaction(int sig, const struct sigaction *sa, struct sigaction *old)
{
}

weak_alias(__sigaction, sigaction);
