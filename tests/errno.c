#include <stdio.h>
#include <errno.h>
#include <limits.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
	char *s;
	s = strerror(ENOMEM);
	printf("%s\n", s);
	return 0;
}
