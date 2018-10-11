static inline long __internal_syscall(long __n, long __a1, long __a2, long __a3, long __a4, long __a5, long __a6)
{
	unsigned long __ret;
	__asm__ __volatile__ ("pushl %7 ; pushl %%ebp ; mov 4(%%esp),%%ebp ; int $128 ; popl %%ebp ; popl %%ecx"
		: "=a"(__ret) : "a"(__n), "b"(__a1), "c"(__a2), "d"(__a3), "S"(__a4), "D"(__a5), "g"(__a6) : "memory");
	return __ret;
}

#include <operating_system.h>

