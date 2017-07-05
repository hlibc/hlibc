#include <gstdio.h> 

int gvprintf(const char *fmt, va_list argptr)
{
	int ret = 0;
	ret = _gprintf_inter(gstdout, NULL, 0, 0, fmt, argptr);
	va_end(argptr);
	return ret;
}
