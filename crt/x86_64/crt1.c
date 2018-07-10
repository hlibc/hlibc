int __attribute__((__noreturn__)) __libc_start_main(
	int (*main)(int, char **, char **), int argc, char **argv);

void _start(void)
{
	int (*main)(int, char **, char **);
	long argc;
	char **argv;
	long blank = 0;

	__asm__ __volatile__
		("xor  %%rbp , %%rbp \n" /* rbp:undefined -> mark as zero 0 (ABI) */
		 "pop  %3	    \n"
		 "pop  %1	    \n" /* 2nd arg: argc */
		 "mov  %%rsp , %2    \n" /* 3rd arg: argv */
		 "andq $-16  , %%rsp \n" /* align stack pointer */
		 "mov  $main , %0    \n" /* 1st arg: application entry ip */
		 : "=r" (main),
		   "=r" (argc),
		   "=r" (argv),
		   "=r" (blank)
		 );
	__libc_start_main(main, argc, argv);

	for(;;);
}
