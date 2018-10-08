#include <sys/syscall.h>
#include <termios.h>
#include <sys/ioctl.h>

int tcsetattr(int fildes, int optional_actions, const struct termios *termios_p)
{
	//TODO: add bounds checking
        return ioctl(fildes, TCSETS + optional_actions, termios_p);
}

