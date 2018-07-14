#include <stdio.h>

#define RUN_TEST(a) { \
extern int test_ ##a (void); \
int e = test_ ##a (); \
if (e) printf("%s test failed, %d error(s)\n", #a, e); \
else   printf("%s test passed\n", #a); \
err += e; \
}

int main()
{
	int err=0;
	RUN_TEST(qsort);
	RUN_TEST(string);
	RUN_TEST(strtol);
	RUN_TEST(basename);
	RUN_TEST(dirname);
	printf("\ntotal errors: %d\n", err);
	return !!err;
}
