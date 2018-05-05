#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static void displayenv(char *envt)
{
	char *t = getenv(envt);
	if (t)
		printf("%s:\n%s\n", envt, t);
}

int main (void)
{
	displayenv("PATH");
	displayenv("USER");
	displayenv("HOME");
	displayenv("PWD");
	displayenv("DISPLAY");
	return 0;
}
