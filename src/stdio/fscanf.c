#include "../internal/internal.h"

int fscanf(FILE *stream, const char *fmt, ...)
{
	int ret = 0;
        va_list argptr;
        va_start(argptr, fmt);
        ret = __fscanf_inter(NULL, stream, fmt, argptr);
        va_end(argptr);
        return ret;
}

