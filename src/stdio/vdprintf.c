#include "../internal/internal.h"

int vdprintf(int fd, const char *fmt, va_list argptr)
{
	int ret = 0;
	ret = __printf_inter(stdout + fd, NULL, 0, 3, fmt, argptr);
	va_end(argptr);
	return ret;
}
