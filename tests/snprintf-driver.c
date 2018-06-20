#include <stdio.h>

int main1(void)
{
	char *s = "This is a string literal";
	char b[1024];
	size_t len = snprintf(b, 5, "%s", s);
	printf ("'%s' -- and snprintf returned %zu\n", b, len);
	return 0;
}


int main2(void)
{
	size_t n = 5252123125;
	char b[1024];
	size_t len = snprintf(b, 5, "%zu", n);
	printf ("'%s' -- and snprintf returned %zu\n", b, len);
	return 0;
}

int trial(size_t len)
{
	printf("and main returned %zu\n", len);
}

int main3(void)
{
	char *s = "This is a string literal";
	char b[1024];
	size_t len = 0;
	len = snprintf(b, 100, "%s", s);
	printf ("'%s'\n", b);
	trial(len);
	return 0;
}


int main4(void)
{
	int n = 52525;
	char b[1024];
	size_t len = snprintf(b, 5, "%d", n);
	printf ("'%s' -- and snprintf returned %zu\n", b, len);
	return 0;
}

int main(void)
{
	main1();
	main2();
	main3();
	main4();
	return 0;
}
