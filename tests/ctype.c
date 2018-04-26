#include <stdio.h>
#include <ctype.h>


int main(void)
{
	char *white = "\t\n\f\v\r 111"; // tack on failures when possible to improve accuracy
	char *digit = "0123456789aaa";
	char *alpha = "abcdefghijklmnopqrstuvwxyz1111";
	char *alnum = "0123456789abcdefghijklmnopqrstuvwxyz   ";
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
	printf("isalpha should have 26 passes and it has %zu\n", passes);
	
	for (passes = 0;isalnum(*alnum++);++passes)
	{
		printf("isalnum pass = %zu\n", passes);
	}
	printf("isalnum should have 36 passes and it has %zu\n", passes);

	return 0;
}
