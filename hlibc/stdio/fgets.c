#include <stdio.h>

char *fgets(char *s, int n, FILE *iop)
{
	register int c    = 0;
	register char *cs = s;

	while (--n > 0 && (c = getc(iop)) != EOF) {
		if ((*cs++ = c) == '\n') {
			break;
		}
	}
	*cs = '\0';
	return (c == EOF && cs == s) ? NULL : s;
}
