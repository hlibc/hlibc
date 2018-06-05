#include "../internal/internal.h"

int dprintf(int fd, const char *fmt, ...)
{
	int ret = 0;
	va_list argptr;
	va_start(argptr, fmt);
	ret = __printf_inter(stdout + fd, NULL, 0, 3, fmt, argptr);
	va_end(argptr);
	return ret;
}
