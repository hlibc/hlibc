#include <stdarg.h>
#include <errno.h>
#include <unistd.h>

long __syscall_ret(unsigned long r)
{
        if (r > -4096UL) {
                errno = -r;
                return -1;
        }
        return r;
}

#undef syscall
long syscall(long n, ...)
{
        va_list ap;
        long a, b, c, d, e, f;
        va_start(ap, n);
        a=va_arg(ap, long);
        b=va_arg(ap, long);
        c=va_arg(ap, long);
        d=va_arg(ap, long);
        e=va_arg(ap, long);
        f=va_arg(ap, long);
        va_end(ap);
        return __syscall_ret(syscall(n, a, b, c, d, e, f));
}

