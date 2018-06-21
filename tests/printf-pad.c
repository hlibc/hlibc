#include <stdio.h>

int main(void)
{

	char *s = "printf padded string";
	printf("%.5s\n", s);

	printf("%.*s\n", 5, s);

	printf("%3.3f \n", 2222.2);

}
