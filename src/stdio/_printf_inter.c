#include "../internal/internal.h"
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>


/* '0' - '0' and 'a' - 'f' */
static int __convtab[20] = {
	'\060', '\061', '\062', '\063',
	'\064', '\065', '\066', '\067',
	'\070', '\071', '\141', '\142',
	'\143', '\144', '\145', '\146' };

size_t __uint2str_inter(char *s, size_t n, int base, size_t i)
{
	if (n / base) {
		i = __uint2str_inter(s, n / base, base, i);
	}
	s[i] = __convtab[(n % base)];
	return ++i;
}

size_t __int2str_inter(char *s, long long n, int base, size_t i)
{
	if (-n / base) {
		i = __int2str_inter(s, n / base, base, i);
	}
	s[i] = __convtab[+(-(n % base))];
	return ++i;
}

size_t __int2str(char *s, long long n, int base)
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

size_t __uint2str(char *s, size_t n, int base)
{
	size_t i = 0;
	return __uint2str_inter(s, n, base, i);
}

static void _dprintf_buffer(int x, FILE *f)
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

int _populate(size_t *incr, int x, int flag, char **s, FILE *fp)
{
	(*incr)++;

	if (flag == 3) {
		_dprintf_buffer(x, fp);
	} else if (flag > 0) {
		**s = x;
		(*s)++;
	}
	else {
		return putc(x, fp);
	}
	return 0;
}

int _printf_inter(
	FILE *fp, char *str, size_t lim, int flag, const char *fmt, va_list ap)
{
	/* flag == 1 == sprintf */
	/* flag == 2 == snprintf */
	/* flag == 0 == printf, vprintf  */
	/* flag == 3 == dprintf, vdprintf */

	const char *p = NULL;
	size_t i = 0;
	size_t bound = BUFSIZ;

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

	if (flag == 2) { /* snprintf */
		;//snprintf functionality is disabled
	}

	for (p = fmt; *p; p++) {
		int long_count = 0;
		int base = 10;
	
		size_t field_width = 6;
		size_t precision = 6;
		
		if (*p != '%') {
			_populate(&i, *p, flag, &str, fp);
			continue;
		}
		++p;

		if (isdigit(*p))
			{
				field_width = strtol(p, &p, 10);
			}
		if (*p == '.') // Handle precision
			{
				precision = strtol(++p, &p, 10);
			}


		do { // Allocate a new loop-block in order to allow re-entry to the switch-case using `continue`
			// Handle long count
			switch (*p) {
			case 'l':
				++p;
				++long_count;
				continue;
			case 'L':
				++p;
				long_count = 2;
				continue;
				
				// Handle integrals
			case 'o':
			case 'x':
				base = *p == 'o' ? 8
						 : 16;
			case 'd':
				lval = long_count == 0 ? va_arg(ap, int) 
				     : long_count == 1 ? va_arg(ap, long)
				     :		   va_arg(ap, long long);
				goto integer;
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
			
				// Handle characters
			case 'c':
				cval = va_arg(ap, int);
				_populate(&i, cval, flag, &str, fp);
				break;
			
				// Handle strings
			case 's':
				sval = va_arg(ap, char *);
				for (; *sval; sval++) {
					_populate(&i, *sval, flag, &str, fp);
				}
				break;
			
				// Handle floating point
			case 'f':
			case 'g':
				fval = long_count < 2 ? va_arg(ap, double)
					              : va_arg(ap, long double) ;
				// ALT_FORM|ZERO_PAD|LEFT_ADJ|PAD_POS|MARK_POS|GROUPED
				convlen = fmt_fp(converted, fval, 19, 6, LEFT_ADJ, 'f');
				for (j = 0; convlen--; ++j) {
					if (converted[j] == '.') {
						if (convlen > precision) {
							convlen = precision;
						}
					}
					_populate(&i, converted[j], flag, &str, fp);
				}
				break;
				
			default:
				_populate(&i, *p, flag, &str, fp);
				break;
				
			integer:
				memset(converted, 0, 100);
				convlen = __int2str(converted, lval, base);
				for (j = 0; j < convlen; ++j) {
					_populate(&i, converted[j], flag, &str, fp);
				}
				base = 10;
				break;
			uinteger:
				convlen = __uint2str(converted, zuval, base);
				for (j = 0; j < convlen; ++j) {
					_populate(&i, converted[j], flag, &str, fp);
				}
				break;
			}
			break;
		} while (1);
	}
	if (flag == 3) {
		_dprintf_buffer(-1, fp);
		return i;
	}
	if (flag > 0) {
		--i;
		_populate(&i, '\0', flag, &str, fp); /* don't incr for '\0' */
	}
	return i;
}
