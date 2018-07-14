#include <stdio.h>

int main(void)
{
	int ch;

	ungetc('+', stdin);

	while ((ch = getchar()) != '1')
	{
		putchar(ch);
		fflush(stdout);
	}

	return 0;
}
