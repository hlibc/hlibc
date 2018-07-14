#include <stdio.h>

int main(void)
{
	int ch;
	while ((ch = getchar()) != '1')
		putchar(ch);
	 
	ungetc('+', stdin);

	ch = getchar();
	putchar(ch);
	printf("\n");
	return 0;
}
