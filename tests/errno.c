#include <stdio.h>
#include <errno.h>
#include <limits.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
	void *a;
	errno = ENOMEM;
	char *s;
	s = strerror(errno);
	printf("%s\n", s);
	
	return 0;
}
