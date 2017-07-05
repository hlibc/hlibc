#include <gstdio.h> 

int gprintf(const char *fmt, ...)
{
	int ret = 0;
	va_list argptr;
	va_start(argptr, fmt);
	ret = _gprintf_inter(gstdout, NULL, 0, 0, fmt, argptr);
	va_end(argptr);
	return ret;
}
