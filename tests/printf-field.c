#include <stdio.h>

int main(void)
{
	char *s = "printf padded string";

	printf("=====================\n");

	printf("field width %%.5s\n");
	printf("%.5s\n", s);
	printf("=====================\n");

	printf("field width %%.*s\n");
	printf("%.*s\n", 5, s);
	printf("=====================\n");
	return 0;
}
