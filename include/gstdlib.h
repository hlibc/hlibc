#include <unistd.h>
#define NALLOC 10000

/* outside libs needed to implement system */
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

/* numbers */
int gatoi(const char *);
double gatof(const char *);
/* malloc */
void gfree(void *);
void *gmalloc(size_t);
void *grealloc(void *, size_t);
void *gcalloc(size_t, size_t);
/* system */
int gsystem(const char *);
/* rand */
int grand(void);
int gsrand(unsigned int);



