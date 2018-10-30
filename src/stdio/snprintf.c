#include "../internal/internal.h"

int snprintf(char *str, size_t lim, const char *fmt, ...)
{
	int ret = 0;
	va_list argptr;
	va_start(argptr, fmt);
	ret = __printf_inter(NULL, str, lim, __snprintf_buffer, fmt, argptr);
	va_end(argptr);
	return ret;
}
