#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>


void simplecat(FILE *fp)
{ 
	int c = 0;
	
	while ((c = getc(fp)) != -1 ) 
		putc(c, stdout); 
}

int main(int argc, char *argv[])
{
	if ( argc > 1 )
	{
		FILE *fp = fopen(argv[1], "r");
		simplecat(fp);
		fclose(fp);
	}else {
		simplecat(stdin);
	}
	return 0;
}
