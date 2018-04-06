#include <stdio.h>
#include <errno.h>
#include <limits.h>
#include <stdint.h>
#include <stdlib.h>

int main(void)
{
	void *a;
	a = malloc(SIZE_MAX);
	perror("malloc error\n");
	return 0;
}
