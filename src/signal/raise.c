/*
	raise.c
	Copyright (c), zhiayang
*/

#include <signal.h>
#include <unistd.h>

int raise(int sig)
{
	/* raise just does kill(sig) on the current process. */
	kill(getpid(), sig);
}
