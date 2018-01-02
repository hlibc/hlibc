#include <string.h>

/* Copyright 2017 Adrian Parvin D. Ouano */

static inline long long unsigned int hash(long unsigned n)
{
	// TODO: Use a better hash
	return n*n + n;
}

char *strstr(const char *haystack, const char *needle)
{
	const char *n = needle, *h = haystack;
	long long unsigned int n_hash = 0, h_hash = 0;
	const char *n_;
	const char *h_;	
	
	for (; *n != '\0' && *h != '\0'; ++n, ++h)
	{
		n_hash += hash(*n);
		h_hash += hash(*h);
	}

	// A longer needle can't fit in a shorter haystack. 
	if (*n != '\0')
		return NULL;

	
	// haystack refers to the beginning of the substring
	// h refers to the end of the substring
	for (;*h != '\0'; ++h, ++haystack) {
		for (;*h != '\0' && n_hash != h_hash; ++h, ++haystack) {
			h_hash += hash(*h) - hash(*haystack);
		}
		*n_ = needle;
		for (*h_ = haystack; *n_ != '\0' && *h_ != '\0'; ++h_, ++n_) {
			if (*h_ != *n_)
				break;
		}
		if (*n_ == '\0')
			return haystack;
	}
	return NULL;
}
