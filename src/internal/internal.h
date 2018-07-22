#ifndef _INTERNAL_
#define _INTERNAL_

#define NULL ((void*)0)
#define EOF (-1)
#undef SEEK_SET
#undef SEEK_CUR
#undef SEEK_END
#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2
#define BUFSIZ 1024
#define FILENAME_MAX 4095
#define FOPEN_MAX 1000
#define TMP_MAX 10000
#include <sys/types.h>
#include <stdarg.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

typedef struct
{
	int fd;
	/* flags */
	int read;
	int write;
	int lnbuf;
	int unbuf;
	int eof;
	int err;
	/**/
	char *buf;
	char *rp;
	char *lp;
	size_t len;
	pid_t pid;
	char ungotten[8];
	size_t ungot;
} FILE;

extern FILE _IO_stream[FOPEN_MAX];
extern FILE *stdin;
extern FILE *stdout;
extern FILE *stderr;

/* interdependent functions */
int putc(int, FILE *);
int fputc(int, FILE *);
int fflush(FILE *);
int ferror(FILE *stream);
int getc(FILE *);
int fclose(FILE *);
FILE *fopen(const char *, const char *);
int setvbuf(FILE *, char *, int, size_t);
pid_t waitpid(pid_t, int *, int);

/* internal */
int __fillbuf(FILE *);
int __flushbuf(int, FILE *);
int __printf_inter(FILE *, char *, size_t, int, const char *, va_list);
int __puts_inter(const char *, FILE *, int);
FILE *__init_file(FILE*);

/* number to string */ 
int fmt_fp(char *, long double, int, int, int, int);
#define MAX(a,b) ((a)>(b) ? (a) : (b))
#define MIN(a,b) ((a)<(b) ? (a) : (b))
#define CONCAT2(x,y) x ## y
#define CONCAT(x,y) CONCAT2(x,y)
#define ALT_FORM   (1U<<'#'-' ')
#define ZERO_PAD   (1U<<'0'-' ')
#define LEFT_ADJ   (1U<<'-'-' ')
#define PAD_POS    (1U<<' '-' ')
#define MARK_POS   (1U<<'+'-' ')
#define GROUPED    (1U<<'\''-' ')
#define FLAGMASK (ALT_FORM|ZERO_PAD|LEFT_ADJ|PAD_POS|MARK_POS|GROUPED)

/* safe arithmetic API */
int __safe_sub(intmax_t, intmax_t, intmax_t *);
int __safe_add(intmax_t, intmax_t, intmax_t *);
int __safe_div(intmax_t, intmax_t, intmax_t *);
int __safe_mul(intmax_t, intmax_t, intmax_t *);
int __safe_usub(uintmax_t, uintmax_t, uintmax_t *);
int __safe_uadd(uintmax_t, uintmax_t, uintmax_t *, uintmax_t);
int __safe_udiv(uintmax_t, uintmax_t, uintmax_t *);
int __safe_umul(uintmax_t, uintmax_t, uintmax_t *, uintmax_t);
int __safe_usub_sz(size_t, size_t, size_t *);     
int __safe_uadd_sz(size_t, size_t, size_t *, size_t);
int __safe_udiv_sz(size_t, size_t, size_t *);
int __safe_umul_sz(size_t, size_t, size_t *, size_t);
/* internal conversion table */
int __isalnum[256];

/* internal __errno_table */
extern char *__errno_table[];
/* string to number */
char *__tol_inter(const char *, int, long long *);
#define MAGLIM 512

extern uintptr_t reftable[MAGLIM];
extern int used[MAGLIM];
void initmag(void);
int fprintf(FILE *, const char *, ...);
#endif
