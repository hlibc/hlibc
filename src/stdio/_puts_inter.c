#include <stdio.h> 

int __puts_inter(const char *s, FILE *fp, int append)
{
	int c;
	while ((c = *s++))
		putc(c, fp);
	if (append)
		putc(append, fp);
	return ferror(fp) ? EOF : 0;
}
