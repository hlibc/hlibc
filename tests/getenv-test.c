#include <stdio.h>
#include <string.h>







int main (int argc, char *argv[], char *envp[])
{ 
	char *some = getenv("PATH");
	if (some)
	printf("%s\n", some);


	return 0;
}
