#include <stdio.h> 
int putchar(int x)
{
	return putc(x, stdout);
}
