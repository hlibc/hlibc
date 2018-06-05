#include "../internal/internal.h"

int sprintf(char *str, const char *fmt, ...)
{
	int ret = 0;
	va_list argptr;
	va_start(argptr, fmt);
	ret = __printf_inter(NULL, str, 0, 1, fmt, argptr);
	va_end(argptr);
	return ret;
}
