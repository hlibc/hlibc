#include <sys/stat.h>
#include <fcntl.h>
#include <sys/syscall.h>
#include <stdarg.h>

int open(const char *filename, int oflag, ...)
{
        va_list i;
        mode_t variadic_mode;
        va_start(i, oflag);
        variadic_mode = va_arg(i, mode_t);
        va_end(i);
#ifdef SYS_open
        return syscall(SYS_open, filename, oflag|O_LARGEFILE, variadic_mode);
#else
        return syscall(SYS_openat, AT_FDCWD, filename, oflag|O_LARGEFILE, variadic_mode);
#endif
}

