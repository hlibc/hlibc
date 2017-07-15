#include <stdio.h>

int main(int argc, char *argv[])
{
	char buffer[BUFSIZ] = { 0 };
	ssize_t ret = 0; 
	if ( argc > 1 ) 
	{
		FILE *filepointer = fopen(argv[1], "r"); 
		while ( (ret = fread(buffer, 1, 1000, filepointer)) > 0 )
			fwrite(buffer, 1, ret, stdout);
		fclose(filepointer);
	}
	return 0;
}

