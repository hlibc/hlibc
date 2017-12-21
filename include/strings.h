#ifndef	_STRINGS_H
#define	_STRINGS_H

#define __NEED_size_t
#define __NEED_locale_t
#include <bits/alltypes.h>
void bzero (void *, size_t);
char *index (const char *, int);
char *rindex (const char *, int);
int strcasecmp (const char *, const char *);
int strncasecmp (const char *, const char *, size_t);
size_t strlen(const char *s);
char *strrchr(const char *s, int c);
char *strchr(const char *s, int c);
int bcmp(const void *s1, const void *s2, size_t n);
#endif

