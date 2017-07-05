#include <gstdio.h> 

int ggetchar(void)
{
	return ggetc(gstdin);
}

