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
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

typedef struct
{
	int fd;
	char flags;
	char *buf;
	char *rp;
	char *lp;
	size_t len;
	pid_t pid;
} FILE;

extern FILE _IO_stream[FOPEN_MAX];

enum _flags
{
	_READ = 001,
	_WRITE = 002,
	_UNBUF = 004,
	_LNBUF = 030,
	_EOF = 010,
	_ERR = 020,
};

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
int _fillbuf(FILE *);
int _flushbuf(int, FILE *);
int _printf_inter(FILE *, char *, size_t, int, const char *, va_list);
int __puts_inter(const char *, FILE *, int);

/* number to string */
size_t __uint2str(char *, size_t, int);
size_t __uint2str_inter(char *, size_t, int, size_t);
size_t __int2str(char *, long long, int);
size_t __int2str_inter(char *, long long, int, size_t);
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

/* safe arithmetic */
size_t _safe_multiply(size_t, size_t, size_t);
size_t _safe_division(size_t, size_t);
size_t _safe_addition(size_t, size_t, size_t);
size_t _safe_upow(size_t, size_t);
/* internal __errno_table */
extern char *__errno_table[];
/* string to number */
char *_tol_driver(const char *, int, long long *);
#endif
