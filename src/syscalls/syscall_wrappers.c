#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <poll.h>
#include <signal.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/syscall.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/utsname.h>
#include <time.h>
#include <unistd.h>
#include "../internal/internal.h"

extern char **__environ;

long __syscall_ret(unsigned long);

off_t lseek(int fd, off_t offset, int whence)
{
#ifdef SYS__llseek
	off_t result;
	return __syscall(SYS__llseek, fd, offset>>32, offset, &result, whence) ? -1 : result;
#else
	return __syscall(SYS_lseek, fd, offset, whence);
#endif
}

pid_t tcgetpgrp(int fd)
{
	int pgrp;
	if (ioctl(fd, TIOCGPGRP, &pgrp) < 0)
		return -1;
	return pgrp;
}

int tcsetpgrp(int fd, pid_t pgrp)
{
	int pgrp_int = pgrp;
	return ioctl(fd, TIOCSPGRP, &pgrp_int);
}

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

void __assert_fail(const char *expr, const char *file, int line, const char *func)
{
	fprintf(stderr, "Assertion failed: %s (%s: %s: %d)\n", expr, file, func, line);
	fflush(NULL);
	abort();
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
		return __syscall(SYS_fcntl, fd, cmd, arg);
	if (cmd == F_GETOWN)
		return __syscall(SYS_fcntl, fd, cmd, arg);
	return __syscall(SYS_fcntl, fd, cmd, arg);
}

int execvp(const char *file, char *const argv[])
{
	const char *p, *z, *path = getenv("PATH");
	size_t l, k;

	errno = ENOENT;
	if (!*file)
		return -1;

	if (strchr(file, '/'))
		return execv(file, argv);

	if (!path)
		path = "/usr/local/bin:/bin:/usr/bin";
	k = strnlen(file, NAME_MAX+1);
	if (k > NAME_MAX) {
		errno = ENAMETOOLONG;
		return -1;
	}
	l = strnlen(path, PATH_MAX-1)+1;

	for(p=path; ; p=z) {
		char b[l+k+1];
		z = strchr(p, ':');
		if (!z)
			z = p+strlen(p);
		if (z-p >= l) {
			if (!*z++)
				break;
			continue;
		}
		memcpy(b, p, z-p);
		b[z-p] = '/';
		memcpy(b+(z-p)+(z>p), file, k+1);
		execv(b, argv);
		if (errno != ENOENT)
			return -1;
		if (!*z++)
			break;
	}
	return -1;
}

int clock_gettime(clockid_t clk, struct timespec *ts)
{ 
	int r = __syscall(SYS_clock_gettime, clk, ts);
	if (!r)
		return r;
	if (r == -ENOSYS) {
		if (clk == CLOCK_REALTIME) {
			__syscall(SYS_gettimeofday, clk, ts, 0);
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

