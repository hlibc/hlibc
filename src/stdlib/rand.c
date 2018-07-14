#include <stdio.h>

static ssize_t cache = 1;

int rand(void)
{
	cache = cache * 1103515245 + 12345;
	return (cache / 65536) % 32768;
}

void srand(unsigned int seed)
{
	cache = seed;
}
/*
	Warning!! FIXME!! 
	using rand and srand for rand and srandom is wrong. But hlibc
	needs this for now in order to build GNU bc
*/
long int random(void)
{
	return rand();
}

void srandom(unsigned int seed)
{
	srand(seed);
}

