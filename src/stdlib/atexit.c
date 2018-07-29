#include <sys/syscall.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#define COUNT 32

static struct fl
{
	void (*f[COUNT])(void *);
	void *a[COUNT];
} builtin, *head;

/*
 * __funcs_on_exit: Iterate through the array of function pointers stored by
 * the atexit() function.
 */
void __funcs_on_exit()
{
	int i;
	void (*func)(void *), *arg;

	/* Count down to the last function introduced */
	for (i=COUNT-1; i>=0 && !head->f[i]; i--)
		;

	/* Run each function in descending order */
	for (; i>=0; i--) {
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

static void _Exit(int ec)
{
	__syscall(SYS_exit_group, ec);
	__syscall(SYS_exit, ec);
}

void exit(int code)
{
	__funcs_on_exit();
	fflush(NULL);

	_Exit(code);
	for(;;);
}

