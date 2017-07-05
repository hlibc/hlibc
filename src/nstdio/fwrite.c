#include <stdio.h> 

size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *fp)
{
	size_t request = size * nmemb;
	size_t ret = write(fp->fd, ptr, request);
	return ret / size;
}

