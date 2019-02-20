/*
	Copyright 2019, zhiayang

	routines for mkstemp, mkstemps, mkostemp, mkostemps
*/

#define _GNU_SOURCE

#include <time.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/stat.h>

#include "../internal/internal.h"

static const char *__char_pool = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
static const int   __char_pool_count = 62;

char *__fill_string_randomly(char *s, int cnt)
{
	for (int i = 0; i < cnt; i++)
		s[i] = __char_pool[rand() % __char_pool_count];

	return s + cnt;
}


#define NUM_TRIES 128
#define REQUIRED_X_COUNT 6

static char *__verify_template_xs(char *templ, int suffix_len)
{
	size_t templ_len = strlen(templ);

	// sanity check the lengths and stuff.
	if (suffix_len < 0 || templ_len < REQUIRED_X_COUNT
		|| templ_len - REQUIRED_X_COUNT < (size_t) suffix_len)
	{
		return NULL;
	}

	// we know that templ_len is at least 6 + suffix_len.
	char *fill_start = templ + templ_len - (REQUIRED_X_COUNT + suffix_len);
	for (int i = 0; i < REQUIRED_X_COUNT; i++)
	{
		if (fill_start[i] != 'X')
		{
			return NULL;
		}
	}

	return fill_start;
}



int mkostemps(char *templ, int suffix_len, int extra_flags)
{
	char *fill_start = __verify_template_xs(templ, suffix_len);
	if (fill_start == NULL)
	{
		errno = EINVAL;
		return -1;
	}


	int fd = -1;
	int counter = NUM_TRIES;
	do {

		// ok, now we can fill the chars at fill_start with random chars.
		__fill_string_randomly(fill_start, REQUIRED_X_COUNT);

		// note: there is no requirement for mkstemp to call unlink().
		fd = open(templ, O_RDWR | O_CREAT | O_EXCL | extra_flags,
			S_IRUSR | S_IWUSR);

		if (fd != -1)
		{
			errno = 0;
			return fd;
		}

	} while (counter--);

	// reset templ back to 'XXXXXX' in case things didn't work out.
	for (int i = 0; i < REQUIRED_X_COUNT; i++)
		fill_start[i] = 'X';

	errno = EEXIST;
	return -1;
}

int mkostemp(char *templ, int flags)
{
	return mkostemps(templ, /* suffixlen: */ 0, flags);
}

int mkstemps(char *templ, int suffixlen)
{
	return mkostemps(templ, suffixlen, /* flags: */ 0);
}

int mkstemp(char *templ)
{
	return mkostemps(templ, /* suffixlen: */ 0, /* flags: */ 0);
}





char *mkdtemp(char *templ)
{
	char *fill_start = __verify_template_xs(templ, 0);
	if (fill_start == NULL)
	{
		errno = EINVAL;
		return NULL;
	}

	int counter = NUM_TRIES;
	do {
		// ok, now we can fill the chars at fill_start with random chars.
		__fill_string_randomly(fill_start, REQUIRED_X_COUNT);

		if(mkdir(templ, S_IRUSR | S_IWUSR | S_IXUSR) == 0)
		{
			errno = 0;
			return templ;
		}

	} while (counter--);

	// reset templ back to 'XXXXXX' in case things didn't work out.
	for (int i = 0; i < REQUIRED_X_COUNT; i++)
		fill_start[i] = 'X';

	errno = EEXIST;
	return NULL;
}








