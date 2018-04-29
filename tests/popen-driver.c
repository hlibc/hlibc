#include <stdio.h>
#include <limits.h>

int main(int argc, char *argv[])
{
	FILE *fp;
	char path[4096];
	char argstring[PATH_MAX*2] = { 0 };
	size_t len = 0;
	
	while (--argc > 0) 
		len += sprintf(argstring + len, "%s ", *++argv);

	if ((fp = popen(argstring, "r")) == NULL)
		return 1;

	while (fgets(path, 4096, fp) != NULL)
		fprintf(stdout, "%s", path);

	pclose(fp);
	return 0;
}


