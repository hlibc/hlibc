#include "../internal/internal.h"

int vprintf(const char *fmt, va_list argptr)
{
	int ret = 0;
	ret = __printf_inter(stdout, NULL, 0, __printf_buffer, fmt, argptr);
	va_end(argptr);
	return ret;
}
