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
#include <dirent.h>

extern char **__environ;


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
	char *lp; /* currently not used */
	size_t len;
	pid_t pid;
	char ungotten[8];
	size_t ungot;
	char unmalloced[1];
} FILE;

struct DIR
{
        int fildes;
        size_t position;
        size_t eob;
        char buffer[2048];
};


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
int ungetc(int, FILE *);
int fclose(FILE *);
FILE *fopen(const char *, const char *);
int setvbuf(FILE *, char *, int, size_t);
pid_t waitpid(pid_t, int *, int);
int fprintf(FILE *, const char *, ...);
int getdents(unsigned int fd, struct dirent *dirp, unsigned int count);
int sprintf(char *str, const char *format, ...);
int fgetc(FILE *);


/* internal */
typedef size_t (*__f)(size_t, int, char *, FILE *);

int __fillbuf(FILE *);
int __flushbuf(int, FILE *);
int __printf_inter(FILE *, char *, size_t, __f, const char *, va_list);
int __puts_inter(const char *, FILE *, int);
FILE *__init_file(FILE*);
size_t __int2str(char *, intmax_t, int);
size_t __uint2str(char *, uintmax_t, int);
int __fscanf_inter(const char *, FILE *restrict, const char *restrict, va_list);

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

/* modulus substitute */
int32_t __mod(int32_t, int32_t);

/* internal conversion table */
int __isalnum[256];

/* internal __errno_table */
extern char *__errno_table[];
/* string to number */
char *__tol_inter(const char *, int, long long *);

/* a simple wrapper for mmap */
void *__mmap_inter(size_t);

long __internal_syscall(long, long, long, long, long, long, long);

/* internal fopen to handle the needs of popen */
FILE *__internal_fopen(const char *, const char *, int);


size_t __dprintf_buffer(size_t, int, char *, FILE *);
size_t __printf_buffer(size_t, int, char *, FILE *);
size_t __sprintf_buffer(size_t, int, char *, FILE *);
size_t __snprintf_buffer(size_t, int, char *, FILE *);

/* silly debugging */
void __debug(int);

/*
	replaces 'cnt' characters at 's' with a random(ish) character from [A-Za-z0-9].
	returns s+cnt. defined in stdlib/mkstemp.c
*/
char *__fill_string_randomly(char *s, int cnt);


#endif



