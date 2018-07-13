#include <stdio.h>

int main(void)
{
	char *s = "printf padded string";
	printf("=====================\n");
	printf("field width %%*5s\n");
	printf("%*shello\n", 5, s);
	printf("%-*shello\n", 25, s);
	return 0;
}
