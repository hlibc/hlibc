#include <libgen.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	char *str = basename(argv[1]);
	printf("%s\n", str);
	return 0;
}
