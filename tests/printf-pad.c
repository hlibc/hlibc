#include <stdio.h>

int main(void)
{
	char *s = "printf padded string";
	printf("%.5s\n", s);
	printf("%.*s\n", 5, s);
	printf("%10s\n", "hell");
	printf("%10d\n", 1234);

	printf("%.3f\n", 3.33333);
	printf("%.10f\n", 3.33333);
	return 0;
}
