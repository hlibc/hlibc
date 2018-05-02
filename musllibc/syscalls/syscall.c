#include <errno.h>
#include <fcntl.h>

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/ioctl.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <sys/uio.h>
#include <sys/utsname.h>
#include <termios.h>
#include <unistd.h>

#include "syscall.h"
#include "libc.h"
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

