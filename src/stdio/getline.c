#include <stdio.h> 
#include <stdlib.h>

ssize_t getline(char **p, size_t *n, FILE *fp)
{
	return getdelim(p, n, '\n', fp);
}
