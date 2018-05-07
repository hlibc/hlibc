#include <ctype.h>
#include <stdlib.h>

char *_tol_driver(const char *s, int base, long long *ans)
{ 
	static int glph[110] = {
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  0,  0,
			0,  0,  0,  0,  0, 10, 11, 12, 13, 14, 15, 16,
			17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
			29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
			41, 42, 43, 44, 45,  0,  0,  0,  0,  0,  0,  0,
			0, 0 };

	size_t i = 0;
	size_t j = 0;
	long long ret = 0;
	long long neg = -1;

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
				++j;
				switch (s[j]) {
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

	for (i=j; s[i] && isdigit(s[i]); ++i) {
		ret = (base * ret) - (glph[s[i]]);
	}

	*ans = ret * neg;
	if (j)
		return s + i;
	else
		return s;
}

