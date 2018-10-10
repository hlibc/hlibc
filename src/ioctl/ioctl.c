#include <sys/ioctl.h>
#include <sys/syscall.h>
#include <stdarg.h>

int ioctl(int fildes, int request, ... /* arg */)
{
        void *argument;
        va_list i;
        va_start(i, request);
        argument = va_arg(i, void *);
        va_end(i);
        return __syscall(SYS_ioctl, fildes, request, argument);
}
