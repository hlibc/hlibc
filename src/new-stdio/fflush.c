#include <gstdio.h>

int gfflush(GFILE *fp)
{
	int ret = 0; 
	size_t i = 0; 
	/* fflush(NULL) flushes all fd */
	if ( fp == NULL )
	{
		for ( fp = gstdout; i < FOPEN_MAX ; ++fp, ++i) 
			if ( fp->buf != NULL ) 
				ret = _flushbuf(EOF, fp); 
		
	}
	else if (fp->flags & _WRITE)
		ret = _flushbuf(EOF, fp);

	fp->rp = fp->buf;
	fp->len = (fp->flags & _UNBUF) ? 1 : BUFSIZ; 
	fp->buf = NULL;
	return ret;
}
