#include <stdio.h>

int main(void)
{
	printf("=====================\n");
	printf("zero padding %%10s and %%10d\n");
	printf("%010s\n", "hello");
	printf("%010d\n", 1234);
	printf("zero padding %%4s and %%4d\n");
	printf("%04s\n", "hello");
	printf("%04d\n", 1234);
	printf("zero padding %%10.3s\n");
	printf("%010.3s\n", "hello world");
	printf("zero padding %%10.3s\n");
	printf("%02.9s\n", "hello this is a world");
	printf("=====================\n");

	return 0;
}

