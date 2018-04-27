#include "../internal/internal.h"

int vdprintf(int fd, const char *fmt, va_list argptr)
{
	int ret = 0;
	ret = _printf_inter(NULL, NULL, 0, 10 + fd, fmt, argptr);
	va_end(argptr);
	return ret;
}
