#include <fcntl.h>
#include <sys/syscall.h>
#include <stdarg.h>
/*
	TODO: add large file support
*/

int fcntl(int fildes, int cmd, ...)
{
	long j;
	va_list i;
	va_start(i, cmd);
	j = va_arg(i, long);
	va_end(i);
	return syscall(SYS_fcntl, fildes, cmd, j);
}
