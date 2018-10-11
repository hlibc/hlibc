static inline long __internal_syscall(long number, long a, long b, long c, long d, long e, long f)
{
	unsigned long ret;
	__asm__ __volatile__ ("pushl %7 ; pushl %%ebp ; mov 4(%%esp),%%ebp ; int $128 ; popl %%ebp ; popl %%ecx"
		: "=a"(ret) : "a"(number), "b"(a), "c"(b), "d"(c), "S"(d), "D"(e), "g"(f) : "memory");
	return ret;
}

#include <operating_system.h>

