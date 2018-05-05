#include <stdio.h>
#include <stdlib.h>

/*
	This code is taken from the posix specification as a test for getline.
*/

int main(void)
{
	FILE *stream;
	char *line = NULL;
	size_t len = 0;
	ssize_t read;

	stream = fopen("/etc/fstab", "r");
	if (stream == NULL)
		exit(EXIT_FAILURE);

	while ((read = getline(&line, &len, stream)) != -1) {
		printf("Retrieved line of length %zu :\n", read);
		printf("%s", line);
	}

	free(line);
	fclose(stream);
	exit(EXIT_SUCCESS);
}

