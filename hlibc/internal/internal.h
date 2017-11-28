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
//#define stdin  (&_IO_stream[0])
//#define stdout (&_IO_stream[1])
//#define stderr (&_IO_stream[2])
extern FILE *stdin;
extern FILE *stdout;
extern FILE *stderr;
#endif
