#ifndef _STDIO_H
#define _STDIO_H
#include <fcntl.h>
#include <unistd.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h> 
/* popen / pclose */
#include <sys/types.h>
#include <sys/wait.h> 
#define __NEED_ssize_t
#define __NEED_off_t 
#include <bits/alltypes.h> 
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

typedef union {
	char __opaque[16];
	double __align;
} fpos_t; 


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


int putc(int, FILE *);
int fputc(int, FILE *);
/* getline */
ssize_t getline (char **, size_t *, FILE *);
ssize_t getdelim(char **, size_t *, char, FILE *);
/* printf */
int _printf_inter(FILE *, char *, size_t, int, const char *, va_list);
int printf(const char *, ...);
int sprintf(char *, const char *, ...);
int snprintf(char *, size_t, const char *, ...);
int dprintf(int, const char *, ...);
int fprintf(FILE *, const char *, ...);
int vprintf(const char *, va_list);
int vsprintf(char *, const char *, va_list);
int vsnprintf(char *, size_t, const char *, va_list);
int vdprintf(int, const char *, va_list); /* not implemented */
int vfprintf(FILE *, const char *, va_list);
/* fwrite */
size_t fread(void *, size_t, size_t, FILE *);
size_t fwrite(const void *, size_t, size_t, FILE *);
/* number conversion */
size_t uint2str(char *, size_t, int);
size_t flt2str(char *, double);
size_t int2str(char *, long long, int);
size_t int2str_inter(char *, long long, int);
size_t flt2str(char *, double);
/* setbuf ( not implemented ) */
void setbuf(FILE *, char *);
void setbuffer(FILE *, char *, size_t);
void setlinebuf(FILE *);
int setvbuf(FILE *, char *, int, size_t);
/* popen */
FILE *popen(const char *, const char *);
int pclose(FILE *);
/* puts */
int fputs(const char *, FILE *);
int puts(const char *);
int _puts_inter(const char *, FILE *, int); 

char *fgets(char *, int, FILE *);

FILE *fopen(const char *path, const char *mode);
int fgetc(FILE *stream);

char *fgets(char *s, int size, FILE *stream);

int getc(FILE *stream);

int getchar(void);

int fclose(FILE *stream);

#define stdin  (&_IO_stream[0])
#define stdout (&_IO_stream[1])
#define stderr (&_IO_stream[2])

#endif
