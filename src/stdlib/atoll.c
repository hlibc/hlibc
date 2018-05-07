#include <ctype.h>
#include <stdlib.h>

char *_tol_driver(const char *s, int base, long long *ans)
{ 
	static int *__toltab = "0123456789ABSCDEF";
				
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

long long strtoll(const char *s, char **end, int base)
{
	long long ans = 0;
	*end = _tol_driver(s, base, &ans);
	return ans;
}

long long atoll(const char *s)
{
	long long ans = 0;
	_tol_driver(s, 10, &ans);
	return ans;
}
