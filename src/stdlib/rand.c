#include <stdio.h>

static ssize_t cache = 1;

int rand(void)
{
	cache = cache * 1103515245 + 12345;
	return (cache/65536) % 32768;
}

void srand(unsigned int seed)
{
	cache = seed;
}

