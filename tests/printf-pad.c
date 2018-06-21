#include <stdio.h>

int main(void)
{
	char *s = "printf padded string";
	printf("%.5s\n", s);
	printf("%.*s\n", 5, s);
	printf("%10s\n", "hell");
	printf("%10d\n", 1234);
	return 0;
}
