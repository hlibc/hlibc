#include <stdlib.h>
#include <string.h>
#include <libgen.h>
#include <stdio.h>

#define TT(path, want) \
{ \
	char tmp[100]; \
	char *got = basename(strcpy(tmp, path)); \
	if (strcmp(want, got) != 0) \
		printf("basename(\"%s\") got \"%s\" want \"%s\"\n", path, got, want); \
}

int main(void)
{
	if (strcmp(basename(0), ".") != 0)
		printf("basename(0) returned \"%s\"; expected \".\"\n", basename(0));
	TT("", ".");
	TT("/usr/lib", "lib");
	TT("/usr/", "usr");
	TT("usr/", "usr");
	TT("/", "/");
	TT("///", "/");
	TT("//usr//lib//", "lib");
	TT(".", ".");
	TT("..", "..");
	return 0;
}
