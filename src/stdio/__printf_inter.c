#include "../internal/internal.h"
#include <stdarg.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>

static int __convtab[20] = { '0', '1', '2', '3', '4', '5', '6', '7',
			     '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };

typedef size_t (*__f)(size_t, int, char *, FILE *);

size_t __dprintf_buffer(size_t i, int x, char *s, FILE *o)
{
	(void)s;
	static char b[BUFSIZ];
	static size_t j = 0;
	if (x > -1) {
		b[j++] = x;
	}
	if (j == BUFSIZ || x == -1){
		write(o - stdout, b, j);
		j = 0;
	}
	return i + 1;
}

static size_t __printf_buffer(size_t i, int x, char *s, FILE *o)
{
	(void)s;
	putc(x, o); 
	return i + 1;
}

static size_t __sprintf_buffer(size_t i, int x, char *s, FILE *o)
{
	(void)o;
	s[i] = x;
	s[i + 1] = 0; /* this needs to be fixed */
	return i + 1;
}

static size_t __uint2str_inter(char *s, size_t n, int base, size_t i)
{
	if (n / base) {
		i = __uint2str_inter(s, n / base, base, i);
	}
	s[i] = __convtab[(n % base)];
	return ++i;
}

static size_t __int2str_inter(char *s, long long n, int base, size_t i)
{
	if (-n / base) {
		i = __int2str_inter(s, n / base, base, i);
	}
	s[i] = __convtab[+(-(n % base))];
	return ++i;
}

static size_t __int2str(char *s, long long n, int base)
{
	size_t i = 0;
	int toggle = 0;
	if (n >= 0) {
		n = -n;
	}
	else {
		s[0] = '-';
		toggle = 1;
	}
	return __int2str_inter(s + toggle, n, base, i) + toggle;
}

static size_t __uint2str(char *s, size_t n, int base)
{
	size_t i = 0;
	return __uint2str_inter(s, n, base, i);
}

void __padding(size_t have, size_t want, __f f, size_t a, int b, char *c , FILE *d)
{
	size_t i = 0;
	for (i=0;want > have +i;++i) {
		f(a, b, c, d);
	}
}

int __printf_inter(FILE *fp, char *str, size_t lim, int flag, const char *fmt, va_list ap)
{ 
	const char *p = NULL;
	size_t i = 0;
	/* this should probably be INT_MAX */
	size_t bound = (size_t)-1;
	int base = 10;

	/* Hold converted numerical strings */
	char converted[BUFSIZ] = { 0 };
	size_t convlen = 0;
	size_t j = 0;
	__f f;
	/* data types */
	int cval = 0;
	char *sval = NULL;
	size_t len = 0;
	size_t ii = 0;
	size_t zuval = 0;
	long long lval = 0;
	long double fval = 0;

	/* float precision */
	size_t precision = 6;

	/* field width */
	size_t off = INT_MAX;	/* upper bound for meaningful comparison */
	size_t z = 0;
	size_t padding = 0;
	int zeropad = 0;
	int altform = 0;
	int signage = 0;
	int leftadj = 0;
	int pls2spc = 0;

	if (flag == 2) {	/* flag 2 == snprintf */
		bound = lim - 1;
		f = __sprintf_buffer;
	}
	else if (flag == 1){	/* flag 1 == sprintf */
		f = __sprintf_buffer;
	}
	else if (flag == 0) {	/* flag 0 == printf, vprintf */
		f = __printf_buffer;
	}
	else if (flag == 3) {	/* flag 3 == dprintf */
		f = __dprintf_buffer;
	}

	for (p = fmt; *p && i < bound; p++) {
		if (*p != '%') {
			i = f(i, *p, str, fp);
			goto end;
		}
		++p;

		start:
		switch (*p) {
		case '.':
			if (isdigit(*++p))
				precision = off = strtol(p, &p, 10);
			goto start;
		case '*':
			++p;
			off = va_arg(ap, int);
			goto start;
		case '0':
			zeropad = 1;
			++p;
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			padding = strtol(p, &p, 10);
			goto start;
		case '#':
			++p;
			altform = 1;
			goto start;
		case '+':
			++p;
			signage = 1;
			goto start;
		case '-':
			++p;
			leftadj = 1;
			goto start;
		case ' ':
			++p;
			pls2spc = 1;
			goto start;
		case 'c':
			cval = va_arg(ap, int);
			goto character;
		case 's':
			sval = va_arg(ap, char *); 
			if (sval == NULL)
				sval = "(null)";
			goto string;
		case 'o':
			base = 8;
			lval = va_arg(ap, int);
			goto integer;
		case 'd':
			lval = va_arg(ap, int);
			goto integer;
		case 'x':
			base = 16;
			lval = va_arg(ap, int);
			goto integer;
		case 'f':
			fval = va_arg(ap, double);
			goto floating;
		case 'g':
			fval = va_arg(ap, double);
			goto floating;
		case 'L':
			switch (*++p) {
			case 'f':
				fval = va_arg(ap, long double);
				goto floating;
			}
			goto end;
		case 'l':
			switch (*++p) {
			case 'd':
				lval = va_arg(ap, long);
				goto integer;
			case 'l':
				switch (*++p) {
				case 'd':
					lval = va_arg(ap, long long);
					goto integer;
				}
				goto end;
			case 'f':
				fval = va_arg(ap, double);
				goto floating;
			default:
				goto end;
			}
			goto end;
		case 'z':
			switch (*++p) {
			case 'u':
				zuval = va_arg(ap, size_t);
				goto uinteger;

			case 'd':
				lval = va_arg(ap, ssize_t);
				goto integer;
			default:
				goto end;
			}
			break;
		default:
			i = f(i, *p, str, fp);
			goto end;
		}

		string:
			len = strlen(sval);
			if (off < len && padding > len - off)
			{
				if (len > off)
					padding += len - off;
			}
			__padding(len, padding, f, i, ' ', str, fp);
			for (z = 0; *sval && z < off; sval++, ++z) {
				i = f(i, *sval, str, fp);
			}
			goto end;
		character:
			i = f(i, cval, str, fp);
			goto end;
		integer:
			convlen = __int2str(converted, lval, base);
			__padding(convlen, padding, f, i, ' ', str, fp);
			for (j = 0; j < convlen; ++j) {
				i = f(i, converted[j], str, fp);
			}
			memset(converted, 0, convlen);
			goto end;
		uinteger:
			convlen = __uint2str(converted, zuval, base);
			__padding(convlen, padding, f, i, ' ', str, fp);
			for (j = 0; j < convlen; ++j) {
				i = f(i, converted[j], str, fp);
			}
			memset(converted, 0, convlen);
			goto end;
		floating:
			// ALT_FORM|ZERO_PAD|LEFT_ADJ|PAD_POS|MARK_POS|GROUPED
			convlen = fmt_fp(converted, fval, 19, 6, ZERO_PAD|LEFT_ADJ, 'f');
			for (j = 0; convlen--; ++j) {
				if (converted[j] == '.') {
					if (convlen > precision) {
						convlen = precision;
					}
				}
				i = f(i, converted[j], str, fp);
			}
		end:
			precision = 6;
			off = INT_MAX;
			base = 10;
			padding = 0;
			zeropad = 0;
			altform = 0;
			leftadj = 0;
			signage = 0;
			pls2spc = 0;
	}
	
	if (flag == 3) { /* dprintf flush */
		f(i, -1, str, fp);
	}else if (flag > 0) {
		if (flag == 2)
			f(bound, 0, str, fp);
		else
			f(i, 0, str, fp); /* don't incr for '\0' */
	}
	return i;
}

