/*
	Copyright 2019 CM Graff
	Thanks to ryuo and alphamule for providing feedback during
	the design stage of this code.
*/

#include <stdlib.h>
#include <time.h>
#include "../internal/internal.h"

static char *__hubris = "ABCDEFghijkLMNOpqrSTUVwyxz";
                      
static size_t __int2_hubris(char *s, uintmax_t n, int base, size_t i)
{
        if (n / base) {
                i = __int2_hubris(s, n / base, base, i);
        }
        s[i] = __hubris[(n % base)];
        return ++i;
}

char *tmpnam(char *s)
{
	static char storage[4096];
	char *name = storage;
	srand(time(NULL));
	int num = rand() % 100000 + time(NULL);
	/* 128 passes should be sufficient to reject */
	char counter = 128;
	char numstore[26];
	char *p = numstore;

	if (s)
		name = s;

	do { 
		p[__int2_hubris(p, num, 10, 0)] = 0;
		sprintf(name, "/tmp/%s", p);
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
	char buf[1024];
	do {
		/* redundantly cycle within tmpnam */
		name = tmpnam(buf); 
		/* __internal_fopen handles O_CREAT and O_EXCL */
		if ((fp = __internal_fopen(name, "w+", 2)))
			break;
	} while (counter--);
	return fp;
}

