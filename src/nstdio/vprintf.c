#include <stdio.h> 

int vprintf(const char *fmt, va_list argptr)
{
	int ret = 0;
	ret = _printf_inter(stdout, NULL, 0, 0, fmt, argptr);
	va_end(argptr);
	return ret;
}
