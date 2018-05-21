#include <stdio.h>

int main(int argc, char *argv[])
{
	char buffer[BUFSIZ] = { 0 };
	size_t frret = 0;
	size_t fwret = 0;
	size_t ret = 0;
	int c = 0;
	FILE *fp = stdin;
	if ( argc > 1 ) {
		fp = fopen(argv[1], "r");
	}
	while ((ret = fread(buffer, 1, 10, fp)) > 0 )
	{
		frret += ret;
		fwret += fwrite(buffer, 1, 10, stdout);
	}
	if (fp != stdin)
		fclose(fp);
	printf("ret val of fread: %zu\n", frret);
	printf("ret val of fwrite: %zu\n", fwret);
	return 0;
}

