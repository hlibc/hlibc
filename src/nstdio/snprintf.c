#include <stdio.h> 

int snprintf(char *str, size_t lim, const char *fmt, ...)
{
	int ret = 0;
	va_list argptr;
	va_start(argptr, fmt);
	ret = _printf_inter(NULL, str, lim, 2, fmt, argptr);
	va_end(argptr);
	return ret;
} 

