
static inline long __syscall6(long __n, long __a1, long __a2, long __a3, long __a4, long __a5, long __a6)
{
	unsigned long __ret;
	register long __r10 __asm__("r10") = __a4;
	register long __r8 __asm__("r8") = __a5;
	register long __r9 __asm__("r9") = __a6;
	__asm__ __volatile__ ("syscall" : "=a"(__ret) : "a"(__n), "D"(__a1), "S"(__a2),
						  "d"(__a3), "r"(__r10), "r"(__r8), "r"(__r9) : "rcx", "r11", "memory");
	return __ret;
}

#include <operating_system.h>
