#ifndef _INTERNAL_
#define _INERNAL_
#define NULL ((void*)0) 
#define EOF (-1) 
#undef SEEK_SET
#undef SEEK_CUR
#undef SEEK_END
#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2 
#define _IOFBF 0
#define _IOLBF 1
#define _IONBF 2 
#define BUFSIZ 1024
#define FILENAME_MAX 4095
#define FOPEN_MAX 1000
#define TMP_MAX 10000
#define L_tmpnam 20
#include <sys/types.h>
#include <stdarg.h>
#include <fcntl.h>
#include <unistd.h>
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
extern FILE *stdin;
extern FILE *stdout;
extern FILE *stderr;
int _printf_inter(FILE *, char *, size_t, int, const char *, va_list);
int _puts_inter(const char *, FILE *, int);
int putc(int, FILE *);
int fputc(int, FILE *);

#endif
