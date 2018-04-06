#include <stdio.h>
#include <errno.h>
#include <limits.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


int main(void)
{
	void *a;
	//a = malloc(SIZE_MAX / 2);
	a = malloc(SIZE_MAX);
	//char *b = strerror(errno);
	//write(2, b, strlen(b));
	perror("malloc error\n");
	return 0;
}
