#include <gstdio.h> 

int __puts_inter(const char *s, GFILE *fp, int append)
{
	int c;
	while ((c = *s++))
		gputc(c, fp);
	if (append)
		gputc(append, fp);
	return gferror(fp) ? EOF : 0;
}
