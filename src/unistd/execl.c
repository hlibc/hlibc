#include <sys/syscall.h>
#include <stdarg.h>
#include <limits.h>
#include <stdio.h>

extern char **__environ;

int execl(const char *path, const char *arg, ...)
{
	char *argv[ARG_MAX];
        va_list j;
	int i = 0;

        va_start(j, arg);
	argv[0] = (char *)arg;
        for (; va_arg(j, const char *); ++i)
              argv[i] = va_arg(j, char *);
	argv[i] = NULL;
        va_end(j);
	return __syscall(SYS_execve, path, argv, __environ);
}

