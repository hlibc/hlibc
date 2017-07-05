#include <gstdio.h> 

char *gfgets(char *s, int n, GFILE *iop)
{
	register int c;
	register char *cs;
	cs = s;
	while (--n > 0 && (c = ggetc(iop)) != EOF)
		if ((*cs++ = c) == '\n')
			break;
	*cs = '\0';
	return (c == EOF && cs == s) ? NULL : s;
}
