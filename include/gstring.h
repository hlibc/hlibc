#include <stddef.h>

size_t gstrlen(const char *); 
size_t gstrnlen(const char *, size_t); 
int gstrcmp(const char *, const char *);
int gstrncmp(const char *, const char *, size_t);
char *gstrchr(const char *, int); 
char *gstrcpy(char *, const char *);
char *gstrncpy(char *, const char *, size_t);
char *gstrtok(char *, const char *);
void* gmemset(void *, int, size_t);
/* memcpy*/
void* gmemcpy(void*, const void*, size_t);
void *gmemccpy(void *, const void *, int, size_t);
/* strspn, strcspn */
size_t gstrspn(const char *, const char *);
size_t gstrcspn(const char *, const char *);
/* memmove */
void *gmemmove(void *, const void *, size_t);
char *gstrdup(const char *);
char *gstrndup(const char *, size_t);
void *gmemchr(const void *, int, size_t);
char *gstrchrnul(const char *, int);

/* strerror */
char *gstrerror(int);

extern char **_messages;

