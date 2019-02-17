/*
	This temporary file implementation is under construction

	tmpnam and tmpfile go in stdio.h 
	mkstemp and mkdtemp go in stdlib.h
*/

#include <stdlib.h>
#include <time.h>
#include "../internal/internal.h"

char *tmpnam(char *s)
{
	static char name[4096];
	srand(time(NULL));
	int num = rand() % 1000;
	char counter = 128;
	do {
		if (s)
			sprintf(name, "%s/%d-temporary.txt", s, num);
		else
			sprintf(name, "%d-temporary.txt", num);
		if (access(name, X_OK) == 0)
			break;
		++num;
	} while (counter--);
	if (counter == 0)
		return NULL;
	return name;
}

FILE *tmpfile(void)
{
	FILE *fp = NULL;
	char counter = 128;
	char *name = NULL;
	do {
		/* reundantly cycle within tmpnam */
		name = tmpnam("/tmp/"); 
		/* __internal_fopen handles O_CREAT and O_EXCL */
		if (!(fp = __internal_fopen(name, "w", 2)))
			;
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

