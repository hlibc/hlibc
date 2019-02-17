/*
	This temporary file implementation is under construction

	tmpnam and tmpfile go in stdio.h 
	mkstemp and mkdtemp go in stdlib.h
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char *tmpnam(char *s)
{
	static char buf[4096];
	srand(time(NULL));
	int num = rand() % 1000;
	if (s)
		sprintf(buf, "%s/%d-temporary.txt", s, num);
	else
		sprintf(buf, "%d-temporary.txt", num);
	return buf;
}

FILE *tmpfile(void)
{
	FILE *fp = NULL;
	char counter = 128;
	char *name = NULL;
	do {
		name = tmpnam("/tmp/");
		if (access(name, X_OK) == 0 )
		{
			if (!(fp = fopen(name, "w")))
				return NULL;
			break;
		}
	}
	while (counter--);
	return fp;
}

int mkstemp(char *template)
{
	;
}

char *mkdtemp(char *template)
{
	;
}

