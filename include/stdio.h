#ifndef _STDIO_H
#define _STDIO_H
#include <fcntl.h>
#include <unistd.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h> 
/* for popen / pclose */
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
#define BUFSIZ 1024
#define FILENAME_MAX 4095
#define FOPEN_MAX 1000
#define TMP_MAX 10000

/* The opaque stdio declaration */
typedef struct FILE FILE;

/* putc/getc */
int getc(FILE *);
int putc(int, FILE *);
int fputc(int, FILE *);

/* getline */
ssize_t getline (char **, size_t *, FILE *);
ssize_t getdelim(char **, size_t *, char, FILE *);

/* printf */
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
char *fgets(char *, int, FILE *);
FILE *fopen(const char *, const char *);
int fgetc(FILE *m);
char *fgets(char *, int, FILE *);
int getchar(void);
int fclose(FILE *);
int fflush(FILE *);
int ferror(FILE *);

/* remove */
int remove(const char *);

/* perror */
void perror(const char *);

/* opaque objects */
FILE *stdin;
FILE *stdout;
FILE *stderr;
#endif
