#include "../internal/internal.h"

int sscanf(const char *str, const char *fmt, ...);
{
	int ret = 0;
        va_list argptr;
        va_start(argptr, fmt);
        ret = __fscanf_inter(str, NULL, fmt, argptr);
        va_end(argptr);
        return ret;
}

