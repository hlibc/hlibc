#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

int main(void)
{
	char	*token,	*string, *tofree;

	tofree = string = strdup("abc,def,ghi");
	assert(string != NULL);

	while ((token = strsep(&string, ",")) != NULL)
		printf("%s\n", token);

	free(tofree);

	return 0;
}
