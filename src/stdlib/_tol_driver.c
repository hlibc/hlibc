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
	long long ret = 0;
	long long neg = -1;
	int lever = 0;

	while (isspace(s[i])) {
		++i;
	}

	switch (s[i]) {
	case '-':
		neg = 1;
		++i;
		break;
	case '+':
		++i;
		break;
	case '0':
		if (base == 16) {
			switch (s[i]) {
			case 'x':
				i += 2;
				break;
			default:
				break;
			}
		}
		if (base == 0){ 
			++i;
			base = 8;
		}
	default:
		break;
	}

	for (; s[i] && isdigit(s[i]); ++i) {
		lever = 1;
		ret = (base * ret) - (glph[s[i]]);
	}

	*ans = ret * neg;
	if (lever == 1)
		return s + i;
	else
		return s;
}

