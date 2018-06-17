#include "../internal/internal.h"
#include <stdarg.h>
#include <string.h>

static int __convtab[20] = { '0', '1', '2', '3', '4', '5', '6', '7',
			     '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };

static int (*__glb)(size_t incr, int x, char *s, FILE *fp);

static int __dprintf_buffer(size_t incr, int x, char *s, FILE *fp)
{
	(void)s;
	static char b[BUFSIZ];
        static size_t i = 0;
        if (x > -1)
                b[i++] = x;
        if (i == BUFSIZ || x == -1)
        {
                write(fp - stdout, b, i);
                i = 0;
        }
	return incr + 1;
}

static int __printf_buffer(size_t incr, int x, char *s, FILE *fp)
{
	(void)s;
	putc(x, fp); 
	return incr + 1;
}

static int __sprintf_buffer(size_t incr, int x, char *s, FILE *fp)
{
	(void)fp;
	s[incr] = x;
	return incr + 1;
}

static size_t __uint2str_inter(size_t n, int base, size_t i, size_t incr, char *s, FILE *fp, size_t bound)
{
	if (i == bound)
		return i;
	if (n / base) {
		i = __uint2str_inter(n / base, base, i, incr, s, fp, bound);
	}
	i = __glb(i, __convtab[(n % base)], s, fp);
	return i;
}

static size_t __int2str_inter(long long n, int base, size_t i, size_t incr, char *s, FILE *fp, size_t bound)
{
	if (i==bound)
		return bound;
	if (-n / base) {
		i = __int2str_inter(n / base, base, i, incr, s, fp, bound);
	}
	i = __glb(i, __convtab[+(-(n % base))], s, fp);
	return i;
}

static size_t __int2str(long long n, int base, size_t incr, char *s, FILE *fp, size_t bound)
{
	size_t i = 0;
	if (n >= 0) {
		n = -n;
	}
	else {
		i = __glb(i, '-', s, fp);
	}
	return __int2str_inter(n, base, i, incr, s, fp, bound);
}

static size_t __uint2str(size_t n, int base, size_t incr, char *s, FILE *fp, size_t bound)
{
	size_t i = 0;
	return __uint2str_inter(n, base, i, incr, s, fp, bound);
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
	static int (*d)(size_t incr, int x, char *s, FILE *fp);
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
		d = __sprintf_buffer;
	}
	else if (flag == 1){
		d = __sprintf_buffer;
	}
	else if (flag == 0) {
		d = __printf_buffer;
	}
	else if (flag == 3) {
                d = __dprintf_buffer;
	}

	__glb = d;

	for (p = fmt; *p && i < bound ; p++) {
		if (*p != '%') {
			i = d(i, *p, str, fp);
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
			i = d(i, *p, str, fp);
			break;
		string:
			for (; *sval; sval++) {
				i = d(i, *sval, str, fp);
			}
			break;
		character:
			i = d(i, cval, str, fp);
			break;
		integer:
			i += __int2str(lval, base, i, str, fp, bound);
			break;
		uinteger:
			i += __uint2str(zuval, base, i, str, fp, bound);
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
				i = d(i, converted[j], str, fp);
			}
			memset(converted, 0, 100);
			break;
		}
	}
	
	if (flag == 3) { /* dprintf flush */
		d(i, -1, str, fp);
	}else if (flag > 0) {
		d(i, '\0', str, fp); /* don't incr for '\0' */
	}
	return i;
}

