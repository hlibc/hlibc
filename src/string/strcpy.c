#include <string.h>



char *strcpy(char *dest, const char *src)
{ 
	const unsigned char *s = src;
	unsigned char *d = dest;
	while ((*d++ = *s++));
	return dest;

}
