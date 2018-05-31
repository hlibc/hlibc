#ifndef _STRINGS_H
#define _STRINGS_H

#ifdef __cplusplus
extern "C" {
#endif

int bcmp(const void *, const void *, size_t);

void bcopy(const void *, void *, size_t);

void bzero(void *, size_t);

char *index(const char *, int);

char *rindex(const char *, int);

#ifdef __cplusplus
}
#endif

#endif

