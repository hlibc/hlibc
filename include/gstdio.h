#include <fcntl.h>
#include <unistd.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

/* popen / pclose */
#include <sys/types.h>
#include <sys/wait.h>


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
#ifndef FOPEN_MAX
#define FOPEN_MAX	20
#endif

#define _PRINTF_NAN -(0./0.)

typedef struct {
	int fd;
	char flags;
	char *buf;
	char *rp;
	char *lp;
	int len;
	ssize_t pid; /* for popen */
} GFILE;

extern GFILE _IO_stream[FOPEN_MAX];

enum _flags {
	_READ  = 001,
	_WRITE = 002,
	_UNBUF = 004,
	_LNBUF = 030,
	_EOF   = 010,
	_ERR   = 020,
};
/* file handling */
GFILE *gfopen(const char *, const char *);
int gfclose(GFILE *);
int gfeof(GFILE *);
int gferror(GFILE *);
int gfileno(GFILE *);
/* single char io */
char *gfgets(char *, int, GFILE *);
int _fillbuf(GFILE *);
int _flushbuf(int, GFILE *);
int gfflush(GFILE *);
int _populate(int, int, int, char *, GFILE *);
int ggetchar(void);
int gputchar(int);
int ggetc(GFILE *);
int gfgetc(GFILE *);
int gputc(int, GFILE *); 
int gfputc(int, GFILE *); 
/* getline */
ssize_t ggetline (char **, size_t *, GFILE *);
ssize_t ggetdelim(char **, size_t *, char, GFILE *);
/* printf */
int _gprintf_inter(GFILE *, char *, size_t, int, const char *, va_list);
int gprintf(const char *, ...);
int gsprintf(char *, const char *, ...);
int gsnprintf(char *, size_t, const char *, ...);
int gdprintf(int, const char *, ...);
int gfprintf(GFILE *, const char *, ...);
int gvprintf(const char *, va_list);
int gvsprintf(char *, const char *, va_list);
int gvsnprintf(char *, size_t, const char *, va_list);
int gvdprintf(int, const char *, va_list); /* not implemented */
int gvfprintf(GFILE *, const char *, va_list);
/* fwrite */
size_t gfread(void *, size_t, size_t, GFILE *);
size_t gfwrite(const void *, size_t, size_t, GFILE *);
/* number conversion */
size_t uint2str(char *, size_t, int);
size_t flt2str(char *, double);
size_t int2str(char *, long long, int);
size_t int2str_inter(char *, long long, int); 
size_t flt2str(char *, double); 
/* setbuf ( not implemented ) */
void gsetbuf(GFILE *, char *);
void gsetbuffer(GFILE *, char *, size_t);
void gsetlinebuf(GFILE *);
int gsetvbuf(GFILE *, char *, int, size_t);
/* popen */
GFILE *gpopen(const char *, const char *);
int gpclose(GFILE *);
/* puts */
int gfputs(const char *, GFILE *);
int gputs(const char *);
int __puts_inter(const char *, GFILE *, int);
/* fseek */
int gfseek(GFILE *, long, int);

#define gstdin  (&_IO_stream[0])
#define gstdout (&_IO_stream[1])
#define gstderr (&_IO_stream[2])
