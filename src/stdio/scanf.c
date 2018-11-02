#include "../internal/internal.h"
#include <limits.h>



int fscanf(FILE *restrict stream, const char *restrict format, ...)
{
	char *p = NULL;
	size_t i = 0;
	size_t bound = INT_MAX;
	
	for (p = (char *)format; *p && i < bound; p++) {
		if (*p != '%') {
			   fputc(*p, stream);
			   continue;
		}
		//++p;
	}
	return 0;
}
