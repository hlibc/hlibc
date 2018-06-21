#include "../internal/internal.h"
#include <stdarg.h>
#include <string.h>

static int __convtab[20] = { '0', '1', '2', '3', '4', '5', '6', '7',
			     '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };

typedef size_t (*__f)(size_t, int, char *, FILE *);

static size_t __dprintf_buffer(size_t i, int x, char *s, FILE *o)
{
	(void)s;
	static char b[BUFSIZ];
        static size_t j = 0;
        if (x > -1) {
                b[j++] = x;
	}
        if (i == BUFSIZ || x == -1){
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

size_t __uint2str(size_t n, int b, size_t i, char *s, FILE *o, size_t bound, __f f)
{ 
	if (n / b) {
		i = __uint2str(n / b, b, i, s, o, bound, f);
	} 
	if (i < bound)
		return f(i, __convtab[(n % b)], s, o);
	else
		return i + 1;
}

size_t __int2str_inter(long long n, int b, size_t i, char *s, FILE *o, size_t bound, __f f)
{ 
	if (-n / b) {
		i = __int2str_inter(n / b, b, i, s, o, bound, f);
	}
	if (i < bound)
		return f(i, __convtab[+(-(n % b))], s, o);
	else
		return i + 1;
}

size_t __int2str(long long n, int b, size_t i, char *s, FILE *o, size_t bound, __f f)
{ 
	if (n >= 0) {
		n = -n;
	}
	else {
		i = f(i, '-', s, o);
	}
	return __int2str_inter(n, b, i, s, o, bound, f);
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
	size_t zuval = 0;
	long long lval = 0;
	long double fval = 0;

	/* float precision */
	size_t precision = 6;

	size_t off = 0;
	size_t z = 0;

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

	for (p = fmt; *p && i < bound; p++, base = 10) {
		if (*p != '%') {
			i = f(i, *p, str, fp);
			continue;
		}
		++p;

		start:
		switch (*p) {
		case '.':
			if (isdigit(*++p))
				off = strtol(p, &p, 10);
			goto start;
		case '*':
			++p;
			off = va_arg(ap, int);
			goto start;
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
			z = 0;
			if (off) {
				for (; *sval && z < off; sval++, ++z) {
					i = f(i, *sval, str, fp);
				}
			} else {
				for (; *sval; sval++) {
	                                i = f(i, *sval, str, fp);
				}
			}
			break;
		character:
			i = f(i, cval, str, fp);
			break;
		integer:
			i = __int2str(lval, base, i, str, fp, bound, f);
			break;
		uinteger:
			i = __uint2str(zuval, base, i, str, fp, bound, f);
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
		if (flag == 2)
			f(bound, 0, str, fp);
		else
			f(i, 0, str, fp); /* don't incr for '\0' */
	}
	return i;
}

