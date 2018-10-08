#define __SYSCALL_LL_E(x) \
((union { long long ll; long l[2]; }){ .ll = x }).l[0], \
((union { long long ll; long l[2]; }){ .ll = x }).l[1]
#define __SYSCALL_LL_O(x) __SYSCALL_LL_E((x))

static inline long __syscall0(long __n)
{
	unsigned long __ret;
	__asm__ __volatile__ ("int $128" : "=a"(__ret) : "a"(__n) : "memory");
	return __ret;
}

static inline long __syscall1(long __n, long __a1)
{
	unsigned long __ret;
	__asm__ __volatile__ ("int $128" : "=a"(__ret) : "a"(__n), "b"(__a1) : "memory");
	return __ret;
}

static inline long __syscall2(long __n, long __a1, long __a2)
{
	unsigned long __ret;
	__asm__ __volatile__ ("int $128" : "=a"(__ret) : "a"(__n), "b"(__a1), "c"(__a2) : "memory");
	return __ret;
}

static inline long __syscall3(long __n, long __a1, long __a2, long __a3)
{
	unsigned long __ret;
	__asm__ __volatile__ ("int $128" : "=a"(__ret) : "a"(__n), "b"(__a1), "c"(__a2), "d"(__a3) : "memory");
	return __ret;
}

static inline long __syscall4(long __n, long __a1, long __a2, long __a3, long __a4)
{
	unsigned long __ret;
	__asm__ __volatile__ ("int $128" : "=a"(__ret) : "a"(__n), "b"(__a1), "c"(__a2), "d"(__a3), "S"(__a4) : "memory");
	return __ret;
}

static inline long __syscall5(long __n, long __a1, long __a2, long __a3, long __a4, long __a5)
{
	unsigned long __ret;
	__asm__ __volatile__ ("int $128" : "=a"(__ret) : "a"(__n), "b"(__a1), "c"(__a2), "d"(__a3), "S"(__a4), "D"(__a5) : "memory");
	return __ret;
}

static inline long __syscall6(long __n, long __a1, long __a2, long __a3, long __a4, long __a5, long __a6)
{
	unsigned long __ret;
	__asm__ __volatile__ ("pushl %7 ; pushl %%ebp ; mov 4(%%esp),%%ebp ; int $128 ; popl %%ebp ; popl %%ecx"
		: "=a"(__ret) : "a"(__n), "b"(__a1), "c"(__a2), "d"(__a3), "S"(__a4), "D"(__a5), "g"(__a6) : "memory");
	return __ret;
}

#include <operating_system.h>

#define __socketcall(nm,a,b,c,d,e,f) syscall(SYS_socketcall, __SC_##nm, \
    ((long [6]){ (long)a, (long)b, (long)c, (long)d, (long)e, (long)f }))

