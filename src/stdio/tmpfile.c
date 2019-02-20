/*

	Copyright 2019 CM Graff
	Copyright 2019 zhiayang

	Thanks to ryuo and alphamule for providing feedback during
	the design stage of the temp file functions

	todo:
		*) add the L_tmpnam variable
*/

#include <time.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

#include <stdio.h>

/* 128 passes should be sufficient to reject */
#define MAX_TRIES 128

/*
	this is a bad hack!! internal.h and stdio.h are mutually exclusive due
	to how FILE is declared and defined ):

	so we don't include internal.h and we fwd-declare these guys.
	we want stdio instead for the L_tmpnam and P_tmpdir constants,
	so we don't have them in two places.
*/

char *__fill_string_randomly(char *s, int cnt);
FILE *__internal_fopen(const char *, const char *, int);


static char *__generate_tmp_filename(char *buf)
{
	static char storage[4096];

	char *output = (buf ? buf : storage);

	char *name = strcpy(output, "/tmp/") + 5;

	srand(time(NULL));

	/* NULL terminate the string. __fill_blabla returns one-past-the-end */
	__fill_string_randomly(name, L_tmpnam - strlen(P_tmpdir))[0] = 0;

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





