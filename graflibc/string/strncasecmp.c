#include <stddef.h>
#include <ctype.h>
#include <string.h>

/* Copyright (c) 2017, Iain Hill */

int strncasecmp(const char *s, const char *t, size_t n)
{
	int s_bis, t_bis;
	size_t i = 0;

        while (*s && *t && i++ < n)
	{
		s_bis = tolower(*s);
		t_bis = tolower(*t);

		if (s_bis == t_bis) {
			if (*s == '\0')
				return 0;
			s++;
			t++;
		}
		else
			break;
	}
        return s_bis - t_bis;
}

