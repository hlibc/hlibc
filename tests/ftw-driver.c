#define _XOPEN_SOURCE 500
#include <ftw.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>

static int
display_info(const char *fpath, const struct stat *sb,
	int tflag)
{
	char pathname[128] = {0};
	char * ppname = getcwd(pathname, 127);

	switch(tflag) {
		case FTW_D:
			printf("d"); break;
		case FTW_DNR:
			printf("dnr"); break;
		case FTW_F:
			printf("f");
			if (S_ISBLK(sb->st_mode)) {
				printf(" b");
			} else if (S_ISCHR(sb->st_mode)) {
				printf(" c");
			} else if (S_ISFIFO(sb->st_mode)) {
				printf(" p");
			} else if (S_ISREG(sb->st_mode)) {
				printf(" r");
			} else if (S_ISSOCK(sb->st_mode)) {
				printf(" s");
			} else {
				printf(" ?");
			}
			break;
		case FTW_SL:
			printf("sl"); break;
		case FTW_NS:
			printf("ns"); break;
		default:
			printf("?"); break;
	}

	printf(" %lld", (long long)sb->st_size);
	printf(" %s", fpath);
	printf(" %s\n", ppname);

	return 0;			/* To tell nftw() to continue */
}

int
main(int argc, char *argv[])
{
	if (ftw((argc < 2) ? "." : argv[1], display_info, 20) == -1)
	{
		perror("ftw");
		exit(EXIT_FAILURE);
	}

	exit(EXIT_SUCCESS);
}
