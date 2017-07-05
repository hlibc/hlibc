#include <gstdio.h> 

int gfclose(GFILE *fp)
{
	int ret = 0;
	if (fp != NULL )
	{
		if ((ret = gfflush(fp)) != EOF)
		{
			fp->rp = fp->buf = NULL;
			fp->len = 0;
			fp->flags &= ~(_READ | _WRITE);
			if (fp->pid == 0 )
				close(fp->fd);
			fp->pid = 0;
		}
	}
	return ret;
}
