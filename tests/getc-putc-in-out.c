#include <stdio.h>

int main(void)
{
	int c = 0;

	while ((c = getc(stdin)) != EOF)
		putc(c, stdout);

	return 0;
}
