#include <stdio.h>

int main(void)
{
	char *s = NULL;
	printf("%s %d\n", s, 1);
	printf("%s %s %s %s %d\n", s, s, "actual string", s, 1);
	return 0;
}
