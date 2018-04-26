#include <stdio.h>
#include <ctype.h>


int main(void)
{
	char *white = "\t\n\f\v\r padd"; // tack on 4 failure bytes to each test
	char *digit = "0123456789    ";
	char *alpha = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ    ";
	char *alnum = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ    ";
	char *punct = "!@#$%^&*()_+,./<>?;':\"[]\\{}|`~-    ";
	char *upper = "ABCDEFGHIJKLMNOPQRSTUVWXYZ    ";
	char *lower = "abcdefghijklmnopqrstuvwxyz    ";
	char cntrlarr[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 
			18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 'p', 'a', 'd', 'd' };
	char *cntrl = cntrlarr;
	char *xdigit = "abcdefABCDEF";
	size_t passes = 0;


	for (passes = 0;isspace(*white++);++passes)
	{
		printf("isspace pass = %zu\n", passes);
	}
	printf("isspace should have 6 passes and it has %zu\n", passes);
	
	for (passes = 0;isdigit(*digit++);++passes)
	{
		printf("isdigit pass = %zu\n", passes);
	}
	printf("isdigit should have 10 passes and it has %zu\n", passes);

	for (passes = 0;isalpha(*alpha++);++passes)
	{
		printf("isalpha pass = %zu\n", passes);
	}
	printf("isalpha should have 52 passes and it has %zu\n", passes);
	
	for (passes = 0;isalnum(*alnum++);++passes)
	{
		printf("isalnum pass = %zu\n", passes);
	}
	printf("isalnum should have 62 passes and it has %zu\n", passes);

	for (passes = 0;ispunct(*punct++);++passes)
	{
		printf("ispunct pass = %zu\n", passes);
	}
	printf("ispunct should have 31 passes and it has %zu\n", passes);

	for (passes = 0;islower(*lower++);++passes)
	{
		printf("islower pass = %zu\n", passes);
	}
	printf("islower should have 26 passes and it has %zu\n", passes);

	for (passes = 0;isupper(*upper++);++passes)
	{
		printf("isupper pass = %zu\n", passes);
	}
	printf("isupper should have 26 passes and it has %zu\n", passes);
	
	for (passes = 0;iscntrl(*cntrl++);++passes)
	{
		printf("iscntrl pass = %zu\n", passes);
	}
	printf("iscntrl should have 32 passes and it has %zu\n", passes);

	for (passes = 0;isxdigit(*xdigit++);++passes)
	{
		printf("isxdigit pass = %zu\n", passes);
	}
	printf("isxdigit should have 12 passes and it has %zu\n", passes);


	return 0;
}
