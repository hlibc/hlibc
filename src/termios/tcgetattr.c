#include <sys/syscall.h>
#include <termios.h>
#include <sys/ioctl.h>

int tcgetattr(int fildes, struct termios *termios_p)
{
        if (ioctl(fildes, TCGETS, termios_p))
                return -1;
        return 0;
}
