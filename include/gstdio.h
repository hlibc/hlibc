#include <fcntl.h>
#include <unistd.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

/* popen / pclose */
#include <sys/types.h>
#include <sys/wait.h>
#ifndef _GRAFMUSL_STDIO_
#define _GRAFMUSL_STDIO_



#ifndef NULL
#define NULL ((void *) 0)
#endif
#ifndef EOF
#define EOF	    -1
#endif
#ifndef SEEK_CUR
#define SEEK_CUR	0
#endif
#ifndef SEEK_END
#define SEEK_END	1
#endif
#ifndef SEEK_SET
#define SEEK_SET	2
#endif
#ifndef BUFSIZ
#define BUFSIZ		1024
#endif

#define FOPEN_MAX	20


#define _PRINTF_NAN -(0./0.)

typedef struct {
	int fd;
	char flags;
	char *buf;
	char *rp;
	char *lp;
	int len;
	ssize_t pid; 
} FILE;

extern FILE _IO_stream[FOPEN_MAX];

enum _flags {
	_READ  = 001,
	_WRITE = 002,
	_UNBUF = 004,
	_LNBUF = 030,
	_EOF   = 010,
	_ERR   = 020,
};
/* file handling */
FILE *gfopen(const char *, const char *);
int gfclose(FILE *);
int gfeof(FILE *);
int gferror(FILE *);
int gfileno(FILE *);
/* single char io */
char *gfgets(char *, int, FILE *);
int _fillbuf(FILE *);
int _flushbuf(int, FILE *);
int gfflush(FILE *);
int _populate(int, int, int, char *, FILE *);
int ggetchar(void);
int gputchar(int);
int ggetc(FILE *);
int gfgetc(FILE *);
int gputc(int, FILE *); 
int gfputc(int, FILE *); 
/* getline */
ssize_t ggetline (char **, size_t *, FILE *);
ssize_t ggetdelim(char **, size_t *, char, FILE *);
/* printf */
int _gprintf_inter(FILE *, char *, size_t, int, const char *, va_list);
int gprintf(const char *, ...);
int gsprintf(char *, const char *, ...);
int gsnprintf(char *, size_t, const char *, ...);
int gdprintf(int, const char *, ...);
int gfprintf(FILE *, const char *, ...);
int gvprintf(const char *, va_list);
int gvsprintf(char *, const char *, va_list);
int gvsnprintf(char *, size_t, const char *, va_list);
int gvdprintf(int, const char *, va_list); /* not implemented */
int gvfprintf(FILE *, const char *, va_list);
/* fwrite */
size_t gfread(void *, size_t, size_t, FILE *);
size_t gfwrite(const void *, size_t, size_t, FILE *);
/* number conversion */
size_t uint2str(char *, size_t, int);
size_t flt2str(char *, double);
size_t int2str(char *, long long, int);
size_t int2str_inter(char *, long long, int); 
size_t flt2str(char *, double); 
/* setbuf ( not implemented ) */
void gsetbuf(FILE *, char *);
void gsetbuffer(FILE *, char *, size_t);
void gsetlinebuf(FILE *);
int gsetvbuf(FILE *, char *, int, size_t);
/* popen */
FILE *gpopen(const char *, const char *);
int gpclose(FILE *);
/* puts */
int gfputs(const char *, FILE *);
int gputs(const char *);
int __puts_inter(const char *, FILE *, int);
/* fseek */
int gfseek(FILE *, long, int);
/* popen */
int pclose(FILE *);
FILE *popen(const char *, const char *);


#define stdin  (&_IO_stream[0])
#define stdout (&_IO_stream[1])
#define stderr (&_IO_stream[2])

#endif
