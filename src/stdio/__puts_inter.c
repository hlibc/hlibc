#include "../internal/internal.h"

int __puts_inter(const char *s, FILE *fp, int append)
{
	/* puts/fputs can't be implemented in terms of a call to fprintf because
	 * the printf family of function is only specified to handle INT_MAX
	 * number of bytes whereas puts has no such retriction.
	 */
	
	while ((*s)) {
		putc(*s++, fp);
	}
	if (append) {
		putc(append, fp);
	}
	if (ferror(fp))
		return EOF;
	return 0;
}
