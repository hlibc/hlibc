#include <ctype.h>
#include <stddef.h>
#include <string.h>

/* Copyright (c) 2017, Iain Hill */

int
strcasecmp (const char *s, const char *t)
{
	int s_bis = 0;
	int t_bis = 0;

	while (*s && *t) {
		s_bis = tolower (*s);
		t_bis = tolower (*t);

		if (s_bis == t_bis) {
			if (*s == '\0') {
				return 0;
			}
			s++;
			t++;
		}
		else {
			break;
		}
	}
	return s_bis - t_bis;
}
