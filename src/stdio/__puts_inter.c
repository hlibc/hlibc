#include "../internal/internal.h"

int __puts_inter(const char *s, FILE *fp, int append)
{
	/* puts/fputs can't be implemented in terms of a call to fprintf because
	 * the printf family of function is only specified to handle INT_MAX
	 * number of bytes whereas puts has no such retriction.
	 */
	int c;
	while ((c = *s++)) {
		putc(c, fp);
	}
	if (append) {
		putc(append, fp);
	}
	return ferror(fp) ? EOF : 0;
}
