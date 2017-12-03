#include <stdio.h>
#include <limits.h>
#include <stdint.h>
#include <stdarg.h>
#include <float.h>


int main(int argc, char *argv[])
{
	int c = 0;

	while ((c = getc(stdin)) != EOF)
		putc(c, stdout);

	return 0;
}
