#include <string.h>

#ifdef _NO_BACK_ITERATION
char *rindex(const char *s, int c)
{
  char * target = NULL;
  do {
    while (*s != c && *s != '\0') {
      ++s;
    }

    if (*s == c) {
      target = (char*)s;
      ++s;
    }
  } while (*s != '\0');
  return target;
}

#else

char *rindex(const char *s, int c)
{
	int i = 0;
	while (s[i] != '\0') {
		++i;
	}
	++i;
	while (s[i] != c && i >= 0) {
		--i;
	}
	if (i == 0 && s[i] != c) {
		return NULL;
	}
	return (char *)s + i;
}
#endif
