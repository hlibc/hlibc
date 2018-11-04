#include "../internal/internal.h"
#include <limits.h>
#include <string.h>
#include <stdlib.h>

typedef int (*__scan)(FILE *o, const char *s);

int __fgetc(FILE *o, const char *s)
{
	(void)s;
	return fgetc(o);
}

int __sscan(FILE *o, const char *s)
{
	(void)o;
	static size_t i = 0;
	return s[i++];
}

static int tk(int c)
{
	if (c == ' ')
		return 0;
	if (c == '\t')
		return 0;
	return 1;
}

int __fscanf_inter(const char *str, FILE *restrict o, const char *restrict fmt, va_list ap)
{
	char *p = NULL;
	size_t i = 0;
	char *sval = NULL;
	char s[1000] = { 0 };
	size_t j = 0;
	int c = 0;
	int *ints = NULL;
	__scan f;

	if (!(str))
		f = __fgetc;
	else
		f = __sscan;
	
	for (p = (char *)fmt; *p; p++) {
		if (*p != '%') {
			/* FIXME */
			f(o, str);
			continue;
		}
		++p;
		switch (*p) {
                case 's':
			sval = va_arg(ap, char *);
			for (c = 0, j = 0;tk(c = f(o, str));) {
				if (c != '\n')
					sval[j++] = c;
			}
			i+=j;
			break;
		case 'd': 
			ints = va_arg(ap, int *);
			for (s[0] = 0, c = 0, j = 0;tk(c = f(o, str));++j) {
				s[j] = c;
			}
			s[j] = 0;
			*ints = strtol(s, NULL, 10);
			i+=j;
			break;
		default:
			goto eof;
		}
	}
	return i;
	eof:
	return EOF;
}

