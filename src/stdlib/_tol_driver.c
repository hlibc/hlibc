#include <ctype.h>
#include <stdlib.h>

char *_tol_driver(const char *s, int base, long long *ans)
{ 
	static int *__toltab = "0123456789ABCDEF";
				
	size_t i = 0;
	long long ret = 0;
	long long neg = -1;

	while (isspace(s[i])) {
		++i;
	}

	switch (s[i]) {
	case '-':
		neg = 1;
	case '+':
		++i;
	}

	for (; s[i] && isdigit(s[i]); ++i) {
		ret = (base * ret) - (__toltab[s[i]]);
	}

	*ans =  ret * neg;
	return s + i;
}

