#include <unistd.h>
#include <termios.h>

int isatty(int fd)
{
	struct termios t;
	if (tcgetattr(fd, &t) == 0)
		return 1;
	else
		return 0;
}
