#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <limits.h> 
#include <signal.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h> 
#include <sys/syscall.h>
#include <sys/time.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#include "../internal/internal.h"

extern char **__environ;

char *getenv(const char *name)
{
	int i;
	size_t l = strlen(name);
	if (!__environ || !*name || strchr(name, '='))
		return NULL;
	for (i=0; __environ[i] && (strncmp(name, __environ[i], l)
		|| __environ[i][l] != '='); i++);
	if (__environ[i])
		return __environ[i] + l+1;
	return NULL;
}

void abort(void)
{
	//raise(SIGABRT);
	for (;;);
}

int raise(int sig)
{ 
	return sig;
}

int fcntl(int fd, int cmd, ...)
{
	long arg;
	va_list ap;
	va_start(ap, cmd);
	arg = va_arg(ap, long);
	va_end(ap);
	if (cmd == F_SETFL)
		arg |= O_LARGEFILE;
	if (cmd == F_SETLKW)
		return syscall(SYS_fcntl, fd, cmd, arg);
	if (cmd == F_GETOWN)
		return syscall(SYS_fcntl, fd, cmd, arg);
	return syscall(SYS_fcntl, fd, cmd, arg);
}

int clock_gettime(clockid_t clk, struct timespec *ts)
{ 
	int r = syscall(SYS_clock_gettime, clk, ts);
	if (!r)
		return r;
	if (r == -ENOSYS) {
		if (clk == CLOCK_REALTIME) {
			syscall(SYS_gettimeofday, clk, ts, 0);
			ts->tv_nsec = (int)ts->tv_nsec * 1000;
			return 0;
		}
		r = -EINVAL;
	}
	errno = -r;
	return -1;
}

time_t time(time_t *t)
{
	struct timespec ts;
	clock_gettime(CLOCK_REALTIME, &ts);
	if (t) *t = ts.tv_sec;
	return ts.tv_sec;
}

