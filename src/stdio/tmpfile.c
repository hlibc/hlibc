/*

	Copyright 2019 CM Graff

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

static char *__debris = "ABCDEFghijkLMNOpqrSTUVwyxz";

static size_t __int2_debris(char *s, uintmax_t n, int base, size_t i)
{
        if (n / base) {
                i = __int2_debris(s, n / base, base, i);
        }
        s[i] = __debris[(n % base)];
        return ++i;
}

char* __generate_tmp_filename(char* buf, int tries)
{
	static char storage[4096];

	char* name = (buf ? buf : storage);

	srand(time(NULL));
	int num = rand() % 100000 + time(NULL);

	int counter = tries;
	char numstore[26];
	char *p = numstore;

	do {
		p[__int2_debris(p, num, 10, 0)] = 0;
		strcpy(name, "/tmp/");
		strcat(name, p);
		if (access(name, X_OK) == 0)
			break;
		++num;

	} while (counter--);

	if (counter == 0)
		return NULL;

	return name;
}

char *tmpnam(char *s)
{
	return __generate_tmp_filename(s, MAX_TRIES);
}

FILE *tmpfile(void)
{
	char* name = __generate_tmp_filename(NULL, MAX_TRIES);
	if(!name)
	{
		errno = EEXIST;
		return NULL;
	}

	return __internal_fopen(name, "w+", 2);
}





