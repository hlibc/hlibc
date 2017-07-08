#include <stdio.h> 

int fputs(const char *s, FILE *fp)
{
	return __puts_inter(s, fp, 0);
}
