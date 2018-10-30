#include "../internal/internal.h"

int vfprintf(FILE *stream, const char *fmt, va_list argptr)
{
	int ret = 0;
	ret = __printf_inter(stream, NULL, 0, __printf_buffer, fmt, argptr);
	va_end(argptr);
	return ret;
}
