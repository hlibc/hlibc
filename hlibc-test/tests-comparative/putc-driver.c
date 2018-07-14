#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

void simplecat(FILE *fp, FILE *out)
{ 
	int c = 0;
	while ((c = getc(fp)) != -1) 
		putc(c, out);
}

int main(int argc, char *argv[])
{
	FILE *fp;
	FILE *fp2;
	if (argc == 2)
	{
		if (!(fp = fopen(argv[1], "r")))
			return 1;
		simplecat(fp, stdout);
		fclose(fp);
	}
	else if (argc == 3)
	{
		if (!(fp = fopen(argv[1], "r")))
			return 1;
		if (!(fp2 = fopen(argv[2], "w")))
			return 1;
		simplecat(fp, fp2);
		fclose(fp);
		fclose(fp2);
	}
	else {
		simplecat(stdin, stdout);
	}
	return 0;
}

