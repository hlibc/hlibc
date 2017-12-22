#include "../internal/internal.h"
#include <stdarg.h>
#include <string.h> /* only for memset() */

size_t __uint2str(char *s, size_t n, int base, size_t i)
{
	if (n / base) {
		i = 0;
		i = __uint2str(s, n / base, base, i);
	}
	if (n % base + '0' > '9') {
		s[i] = (n % base + '0' + 39);
	}
	else {
		s[i] = (n % base + '0');
	}
	return ++i;
}

size_t __int2str(char *s, long long n, int base, size_t i)
{
	/* Do these calculations in the negative range */
	long long val = 0;
	if (-n / base) {
		i = 0;
		i = __int2str(s, n / base, base, i);
	}
	if (n % base + '0' > '9') {
		s[i] = (-(n % base) + '0' + 39);
	}
	else {
		s[i] = (-(n % base) + '0');
	}

	return ++i;
}

size_t int2str(char *s, long long n, int base)
{
	size_t i = 0;
	int toggle = 0;
	if (n >= 0) {
		n = -n;
	}
	else {
		s[0]   = '-';
		toggle = 1;
	}
	return __int2str(s + toggle, n, base, i) + toggle;
}

size_t uint2str(char *s, size_t n, int base)
{
	int convtab[10] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
	size_t i = 0;
	if (n < 10) {
		s[0] = convtab[n];
		return 1;
	}
	return __uint2str(s, n, base, i);
}

/*

These are notes taken from dalias, they should be applied to the float
conversion routine below.  -graff

A:
10 is 1010 (<<3 | <<1) in binary so it increases the number of bits you'd
need to preserve the value by 2 each time you do it but a given floating
point type has fixed width so after a few steps you're throwing away data

B:
you could use a large array of doubles whose sum is the whole value, and
multiply by 10 in it but that's less efficient than an array of ints
since the exponents are redundant ultimately your bignum work should yield
a nice way to do it what's in musl is just very-special-case bignum without
generality to do other ops

*/

size_t flt2str(char *s, double flt)
{
	size_t i	= 0;
	long long real  = flt;
	double imag     = flt - real;
	int prec	= 20;
	int convtab[10] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };

	if (real != 0) {
		i = int2str(s, real, 10);
	}
	else {
		s[i++] = '0';
	}
	s[i++] = '.';

	if (imag > 0) {
		while (imag > 0 && --prec) {
			imag *= 10.0;
			real = imag;
			imag -= real;
			s[i++] = convtab[real];
		}
	}
	else {
		memset(s + i, '0', 20);
		i += 20;
	}
	return i;
}

int _populate(int incr, int x, int flag, char *s, FILE *fp)
{
	if (flag > 0) {
		*s = x;
	}
	else {
		putc(x, fp);
	}
	return incr + 1;
}

int _printf_inter(FILE *fp, char *str, size_t lim, int flag, const char *fmt, va_list ap)
{
	/* flag == 1 == sprintf */
	/* flag == 2 == snprintf */
	/* flag == 0 == printf, vprintf, dprintf etc  */

	const char *p = NULL;
	size_t i = 0;
	size_t bound = BUFSIZ;
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
		bound = lim;
	}

	for (p = fmt; *p && i < bound; p++) {
		if (*p != '%') {
			i = _populate(i, *p, flag, str++, fp);
			continue;
		}
		switch (*++p) {
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
			i = _populate(i, *p, flag, str++, fp);
			break;
		string:
			for (; *sval; sval++, ++i) {
				i = _populate(i, *sval, flag, str++, fp);
			}
			break;
		character:
			i = _populate(i, cval, flag, str++, fp);
			break;
		integer:
			memset(converted, 0, 100);
			convlen = int2str(converted, lval, base);
			for (j = 0; j < convlen; ++j) {
				i = _populate(i, converted[j], flag, str++, fp);
			}
			base = 10;
			break;
		uinteger:
			convlen = uint2str(converted, zuval, base);
			for (j = 0; j < convlen; ++j) {
				i = _populate(i, converted[j], flag, str++, fp);
			}
			break;
		floating:
			convlen = flt2str(converted, fval);
			for (j = 0; convlen--; ++j) {
				if (converted[j] == '.') {
					if (convlen > precision) {
						convlen = precision;
					}
				}
				i = _populate(i, converted[j], flag, str++, fp);
			}
			break;
		}
	}
	if (flag > 0) {
		_populate(i, '\0', flag, str, fp); /* don't incr for '\0' */
	}
	if (flag == 0) {
		_flushbuf(EOF, fp);
	}
	return i;
}

