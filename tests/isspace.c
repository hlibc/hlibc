#include <stdio.h>
#include <ctype.h>


int main(void)
{
	char *s = "\t\n\f\v\r ";

	while (isspace(*s++))
		printf("ok\n");
	return 0;
}
