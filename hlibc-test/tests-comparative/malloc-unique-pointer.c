#include <stdlib.h>
#include <stdio.h>
 
int main(void)
{
	void *p = malloc(0);
	void *q = malloc(0);
	void *r = malloc(0);
	int lever = 0;
	if (!p || !q || !r){
		printf("malloc(0) returned NULL\n");
		lever = 1;
	}
	if (p == q || p == r || q == r){
		printf("malloc(0) returned non-unique pointers: %p, %p, %p\n", p, q, r);
		lever = 1;
	}
	if (lever == 0)
		printf("malloc(0) works and returns unique pointers\n");
	free(q);
	free(p);
	free(r);
	return 0;
}
