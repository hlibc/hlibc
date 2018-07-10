#include <stdio.h>
#include <string.h>

void parseurl(char *argv)
{
	char *host;
	char *type;
	char *page;

	type = host = page = argv;
	
	if ((host = strstr(argv, "://")))
	{
		*host = '\0';
		host += 3;
	}
	if ((page = strstr(host, "/")))
		*page++ = '\0';

	printf("Attempting an [%s] protocol on [%s] to retrieve [%s]\n", type, host, page);
	
	return;
}

int main(void)
{
	//parseurl("https://www.gnu.org/home.en.html");
	char string1[1024] = { 0 };
	char string2[1024] = { 0 };
	char string3[1024] = { 0 };
	strcpy(string1, "https://www.musl-libc.org/releases/musl-0.9.0.tar.gz");
	strcpy(string2, "https://www.gnu.org/home.en.html");
	strcpy(string3, "http://www.csit.parkland.edu/~cgraff1/books/Isaac-Newton-Principia-English-1846.pdf");
	parseurl(string1);
	parseurl(string2);
	parseurl(string3);
	return 0;
}
