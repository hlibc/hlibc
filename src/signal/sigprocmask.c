#include <signal.h>
#include <errno.h>

int sigprocmask(int how, const sigset_t *set, sigset_t *old)
{
	/* removed thrd support CM Graff */
	return 0; 
}
