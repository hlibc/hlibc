#include "../internal/internal.h"
#include <stdarg.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdint.h>
#include <float.h>
#include <errno.h>

static int __convtab[20] = { '0', '1', '2', '3', '4', '5', '6', '7',
			     '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };
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

size_t __printf_buffer(size_t i, int x, char *s, FILE *o)
{
	(void)s;
	putc(x, o);
	return i + 1;
}

static size_t __sprintf_family(size_t i, int x, char *s, FILE *o) 
{
	(void)o;
	s[i] = x;
	s[i + 1] = 0;
	return i + 1;
}

size_t __snprintf_buffer(size_t i, int x, char *s, FILE *o)
{
	return __sprintf_family(i, x, s, o);
}

size_t __sprintf_buffer(size_t i, int x, char *s, FILE *o)
{
	return __sprintf_family(i, x, s, o);
}

static size_t __uint2str_inter(char *s, uintmax_t n, int base, size_t i)
{
	if (n / base) {
		i = __uint2str_inter(s, n / base, base, i);
	}
	s[i] = __convtab[(n % base)];
	return ++i;
}

static size_t __int2str_inter(char *s, intmax_t n, int base, size_t i)
{
	if (-n / base) {
		i = __int2str_inter(s, n / base, base, i);
	}
	s[i] = __convtab[+(-(n % base))];
	return ++i;
}

static size_t __int2str(char *s, intmax_t n, int base)
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

static size_t __uint2str(char *s, uintmax_t n, int base)
{
	size_t i = 0;
	return __uint2str_inter(s, n, base, i);
}

int __printf_inter(FILE *fp, char *str, size_t lim, __f f, const char *fmt, va_list ap)
{ 
	char *p = NULL;
	size_t i = 0;
	size_t bound = INT_MAX;
	int base = 10;

	/* Hold converted numerical strings */
	char converted[LDBL_MANT_DIG];
	converted[0] = 0;
	size_t convlen = 0;
	size_t j = 0;

	/* data types */
	int cval = 0;
	char *sval = NULL;
	size_t len = 0;
	uintmax_t zuval = 0;
	intmax_t lval = 0;
	long double fval = 0;

	/* float precision */
	size_t precision = 6;

	/* field width */
	size_t off = SIZE_MAX;	/* upper bound for meaningful comparison */
	size_t z = 0;
	size_t padding = 0;
	int zeropad = 0;
	int altform = 0;
	int signage = 0;
	int leftadj = 0;
	int pls2spc = 0;
	int hasdot = 0;
	char padd = ' ';
	size_t pp = 0;

	if (f == __snprintf_buffer) {
		bound = lim - 1;
	}

	for (p = (char*)fmt; *p && i < bound; p++) {
		if (*p != '%') {
			i = f(i, *p, str, fp);
			goto end;
		}
		++p;

		start:
		switch (*p) {
		case '.':
			hasdot = 1;
			if (isdigit(*++p))
				precision = off = strtol(p, &p, 10);
			goto start;
		case '*':
			++p;
			if (hasdot == 0)
				padding = va_arg(ap, int);
			else
				off = va_arg(ap, int);
			goto start;
		case '0':
			zeropad = 1;
			padd = '0';
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
			zeropad = 0;
			padd = ' ';
			sval = va_arg(ap, char *);
			goto string;
		case 'o':
			base = 8;
			zuval = va_arg(ap, unsigned int);
			goto uinteger;
		case 'd':
		case 'i':
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
			case 'i':
				lval = va_arg(ap, long);
				goto integer;
			case 'o':
				zuval = va_arg(ap, unsigned long);
				base = 8;
				goto uinteger;
			case 'u':
				zuval = va_arg(ap, unsigned long);
				goto uinteger;
			case 'l':
				switch (*++p) {
				case 'd':
				case 'i':
					lval = va_arg(ap, long long);
					goto integer;
				case 'u':
					zuval = va_arg(ap, unsigned long long);
					goto uinteger;
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
			case 'i':
				lval = va_arg(ap, ssize_t);
				goto integer;
			case 'o':
				zuval = va_arg(ap, size_t);
				base = 8;
				goto uinteger;
			default:
				goto end;
			}
			break;
		case 'j':
			switch (*++p) {
			case 'u':
				zuval = va_arg(ap, unsigned long long);
				goto uinteger;
			case 'd':
			case 'i':
				lval = va_arg(ap, long long);
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
			if (leftadj == 0)
			{
				if (off < len && padding > len - off)
				{
					if (len > off)
						padding += len - off;
				}
				for (size_t pp=0; padding > len+ pp;++pp) {
					i = f(i, padd, str, fp);
				}
			}
			for (z = 0; *sval && z < off; sval++, ++z) {
				i = f(i, *sval, str, fp);
			}
			if (leftadj == 1) { 
				for (size_t pp=0; padding > z+ pp;++pp) {
					i = f(i, padd, str, fp);
				}
			}
			goto end;
		character:
			i = f(i, cval, str, fp);
			goto end;
		integer:
			convlen = __int2str(converted, lval, base);
			if (leftadj == 0) {
				for (size_t pp=0;padding > convlen+ pp;++pp) {
					i = f(i, padd, str, fp);
				}
			}
			for (j = 0; j < convlen; ++j) {
				i = f(i, converted[j], str, fp);
			}
			if (leftadj == 1 && j < padding) {
				for (size_t pp=0;padding > j  + pp;++pp) {
					i = f(i, padd, str, fp);
				}
			}
			goto end;
		uinteger:
			convlen = __uint2str(converted, zuval, base);
			if (leftadj == 0) {
				for (size_t pp=0;padding > convlen + pp;++pp) {
					i = f(i, padd, str, fp);
				}
			}
			for (j = 0; j < convlen; ++j) {
				i = f(i, converted[j], str, fp);
			}
			if (leftadj == 1 && j < padding) {
				for (size_t pp=0; padding < j+ pp;++pp) {
					i = f(i, padd, str, fp);
				}
			}
			goto end;
		floating:
			/* 	fmt_fp accepts the following flags:
				ALT_FORM|ZERO_PAD|LEFT_ADJ|PAD_POS|MARK_POS|GROUPED
			*/
			convlen = fmt_fp(converted, fval, 19, precision, ZERO_PAD|LEFT_ADJ, 'f');
			for (j = 0; convlen--; ++j) {
				if (converted[j] == '.') {
					if (convlen > precision) {
						convlen = precision;
					}
				}
				i = f(i, converted[j], str, fp);
			}
		end:
			converted[0] = 0;
			precision = 6;
			off = SIZE_MAX;
			base = 10;
			padding = 0;
			zeropad = 0;
			altform = 0;
			leftadj = 0;
			signage = 0;
			pls2spc = 0;
			hasdot = 0;
			padd = ' ';
	}
		
	
	if (f == __dprintf_buffer) { /* dprintf flush */
		f(i, -1, str, fp); /* don't incr for dprintf flushing */
	}else if (f != __printf_buffer) {
		if (f == __snprintf_buffer)
			f(bound, 0, str, fp);
		else
			f(i, 0, str, fp); /* don't incr for '\0' */
	}
	
	if (i >= INT_MAX) {
		errno = EOVERFLOW;
		i = 0;
	}

	return i;
}

