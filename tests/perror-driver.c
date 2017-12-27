#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
int main(void)
{
	malloc((size_t)-1);
	perror("malloc() error?");
	return 0;
}
