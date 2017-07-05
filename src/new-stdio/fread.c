#include <gstdio.h> 
size_t gfread(void *ptr, size_t size, size_t nmemb, GFILE *fp)
{
	size_t request = size * nmemb;
	size_t ret = read(fp->fd, ptr, request);
	return ret / size;
}
