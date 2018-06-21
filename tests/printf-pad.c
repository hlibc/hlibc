#include <stdio.h>

int main(void)
{
	printf("=====================\n");
	printf("whitespace padding %%Nd\n");
	printf("%10s\n", "hell");
	printf("%10d\n", 1234);
	printf("=====================\n");

	printf("truncate floats\n");
	printf("%.3f\n", 3.33333);
	printf("%.10f\n", 3.33333);
	printf("=====================\n");

	printf("Alternate verse regular form %%#x\n");
	printf("%x\n", 0xDEADBEEF);
	printf("%#x\n", 0xDEADBEEF);
	printf("=====================\n");

	printf("0 padding %%012d\n");
	printf("%012d\n", 1234);
	printf("=====================\n");

	return 0;
}
