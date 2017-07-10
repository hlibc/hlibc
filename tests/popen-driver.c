#include <stdio.h>

int main(int argc, char *argv[])
{
	FILE *fp;
	int status;
	char path[4096];

	++argv;

	if (( fp = popen(*argv, "r")) == NULL)
		return 1;

	while (fgets(path, 4096, fp) != NULL)
		fprintf(stdout, "%s", path);

	pclose(fp);
	return 0;
}


