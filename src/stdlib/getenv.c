#include "../internal/internal.h"
#include <string.h>
#include <limits.h>

char *getenv(const char *name)
{
	size_t i = 0;
	size_t j = 0;
	for (;__environ[i]; ++i) { 
		for (j = 0;__environ[i][j]; j++) {
			
			if (name[j] != __environ[i][j] && __environ[i][j] != '=')
				break;
			if (__environ[i][j] == '=') 
				return __environ[i] + (j+1); 
			if (name[j] == '\0')
				break;
		}
	}
	return NULL;
}

