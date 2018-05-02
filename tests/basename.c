#include <libgen.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	char *str;
	if (argc < 2) { 
		fprintf(stderr, "%s needs an argument\n", argv[0]);
		return 1;
	}
	str = basename(argv[1]);
	printf("%s\n", str);
	return 0;
}
