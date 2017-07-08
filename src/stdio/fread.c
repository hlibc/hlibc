#include <stdio.h> 
size_t fread(void *ptr, size_t size, size_t nmemb, FILE *fp)
{
	size_t request = size * nmemb;
	size_t ret = read(fp->fd, ptr, request);
	return ret / size;
}
