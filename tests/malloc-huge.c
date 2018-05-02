#include <stdio.h>
#include <errno.h>
#include <limits.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(void)
{
	malloc(SIZE_MAX);
	if (errno == ENOMEM)
		printf("malloc-huge driver correctly set errno\n");

	return 0;
}
