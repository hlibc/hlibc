static inline long __internal_syscall(long number, long a, long b, long c, long d, long e, long f)
{
	unsigned long ret;
	register long g __asm__("r8") = e;
	register long h __asm__("r9") = f;
	register long i __asm__("r10") = d;
	__asm__ __volatile__ ("syscall" : "=a"(ret) : "a"(number), "D"(a), "S"(b),
						  "d"(c), "r"(i), "r"(g), "r"(h) : "rcx", "r11", "memory");
	return ret;
}

#include <operating_system.h>
