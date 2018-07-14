#include <stdio.h>

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	size_t i = 0;
	for (; envp[i] != NULL; i++) {
		/* special case $_: bash will assign argv[0] to this. */
		if (strncmp(envp[i], "_=", 2)) {
			printf("%s\n", envp[i]);
		}
	}
	return 0;
}
