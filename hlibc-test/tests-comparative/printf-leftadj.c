#include <stdio.h>

int main(void)
{
	printf("=====================\n");
	printf("whitespace padding with left adj %%-10s and %%-10d\n");
	printf("space %-10s world\n", "hello");
	printf("space %-10d world\n", 1234);
	printf("=====================\n");

	return 0;
}
