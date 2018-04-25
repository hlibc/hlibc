#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

void simplecat(FILE *fp)
{ 
	int c = 0;
	
	while ((c = getc(fp)) != EOF) 
		putc(c, stdout); 
}

int main(int argc, char *argv[])
{
	FILE *fp;
	if (argc > 1)
	{
		if (!(fp = fopen(argv[1], "r")))
			return 1;
		simplecat(fp);
		fclose(fp);
	}else {
		simplecat(stdin);
	}
	return 0;
}

