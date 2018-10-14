/*
	Copyright 2010 Rich Felker

	Modifications to this file are Copyright 2017 Christopher M. Graff
*/
#include "../internal/internal.h"
#include <stdint.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdarg.h>
#include <string.h>
#include <inttypes.h>
#include <fcntl.h>
#include <limits.h>
#include <errno.h>
#include <ctype.h>
#include <math.h>
#include <float.h>
#include <string.h>
static uint64_t pt[30] = {
	1, 
	2, 4, 8, 16, 32,
	64, 128, 256, 512, 1024,
	2048, 4096, 8192, 16384, 32768,
	65536, 131072, 262144, 524288, 1048576,
	2097152, 4194304, 8388608, 16777216, 33554432,
	67108864, 134217728, 268435456, 536870912,
};

static size_t __last = 0;

static void out(char *f, const char *s, size_t l)
{
	memcpy(f + __last, s, l);
	__last += l;
}

static void pad(char *f, char c, int w, int l, int fl)
{
	char pad[256];
	if (fl & (LEFT_ADJ | ZERO_PAD) || l >= w) return;
	l = w - l;
	memset(pad, c, l>sizeof pad ? sizeof pad : l);
	for (; l >= sizeof pad; l -= sizeof pad)
		out(f, pad, sizeof pad);
	out(f, pad, l);
}

static char *fmt_u(uintmax_t x, char *s)
{
	unsigned long y;
	for (; x>ULONG_MAX; x/=10) 
		*--s = '0' + x%10;
	for (y=x; y; y/=10)
		*--s = '0' + y%10;
	return s;
}

int fmt_fp(char *f, long double y, int w, int p, int fl, int t)
{
	__last = 0;
	/*
		We massivly overshoot the size needed for the bignum
		arrays so as to avoid pedantry and over-complication.
	*/
	uint32_t bignum[LDBL_MANT_DIG * 5];
	uint32_t *a, *d, *r, *z;
	int e2=0, e, i, j, l;
	char buf[LDBL_MANT_DIG * 5], *s;
	const char *prefix="-0X+0X 0X-0x+0x 0x";
	int pl;
	uint64_t base = 1000000000;

	pl=1;
	if (y<0 || 1/y<0) {
		y=-y;
	} else if (fl & MARK_POS) {
		prefix+=3;
	} else if (fl & PAD_POS) {
		prefix+=6;
	} else prefix++, pl=0;

	if (!isfinite(y)) {
		char *s = (t&32)?"inf":"INF";
		if (y!=y)
			s=(t&32)?"nan":"NAN", pl=0;
		pad(f, ' ', w, 3+pl, fl&~ZERO_PAD);
		out(f, prefix, pl);
		out(f, s, 3);
		pad(f, ' ', w, 3+pl, fl^LEFT_ADJ);
		return MAX(w, 3+pl);
	}

	y = frexpl(y, &e2) * 2;
	if (y)
		e2--;
	
	if (p<0)
		p=6;

	if (y)
		y *= 0x1p28, e2-=28;

	if (e2<0)
		a = r = z = bignum;
	else
		a = r = z = bignum+sizeof(bignum)/sizeof(*bignum) - LDBL_MANT_DIG - 1;

	do {
		*z = y;
		y = base*(y-*z++);
	} while (y);

	uint32_t carry = 0;
	int sh = 0;
	/*
		2^N ...
		2^4  16 2^5  32 2^6  64 2^7  128  2^8 256  2^9 512   
		low sh stays between 4 and 512 as 2->9
		high sh stays between 4 and 536870912 as 2->29
	*/
	/* this is a bignum multiplication */ 
	while (e2>0) {
		carry = 0;
		sh = MIN(29, e2);
		for (d = z-1; d>=a; d--) {
			uint64_t x = ((uint64_t)*d * pt[sh])+carry;
			*d = x % base;
			carry = x / base;
		}
		if (!z[-1] && z > a)
			z--;
		if (carry)
		{
			a--;
			*a = carry;
		}
		e2-=sh; 
	}

	/* this is a bignum division/remainder variant */
	while (e2<0) {
		carry = 0;
		sh = MIN(9, -e2);
		for (d = a; d<z; d++) {
			uint32_t rm = *d % pt[sh];
			*d = (*d / pt[sh]) + carry;
			carry = (base / pt[sh]) * rm;
		}
		if (!*a)
			a++;
		if (carry)
			*z++ = carry;
		e2+=sh;
	}
	
	
	if (a<z)
		for (i=10, e=9*(r-a); *a>=i; i*=10, e++)
			;
	else
		e=0;


	/* Perform rounding: j is precision after the radix (possibly neg) */
	j = p - ((t|32)!='f')*e - ((t|32)=='g' && p);
	if (j < 9*(z-r-1)) {
		uint32_t x;
		/* We avoid C's broken division of negative numbers */
		d = r + 1 + (j+9*LDBL_MAX_EXP)/9 - LDBL_MAX_EXP;
		j += 9*LDBL_MAX_EXP;
		j %= 9;
		for (i=10, j++; j<9; i*=10, j++)
			;
		x = *d % i;
		//x = __mod(*d, i);
		/* Are there any significant digits past j? */
		if (x || d+1!=z) {
			long double round = CONCAT(0x1p,LDBL_MANT_DIG);
			long double small;
			//if (*d/i & 1)
			//if (__mod(*d/i, 1) == 0)
			if (*d/i % 1 == 0)
				round += 2;
			if (x<i/2)
				small=0x0.8p0;
			else if (x==i/2 && d+1==z)
				small=0x1.0p0;
			else
				small=0x1.8p0;
			if (pl && *prefix=='-')
				round*=-1, small*=-1;
			*d -= x;
			/* Decide whether to round by probing round+small */
			if (round+small != round) {
				*d = *d + i;
				while (*d > (base-1)) {
					*d--=0;
					(*d)++;
				}
				if (d<a)
					a=d;
				for (i=10, e=9*(r-a); *a>=i; i*=10, e++)
					;
			}
		}
		if (z>d+1)
			z=d+1;
		for (; !z[-1] && z>a; z--)
			;
	}
	
	l = 1 + p + (p || (fl&ALT_FORM));
	if ((t|32)=='f') {
		if (e>0)
			l+=e;
	} 

	pad(f, ' ', w, pl+l, fl);
	out(f, prefix, pl);
	pad(f, '0', w, pl+l, fl^ZERO_PAD);


	if (a>r)
		a=r;
	for (d=a; d<=r; d++) {
		char *s = fmt_u(*d, buf+9);
		if (d!=a) while (s>buf)
			*--s='0';
		else if (s==buf+9)
			*--s='0';
		out(f, s, buf+9-s);
	}
	if (p || (fl&ALT_FORM))
		out(f, ".", 1);
	for (; d<z && p>0; d++, p-=9) {
		char *s = fmt_u(*d, buf+9);
		while (s>buf)
			*--s='0';
		out(f, s, MIN(9,p));
	}
	pad(f, '0', p+9, 9, 0);
	
	pad(f, ' ', w, pl+l, fl^LEFT_ADJ);

	return MAX(w, pl+l);
}

