#include <unistd.h>
#include <sys/syscall.h>
#include <stdarg.h>
#include <errno.h>
#undef syscall
long syscall(long number, ...)
{
	long ret = 0;
        long a, b, c, d, e, f;
        va_list i;
        va_start(i, number);
        a=va_arg(i, long);
        b=va_arg(i, long);
        c=va_arg(i, long);
        d=va_arg(i, long);
        e=va_arg(i, long);
        f=va_arg(i, long);
        va_end(i);
	ret = __syscall6(number, a, b, c, d, e, f);
	if (ret > -4096UL) {
                errno = -ret;
                return -1;
        }

        return ret;
}
