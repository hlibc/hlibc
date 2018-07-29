/* Copyright 2018, Adrian Parvin D. Ouano */

int __attribute__((__noreturn__)) __libc_start_main(
	int (*main)(int, char **, char **), int argc, char **argv);
int atexit(void (*)(void));


void _start(void)
{
	int (*main)(int, char **, char **);
	long argc;
	char **argv = 0;
	long blank = 0;
	int (*atexit)(void (*)(void));

	__asm__ __volatile__
		("xor %%rbp, %%rbp	\n"/* rbp:undefined -> mark as zero 0 (ABI) */
		"mov %%rdx, $3		\n"/* 6th arg: ptr to register with atexit() */
		"pop %1			\n"/* 2nd arg: argc */
		"mov %%rsp, %2		\n"/* 3rd arg: argv */
		"andq $-16, %%rsp	\n"/* align stack pointer */
		"mov $main, %%rdi		\n"/* 1st arg: application entry ip */
		:	"=r" (main),
			"=r" (argc),
			"=r" (argv),
			"=r" (atexit)
		);
	__libc_start_main(main, argc, argv);

	for(;;);
}
