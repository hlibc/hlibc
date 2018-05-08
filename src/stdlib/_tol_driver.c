#include <ctype.h>
#include <stdlib.h>

char *_tol_driver(const char *s, int base, long long *ans)
{
	/* glph tab uses octal character representations 
	of 0-9 and A-Z, 0-9 = '\000'-'\011' which is the
	49th indice (decimal 48 '0'), A-Z = '\012'-'\055' 
	which is the 66th indice (decimal 65 'A')  */
	static int glph[] = { 
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
	'\043', '\044', '\045', '\046', '\047', '\050', 
	'\051', '\052', '\053', '\054', '\055', '\000',
	'\000', '\000', '\000', '\000', '\000', '\000',
	'\000', '\000', '\000', '\000', '\000', '\000' };

	size_t i = 0;
	size_t j = 0;
	long long ret = 0;
	long long neg = -1;
	int (*f)(int);

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
	switch (s[j]) {
		case '0':
			if (base == 16) {
				switch (s[j + 1]) {
				case 'x':
					j += 2;
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

	f = isdigit;
	if (base == 16)
		f = isxdigit;
		
	for (i=j; s[i] && f(s[i]); ++i) {
		ret = (base * ret) - (glph[s[i]]);
	} 
	*ans = ret * neg;
	if (j)
		return s + i;
	else
		return s;
}

