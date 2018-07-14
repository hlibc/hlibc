#include <string.h>
#include <unistd.h>
#include <errno.h>

int main(void)
{
	char *message = strerror(EPERM);
	size_t len =strlen(message);
	write(1, message, len);
	write(1, "\n", 1);
	message = strerror(E2BIG);
	len =strlen(message);
	write(1, message, len);
	return 0;
}
