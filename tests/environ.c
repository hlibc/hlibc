#include <stdio.h>

int main(int argc, char **argv, char **envp)
{
	size_t i = 0;
	for (; envp[i] != NULL; i++)
		printf("%s\n", envp[i]);
	return 0;
}
