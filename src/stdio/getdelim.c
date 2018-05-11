#include <stdio.h> 
#include <stdlib.h>

ssize_t getdelim(char **p, size_t *n, char delim, FILE *fp)
{
	size_t i = 0;
	size_t chunk = BUFSIZ;
	char *o = NULL;
	int c = 0;

	if (!*p){
		if (!(*p = malloc(chunk))){
			return -1;
		}
		*n = chunk;
	}

	for (o = *p, i = *n;c != delim;i--, o++){ 
		if (i == 0){
			*n += chunk;
			i = chunk;
			if (!(*p = realloc(*p, *n))){
				return -1;
			}
			o = *p;
		}

		if ((c = fgetc(fp)) == EOF || c == 0){
			if (o == *p)
				return -1;
			else
				break;
		}
		*o = c;
	}

	*o = '\0';
	
	return o - (*p);
}

