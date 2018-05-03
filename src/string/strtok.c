#include <stddef.h>

#include <string.h>

static char *saveptr;

char *strtok(char *s, const char *delim)
{
	return strtok_r(s, delim, &saveptr);
}

char *strtok_r(char *s, const char *delim, char **saveptr)
{
	char *start = NULL;

	// Check if successive call
	if (s == NULL) {
		if (*saveptr == NULL) {
			return NULL;
		}

		s = *saveptr;
	}

	// Advance to non-delimiter
	for (; *s != '\0'; ++s) {
		// Iterate through delimiter list; advance if delimiter found
		for (const char *d = delim; *d != '\0'; ++d) {
			if (*s == *d) {
				goto advance;
			}
		}

		start = s;
		break;
	advance:
		continue;
	}

	// Advance to delimiter
	for (; *s != '\0'; ++s) {
		// Iterate through delimiter list
		for (const char *d = delim; *d != '\0'; ++d) {
			if (*s == *d) {
				*saveptr = s + 1;

				*s = '\0';
				return start;
			}
		}
	}

	// If no delimiter was found, then no successive calls are necessary.
	*saveptr = NULL;

	// The first loop will read until a delimiter or '\0'
	// If it reaches '\0', start remains to be NULL.
	// And the second loop is not executed, as its condition fails.
	return start;
}
