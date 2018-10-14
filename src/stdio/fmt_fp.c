/*
	Copyright 2010 Rich Felker

	Modifications to this file are Copyright 2017 Christopher M. Graff

	This algorithm was likely derived from plan9 which was in turn derived
	from the dragon4 algorithm by Steele and White. The original paper
	can befound here:
		kurtstephens.com/files/p372-steele.pdf
	It is titled "How to Print Floating-Point Numbers Accurately" and is
	a canonical early and historical reference for float printing. It does
	however, referece the work of Knuth which helps to put perspective on 
	its place within historical context.

	The two main bignum operation loops are standalone and as far as my
	tests reveal are never both entered when printing a given float.

	'sh' is the incrementor used to access the powers of 2 array. the bignum
	operations can be considered to be a bignum multiplied or divided by the
	array of powers of 2

	The array of powers of 2 is notated as follows: 
	
		2^N ...
		2^4  16 2^5  32 2^6  64 2^7  128  2^8 256  2^9 512   
		low sh (division) stays between 4 and 512 as 2->9
		high sh (multiplication) stays between 4 and 536870912 as 2->29


	'd' the main pointer to the bignum does not need to be set at a particular
	pointer offset after it leaves the bignum multiplication and division
	operations. It therefore can be rewritten to be an array instead of 
	pointer offset operation. However, due to the diminishing offsets of
	'a' and 'z' this has proved difficult to do. Most of the unused temporary
	variables that I have added are here for the purpose of such a rewrite. They
	can of course be deleted.
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

/* powers of 2 table */
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
	uint32_t bignum[(LDBL_MAX_EXP+LDBL_MANT_DIG)/9+1];
	uint32_t *a, *d, *r, *z, *hold;
	int e2=0, e, i, j, l;
	char buf[9+LDBL_MANT_DIG/4], *s; 
	const char *prefix="-0X+0X 0X-0x+0x 0x";
	int pl;
	uint64_t base = 1000000000;

	uint32_t rm = 0; /* remainder */
	uint64_t prd = 0; /* product */
	uint32_t carry = 0; /* the same 'carry' as from grade school */
	char sh = 0; /* the iterator */


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

	size_t len = sizeof(bignum)/sizeof(*bignum) - LDBL_MANT_DIG - 1;

	y = frexpl(y, &e2) * 2;
	if (y)
		e2--;
	
	if (p<0)
		p=6;

	if (y)
		y *= 0x1p28, e2-=28;

	hold = bignum;

	if (e2<0)
		a = r = z = bignum;
	else
		a = r = z = bignum+len;

	do {
		/* here 'z' is incremented past 'a' for later use in look comparison */
		*z = y;
		y = base*(y-*z++);
	} while (y);

	
	/* this is a bignum multiplication */ 
	int k = z -hold;
	int ko =  z -hold;
	int lenz =  z -hold;
	
	while (e2>0) {
	
		sh = MIN(29, e2);
	
		for (carry = 0, d = z-1; d>=a; d--) {
			prd = *d * pt[sh] + carry;
			carry = prd / base;
			*d = prd % base;
		}
	
		/*
		for (carry = 0, k = (z-hold - (z-hold))-1; k>=( a-hold) - (a-hold) ; k--) {
			prd = d[k -1] * pt[sh] + carry;
			carry = prd / base;
			d[k -1]  = prd % base;
		}
	
		*/
		if (!z[-1] && z > a)
		{
			z--;
		}

	
		if (carry) {
			
			a--;
			*a = carry;
		}
	
		ko = a-hold;
		lenz = z-hold;
		e2-=sh; 
	}


	/* this is a bignum division/remainder variant */
	while (e2<0) {


		sh = MIN(9, -e2);
		for (carry = 0, d = a; d<z; d++) {
			rm = *d % pt[sh];
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

