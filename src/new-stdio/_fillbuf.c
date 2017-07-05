#include <gstdio.h> 

int _fillbuf(GFILE *fp)
{
	int bufsize = 0;
	static char buffer[BUFSIZ] = { 0 };

	if ((fp->flags & (_READ | _EOF | _ERR)) != _READ)
		return EOF;
	bufsize = (fp->flags & _UNBUF) ? 1 : BUFSIZ;
	if (fp->buf == NULL)
		fp->buf = buffer;
	fp->rp = fp->buf;
	fp->len = read(fp->fd, fp->rp, bufsize);

	if (--fp->len < 0)
	{
		if (fp->len == -1)
			fp->flags |= _EOF;
		else
			fp->flags |= _ERR;
		fp->len = 0;
		gfflush(NULL);
		return EOF;
	}

	return (unsigned char) *fp->rp++;
}

