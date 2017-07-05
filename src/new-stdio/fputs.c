#include <gstdio.h> 

int gfputs(const char *s, GFILE *fp)
{
	return __puts_inter(s, fp, 0);
}
