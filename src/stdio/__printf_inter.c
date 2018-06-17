#include "../internal/internal.h"
#include <stdarg.h>
#include <string.h>

static int __convtab[20] = { '0', '1', '2', '3', '4', '5', '6', '7',
			     '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };

static int (*__populate)(size_t incr, int x, char *s, FILE *fp);

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

static size_t __uint2str(size_t n, int base, size_t incr, char *s, FILE *fp, size_t bound)
{

	
	if (n / base) {
		 incr = __uint2str(n / base, base, incr, s, fp, bound);
	}
	
	if (incr >= bound )
		return bound;
	return __populate(incr, __convtab[(n % base)], s, fp);
}

static size_t __int2str_inter(long long n, int base, size_t incr, char *s, FILE *fp, size_t bound)
{
	
	
	
	if (-n / base) {
		incr = __int2str_inter(n / base, base, incr, s, fp, bound);
	}
	if (incr >= bound )
		return bound;
	return __populate(incr, __convtab[+(-(n % base))], s, fp);
}

static size_t __int2str(long long n, int base, size_t incr, char *s, FILE *fp, size_t bound)
{ 
	if (n >= 0) {
		n = -n;
	}
	else {
		incr = __populate(incr, '-', s, fp);
	}
	return __int2str_inter(n, base, incr, s, fp, bound);
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
	static int (*f)(size_t incr, int x, char *s, FILE *fp);
	/* data types */
	int cval = 0;
	char *sval = NULL;
	size_t zuval = 0;
	long long lval = 0;
	long double fval = 0;

	/* float precision */
	size_t precision = 6;

	if (flag == 2) {	/* flag 2 == snprintf */
		bound = lim; // +1?
		__populate = f = __sprintf_buffer;
	}
	else if (flag == 1){	/* flag 1 == sprintf */
		__populate = f = __sprintf_buffer;
	}
	else if (flag == 0) {	/* flag 0 == printf, vprintf */
		__populate = f = __printf_buffer;
	}
	else if (flag == 3) {	/* flag 3 == dprintf */
                __populate = f = __dprintf_buffer;
	}

	for (p = fmt; *p && i < bound; p++) {
		if (*p != '%') {
			i = f(i, *p, str, fp);
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
			i = f(i, *p, str, fp);
			break;
		string:
			for (; *sval; sval++) {
				if (i < bound -1)
					i = f(i, *sval, str, fp);
				else
					++i;
			}
			break;
		character:
			i = f(i, cval, str, fp);
			break;
		integer:
			i = __int2str(lval, base, i, str, fp, bound - 1);
			if (i == bound -1)
				++i;
			base = 10;
			break;
		uinteger:
			i = __uint2str(zuval, base, i, str, fp, bound -1 );
			if (i == bound -1)
				++i;
			base = 10;
			break;
		floating:
			// ALT_FORM|ZERO_PAD|LEFT_ADJ|PAD_POS|MARK_POS|GROUPED
			convlen = fmt_fp(converted, fval, 19, 6, LEFT_ADJ, 'f');
			for (j = 0; convlen--; ++j) {
				if (converted[j] == '.') {
					if (convlen > precision) {
						convlen = precision;
					}
				}
				i = f(i, converted[j], str, fp);
			}
			break;
		}
	
	}
	
	if (flag == 3) { /* dprintf flush */
		f(i, -1, str, fp);
	}else if (flag > 0) {
		f(i, 0, str, fp); /* don't incr for '\0' */
	}
	return i;
}

