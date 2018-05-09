#include <ctype.h>
#include <stdlib.h>
char *_tol_driver(const char *s, int base, long long *ans);
long long strtoll(const char *s, char **end, int base)
{
        long long ans = 0;
        *end = _tol_driver(s, base, &ans);
        return ans;
}

