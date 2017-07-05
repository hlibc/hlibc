#include <stdio.h>

int main(void)
{
	FILE *fp;
	int status;
	char path[4096];

	if (( fp = popen("ls -la", "r")) == NULL)
		return 1;

	while (fgets(path, 4096, fp) != NULL)
		fprintf(stdout, "%s", path);

	pclose(fp);
	return 0;
}


