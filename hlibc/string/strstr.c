#include <string.h>

char *strstr(const char *haystack, const char *needle)
{
	const char *h = haystack;
	const char *n = needle;

	while (*haystack) {
		h = haystack;
		n = needle;

		while (*h != '\0' && *n != '\0' && *h == *n) {
			++h;
			++n;
		}
		if (!*n) {
			return (char *)haystack;
		}

		haystack++;
	}

	return NULL;
}
