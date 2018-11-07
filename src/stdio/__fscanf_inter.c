#include "../internal/internal.h"
#include <limits.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef int (*__scan)(FILE *o, const char *s);

static int __fgetc(FILE *o, const char *s)
{
	(void)s;
	return fgetc(o);
}

static int __sscan(FILE *o, const char *s)
{
	(void)o;
	static size_t i = 0;
	return s[i++];
}

static int dectk(int c)
{
	switch(c) {
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			return 1;
	}
	//if (c == EOF)
	//	return 0;
	return 0;
}
static int tk(int c)
{
	if (isspace(c))
		return 0;
	if (c == EOF)
		return 0;
	return 1;
}

int __fscanf_inter(const char *str, FILE *restrict o, const char *restrict fmt, va_list ap)
{
	char *p = NULL;
	size_t i = 0;
	static char array[1024] = { 0 };
	size_t j = 0;
	int c = 0;
	int *ints = NULL;
	__scan f;
	char *ps = array;
	char *s = NULL;
	int lever = 0;
	int base = 10;

	if (!(str))
		f = __fgetc;
	else
		f = __sscan;

	for (p = (char *)fmt; *p; p++) {
		if (*p != '%') {
			;// FIXME
		}
		++p;
		switch (*p) {
		case 's':
			s = va_arg(ap, char *);
			for (lever = 0;isspace((c = f(o, str)));) {
				lever = 1;
			}
			if (lever == 1 && c != EOF) {
				ungetc(c, o);
				lever = 0;
			}
	
			for (s[0] = 0, c = 0, j = 0;tk(c = f(o, str));) { 
				s[j++] = c;
				s[j] = 0;
				i++;
				lever = 1;
			}

			if (lever == 1 && c != EOF) {
				ungetc(c, o);
				lever = 0;
			}
			if (c == EOF)
				goto eof;
			break;
		case 'd':
			base = 10;
			ints = va_arg(ap, int *);
			
			for (lever = 0;isspace((c = f(o, str)));) {
				lever = 1;
			}
			if (lever == 1 && c != EOF) {
				ungetc(c, o);
				lever = 0;
			}
			for (ps[0] = 0, c = 0, j = 0;dectk(c = f(o, str));) {
				ps[j++] = c;
				ps[j] = 0;
				i++;
				lever = 1;
			}
			*ints = strtoul(ps, NULL, base);
			
			if (dectk(c) == 0 || (lever == 1 && c != EOF)) {
				ungetc(c, o);
				lever = 0;
			}
			
			if (c == EOF)
				goto eof;

			
			break;
		}
	}
	return i;
	eof:
	return EOF;
}

