#include <stdio.h> 

int __puts_inter(const char *s, FILE *fp, int append)
{
	int c;
	while ((c = *s++))
		gputc(c, fp);
	if (append)
		gputc(append, fp);
	return ferror(fp) ? EOF : 0;
}
