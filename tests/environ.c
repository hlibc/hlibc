#include <stdio.h>

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	size_t i = 0;
	for (; envp[i] != NULL; i++)
		printf("%s\n", envp[i]);
	return 0;
}
