#include <stdio.h>
#include <time.h>

int main(void)
{
	time_t z = time(NULL);
	if (z != ((time_t)-1))
		printf("the time() function set the time without returning an error\n");
	else
		printf("the time() function did not set the time without returning an error\n");

	return 0;
}
