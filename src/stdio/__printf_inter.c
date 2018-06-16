#include "../internal/internal.h"
#include <stdarg.h>
#include <string.h>

static int __convtab[20] = { '0', '1', '2', '3', '4', '5', '6', '7',
			     '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };

static void __dprintf_buffer(int x, FILE *f)
{ 
	static char b[BUFSIZ];
	static size_t i = 0;
	if (x > -1)
		b[i++] = x;
	if (i == BUFSIZ || x == -1)
	{
		write(f - stdout, b, i);
		i = 0;
	}
}

static int __populate1(size_t incr, int x, char *s, FILE *fp)
{
	(void)s;
	__dprintf_buffer(x, fp); 
	return incr + 1;
}

static int __populate2(size_t incr, int x, char *s, FILE *fp)
{
	(void)s;
	putc(x, fp); 
	return incr + 1;
}

static int __populate3(size_t incr, int x, char *s, FILE *fp)
{
	(void)fp;
	s[incr] = x;
	return incr + 1;
}

static int __populate(size_t incr, int x, int flag, char *s, FILE *fp)
{
	if (flag == 3) {
		__dprintf_buffer(x, fp);
	}else if (flag > 0) {
		s[incr] = x;
	}
	else {
		putc(x, fp);
	}
	return incr + 1;
}

static size_t __uint2str_inter(size_t n, int base, size_t i, size_t incr, int flag, char *s, FILE *fp, size_t bound)
{
	if (i == bound)
		return i;
	if (n / base) {
		i = __uint2str_inter(n / base, base, i, incr, flag, s, fp, bound);
	}
	i = __populate(i, __convtab[(n % base)], flag, s, fp);
	return i;
}

static size_t __int2str_inter(long long n, int base, size_t i, size_t incr, int flag, char *s, FILE *fp, size_t bound)
{
	if (i==bound)
		return bound;
	if (-n / base) {
		i = __int2str_inter(n / base, base, i, incr, flag, s, fp, bound);
	}
	i = __populate(i, __convtab[+(-(n % base))], flag, s, fp);
	return i;
}

static size_t __int2str(long long n, int base, size_t incr, int flag, char *s, FILE *fp, size_t bound)
{
	size_t i = 0;
	if (n >= 0) {
		n = -n;
	}
	else {
		i = __populate(i, '-', flag, s, fp);
	}
	return __int2str_inter(n, base, i, incr, flag, s, fp, bound);
}

static size_t __uint2str(size_t n, int base, size_t incr, int flag, char *s, FILE *fp, size_t bound)
{
	size_t i = 0;
	return __uint2str_inter(n, base, i, incr, flag, s, fp, bound);
}

int __printf_inter(FILE *fp, char *str, size_t lim, int flag, const char *fmt, va_list ap)
{
	/* flag == 1 == sprintf */
	/* flag == 2 == snprintf */
	/* flag == 3 == dprintf */
	/* flag == 0 == printf, vprintf, dprintf etc  */
	

	const char *p = NULL;
	size_t i = 0;
	/* this should probably be INT_MAX */
	size_t bound = (size_t)-1;
	int base = 10;

	/* Hold converted numerical strings */
	char converted[BUFSIZ] = { 0 };
	size_t convlen = 0;
	size_t j = 0;

	/* data types */
	int cval = 0;
	char *sval = NULL;
	size_t zuval = 0;
	long long lval = 0;
	long double fval = 0;

	/* float precision */
	size_t precision = 6;

	if (flag == 2) { /* snprintf */
		bound = lim; // +1?
	}

	for (p = fmt; *p && i < bound ; p++) {
		if (*p != '%') {
			i = __populate(i, *p, flag, str, fp);
			continue;
		}
		++p;
		switch (*p) {
		case 'c':
			cval = va_arg(ap, int);
			goto character;
		case 's':
			sval = va_arg(ap, char *);
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
			break;
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
				break;
			case 'f':
				fval = va_arg(ap, double);
				goto floating;
			default:
				break;
			}
			break;
		case 'z':
			switch (*++p) {
			case 'u':
				zuval = va_arg(ap, size_t);
				goto uinteger;

			case 'd':
				lval = va_arg(ap, ssize_t);
				goto integer;
			default:
				break;
			}
			break;
		default:
			i = __populate(i, *p, flag, str, fp);
			break;
		string:
			for (; *sval; sval++) {
				i = __populate(i, *sval, flag, str, fp);
			}
			break;
		character:
			i = __populate(i, cval, flag, str, fp);
			break;
		integer:
			i += __int2str(lval, base, i, flag, str, fp, bound);
			break;
		uinteger:
			i += __uint2str(zuval, base, i, flag, str, fp, bound);
			break;
		floating:
			// ALT_FORM|ZERO_PAD|LEFT_ADJ|PAD_POS|MARK_POS|GROUPED
			memset(converted, 0, 100);
			convlen = fmt_fp(converted, fval, 19, 6, LEFT_ADJ, 'f');
			for (j = 0; convlen--; ++j) {
				if (converted[j] == '.') {
					if (convlen > precision) {
						convlen = precision;
					}
				}
				i = __populate(i, converted[j], flag, str, fp);
			}
			memset(converted, 0, 100);
			break;
		}
	}
	
	if (flag == 3) {
		__dprintf_buffer(-1, fp);
	}else if (flag > 0) {
		__populate(i, '\0', flag, str, fp); /* don't incr for '\0' */
	}
	return i;
}

