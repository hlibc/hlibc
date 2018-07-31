#include <sys/syscall.h>
#include <stdio.h>
#include <stdint.h>

#define COUNT 32

static struct fl
{
	struct fl *next;
	void (*f[COUNT])(void *);
	void *a[COUNT];
} builtin, *head;

/*
 * __funcs_on_exit: Iterate through the array of function pointers collected by
 * the atexit() function.
 */
void __funcs_on_exit()
{
	int i;
	void (*func)(void *), *arg;

	if (!head)
		return;

	for (i=COUNT-1; i>=0 && !head->f[i]; i--)
		;

	if (i>=0)
		for (; i>=0 && head->f[i]; i--) {
			func = head->f[i];
			arg = head->a[i];
			head->f[i] = 0;
			func(arg);
		}
}

/*
 * __cxa_atexit: Add the given function pointer to the array of function
 * pointers that are called by the exit of the main() function.
 */
static int __cxa_atexit(void (*func)(void *), void *arg)
{
	int i;
	/* Defer initialization of head so it can be in BSS */
	if (!head) head = &builtin;

	/* Append function to the list. */
	for (i=0; i<COUNT && head->f[i]; i++)
		;

	/* If there is still a slot available, use it. */
	if (i < COUNT) {
		head->f[i] = func;
		head->a[i] = arg;
	}
	return 0;
}

static void call(void *p)
{
	((void (*)(void))(uintptr_t)p)();
}

int atexit(void (*func)(void))
{
	return __cxa_atexit(call, (void *)(uintptr_t)func);
}

void __funcs_on_exit();

void exit(int code)
{
	__funcs_on_exit();
	fflush(NULL);
	_Exit(code);
	for(;;);
}

void _Exit(int ec)
{
	__syscall(SYS_exit_group, ec);
	__syscall(SYS_exit, ec);
}

void _exit(int status)
{
	_Exit(status);
}

