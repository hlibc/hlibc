#include <gstdio.h> 

int gvsprintf(char *str, const char *fmt, va_list argptr)
{
	int ret = 0;
	ret = _gprintf_inter(NULL, str, 0, 1, fmt, argptr);
	va_end(argptr);
	return ret;
}
