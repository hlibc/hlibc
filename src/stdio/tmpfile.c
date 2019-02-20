/*

	Copyright 2019 CM Graff
	Copyright 2019 zhiayang

	Thanks to ryuo and alphamule for providing feedback during
	the design stage of the temp file functions

	todo:
		*) add the L_tmpnam variable

		*) create better prng char strings

		*) prng against the array of debris
*/

#include <time.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include "../internal/internal.h"

/* 128 passes should be sufficient to reject */
#define MAX_TRIES 128

/* mkstemp does at most 6 chars, so we just follow that */
#define NUM_RAND_CHARS 6


static char *__generate_tmp_filename(char *buf)
{
	static char storage[4096];

	char *output = (buf ? buf : storage);

	char *name = strcpy(output, "/tmp/") + 5;

	srand(time(NULL));

	/* NULL terminate the string. __fill_blabla returns one-past-the-end */
	__fill_string_randomly(name, NUM_RAND_CHARS)[0] = 0;

	return output;
}

char *tmpnam(char *s)
{
	char *name = NULL;
	int counter = MAX_TRIES;

	do {
		name = __generate_tmp_filename(NULL);
		if (access(name, X_OK) == 0)
			break;
	} while (counter--);

	if (counter == 0)
		return NULL;

	return name;
}

FILE *tmpfile(void)
{
	FILE *fd = NULL;
	char *name = NULL;
	int counter = MAX_TRIES;

	do {
		name = __generate_tmp_filename(NULL);
		if ((fd = __internal_fopen(name, "w+", 2)))
			break;

	} while (counter--);

	if (fd)
	{
		/*
			unlink the file, which removes it from the disk. since we already fopen-ed it, the file
			will continue to exist until the last user gets closes it. since nobody else know about
			the file (in theory), this process will be the last user, and the file will be freed when
			the process exits.
		*/

		unlink(name);
	}

	return fd;
}





