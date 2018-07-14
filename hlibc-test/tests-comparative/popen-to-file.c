#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
	FILE *fp;
	FILE *outfile;
	char path[4096];
	char temp[1000] = { 0 };
	if (argc < 2) {
		fprintf(stderr, "%s needs an argument\n", *argv);
		return 1;
	}

	++argv;
	strcpy(temp, argv[1]);
	argv[1] = NULL;
	
	if ((outfile = fopen(temp, "w")) == NULL)
		return 1;

	if ((fp = popen(*argv, "r")) == NULL)
		return 1;

	while (fgets(path, 4096, fp) != NULL)
		fprintf(outfile, "%s", path);

	pclose(fp);
	fclose(outfile);
	return 0;
}


