#include "../internal/internal.h"

int vsprintf(char *str, const char *fmt, va_list argptr)
{
	int ret = 0;
	ret = __printf_inter(NULL, str, 0, __sprintf_buffer, fmt, argptr);
	va_end(argptr);
	return ret;
}
