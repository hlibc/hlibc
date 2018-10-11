#include <sys/syscall.h>
#include <stdio.h>
#include <stdint.h>

static int __internal_atexit(void (*f)(void), int fireoff)
{
	static void (*funcs[32])(void);
	static size_t i = 0;

	if (i == 32)
		return 1;

	if (fireoff == 0)
	{
		funcs[i++] = f;
		return 0;
	}
	for (;i>0;)
		funcs[--i]();

	return 0;
}

int atexit(void (*f)(void))
{
	return __internal_atexit(f, 0);
}

void exit(int status)
{
	__internal_atexit(NULL, 1);
	fflush(NULL);
	_Exit(status);
	for(;;)
		;
}

void _Exit(int status)
{
#ifdef SYS_exit_group
	syscall(SYS_exit_group, status);
#endif
	syscall(SYS_exit, status);
}

void _exit(int status)
{
	_Exit(status);
}

