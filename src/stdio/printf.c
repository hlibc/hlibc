#include "../internal/internal.h"

int printf(const char *fmt, ...)
{
	int ret = 0;
	va_list argptr;
	va_start(argptr, fmt);
	ret = __printf_inter(stdout, NULL, 0, 0, fmt, argptr);
	va_end(argptr);
	return ret;
}
