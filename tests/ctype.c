#include <stdio.h>
#include <ctype.h>

void ctype_driver(char *m1, size_t n, int (*f)(int), char *data)
{ 
	size_t passes = 0;
	for (passes = 0;f(*data++);++passes) {
		printf("%s pass = %zu\n", m1, passes);
	}
	printf("%s should have %zu passes and it has %zu\n", m1, n, passes);
}

int main(void)
{
	char *white = "\t\n\f\v\r padd"; // tack on 4 failure bytes to each test
	char *digit = "0123456789    ";
	char *alpha = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ    ";
	char *alnum = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ    ";
	char *punct = "!@#$%^&*()_+,./<>?;':\"[]\\{}|`~-    ";
	char *upper = "ABCDEFGHIJKLMNOPQRSTUVWXYZ    ";
	char *lower = "abcdefghijklmnopqrstuvwxyz    ";
	char cntrl[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17,
			18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 'p', 'a', 'd', 'd' };
	char *xdigit = "abcdefABCDEF    ";
	char *blank = "\t padd";

	ctype_driver("isspace", 6, isspace, white);
	ctype_driver("isdigit", 10, isdigit, digit);
	ctype_driver("isalpha", 52, isalpha, alpha);
	ctype_driver("isalnum", 62, isalnum, alnum);
	ctype_driver("ispunct", 31, ispunct, punct);
	ctype_driver("islower", 26, islower, lower);
	ctype_driver("isupper", 26, isupper, upper);
	ctype_driver("iscntrl", 32, iscntrl, cntrl);
	ctype_driver("isxdigit", 12, isxdigit, xdigit);
	ctype_driver("isblank", 2, isblank, blank);

	ctype_driver("isalpha", 0, isalpha, punct);
	ctype_driver("isdigit", 0, isdigit, alpha);
	ctype_driver("isdigit", 0, isdigit, white);
	ctype_driver("isdigit", 0, isdigit, punct);

	return 0;
}
