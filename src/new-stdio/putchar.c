#include <gstdio.h> 
int gputchar(int x)
{
	return gputc(x, gstdout);
}
