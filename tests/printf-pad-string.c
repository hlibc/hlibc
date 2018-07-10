#include <stdio.h>

int main(void)
{
	printf("=====================\n");
	printf("whitespace padding %%10s and %%10d\n");
	printf("%10s\n", "hello");
	printf("%10d\n", 1234);


	printf("whitespace padding %%4s and %%4d\n");
	printf("%4s\n", "hello");
	printf("%4d\n", 1234);

	printf("whitespace padding %%10.3s\n");
	printf("%10.3s\n", "hello world");
 

	printf("whitespace padding %%10.3s\n");
	printf("%2.9s\n", "hello this is a world");

	printf("=====================\n");

	return 0;
}
