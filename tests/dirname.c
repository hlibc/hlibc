#include <libgen.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	char *str = dirname(argv[1]);
	printf("%s\n", str);
	return 0;
}
