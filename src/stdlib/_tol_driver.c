#include <ctype.h>
#include <stdlib.h>
#include <stdint.h>

/*
	Copyright 2018 CM Graff
	with various fixes by:
	Copyright 2018 Tuomo Venäläinen
	Copyright 2018 Zach van Rijn
	Copyright 2018 Adrian Parvin D. Ouano
	
	glph tab uses octal character representations of 0-9, A-Z and a-z. 
	0-9 = '\000'-'\011' located at the 49th indice (decimal 48 '0')
	A-Z = '\012'-'\055' located at the 66th indice (decimal 65 'A')
	a-z = '\012'-'\055' located at the 98th indice (decimal 97 'a')
*/



char *_tol_driver(const char *s, int base, long long *ans)
{ 
	static uint8_t glph[] = { 
	/* v    useless filler until the 1st isxdigit */
	'\000', '\000', '\000', '\000', '\000', '\000',
	'\000', '\000', '\000', '\000', '\000', '\000',
	'\000', '\000', '\000', '\000', '\000', '\000',
	'\000', '\000', '\000', '\000', '\000', '\000',
	'\000', '\000', '\000', '\000', '\000', '\000',
	'\000', '\000', '\000', '\000', '\000', '\000',
	'\000', '\000', '\000', '\000', '\000', '\000',
	'\000', '\000', '\000', '\000', '\000', '\000',
	/* v   0-9 start at 48 code points from zero. */
	'\000', '\001', '\002', '\003', '\004', '\005',
	'\006', '\007', '\010', '\011', '\000', '\000',
	/* A-Z start at 65 code points from zero.  v  */
	'\000', '\000', '\000', '\000', '\000', '\012', 
	'\013', '\014', '\015', '\016', '\017', '\020', 
	'\021', '\022', '\023', '\024', '\025', '\026', 
	'\027', '\030', '\031', '\032', '\033', '\034', 
	'\035', '\036', '\037', '\040', '\041', '\042',
	/* v   a-z start at 98 code points from zero. */
	'\043', '\000',	'\000',	'\000', '\000', '\000', 
	'\000', '\012', '\013', '\014', '\015', '\016', 
	'\017', '\020', '\021', '\022', '\023', '\024', 
	'\025', '\026', '\027', '\030', '\031', '\032', 
	'\033', '\034', '\035', '\036', '\037', '\040',
	'\041', '\042', '\043', '\000', '\000', '\000',
	'\000', '\000', '\000', '\000', '\000', '\000',
	'\000', '\000', '\000' };
	
	size_t i = 0;
	size_t j = 0;
	long long ret = 0;
	long long neg = -1;
	uint8_t temp = 0;

	if (base > 36)
		base = 36; // error? 
	else if (base == 1)
		base = 0;

	while (isspace(s[j])) {
		++j;
	}

	switch (s[j]) {
	case '-':
		neg = 1;
	case '+':
		++j;
		break; 
	default:
		break;
	}
	/* starts with a 0 .. might be hexadecimal or octal */
	switch (s[j]) {
		case '0':
			if (base == 16) {
				switch (s[j + 1]) {
				case 'x':
					j += 2;
					break;
				case 'X':
					j =+ 2;
					break;
				default:
					break;
				}
			}else if (base == 0){ 
				++j;
				base = 8;
			}
		default:
			break;
	}

	for (i=j; s[i] && isalnum(s[i]) ; ++i) {
		temp = glph[(int)s[i]];
		/* break if char val lies outside of the base's range */
		if (temp >= base)
			break;
		ret = (base * ret) - temp;
	}
	*ans = ret * neg;
	if (i > j)
		return (char*) s + i;
	else
		return (char *)s;
}

