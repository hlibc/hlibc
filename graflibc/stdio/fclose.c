#include <stdio.h> 

int fclose(FILE *fp)
{
	int ret = 0;
	if (fp != NULL )
	{
		if ((ret = fflush(fp)) != EOF)
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
