void __attribute__((weak)) _init(int, char **, char **);
void __attribute__((weak)) _fini(void);

int __libc_start_main(
	int (*main)(int, char **, char **), int argc, char **argv,
	int (*init)(int, char **, char **), void (*fini)(void),
	void (*ldso_fini)(void));

void _start(void)
{
	register int (*__main)(int, char **, char **) __asm__("rdi");
	register long __argc                          __asm__("rsi");
	register char **__argv                        __asm__("rdx");
	register int (*__init)(int, char **, char **) __asm__("rcx");
	register void (*__fini)(void)                 __asm__("r8");
	register void (*__ldso_fini)(void)            __asm__("r9");
	
	__asm__ __volatile__
		("xor  %%rbp , %%rbp \n" /* rbp:undefined -> mark as zero 0 (ABI) */
		 "mov  %%rdx , %5    \n" /* 6th arg: ptr to register with atexit() */
		 "pop  %1            \n" /* 2nd arg: argc */
		 "mov  %%rsp , %2    \n" /* 3rd arg: argv */
		 "andq $-16  , %%rsp \n" /* align stack pointer */
		 "mov  $_fini, %4    \n" /* 5th arg: fini/dtors function */
		 "mov  $_init, %3    \n" /* 4th arg: init/ctors function */
		 "mov  $main , %0    \n" /* 1st arg: application entry ip */
		 : "=r" (__main),
		   "=r" (__argc),
		   "=r" (__argv),
		   "=r" (__init),
		   "=r" (__fini),
		   "=r" (__ldso_fini)
		 );
	__libc_start_main(__main, __argc, __argv, __init, __fini, __ldso_fini);

	for(;;);
}
