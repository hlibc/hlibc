#define _XOPEN_SOURCE 500
#include <ftw.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>

static int
display_info(const char *fpath, const struct stat *sb,
							int tflag, struct FTW *ftwbuf)
{
	char pathname[128] = {0};
	char * ppname = getcwd(pathname, 127);
	printf("ppname=%s\n", ppname);

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
		case FTW_DP:
			printf("dp"); break;
		case FTW_SLN:
			printf("sln"); break;
		default:
			printf("?"); break;
	}

	printf(" %ld", (intmax_t)sb->st_size);
	printf(" %d", ftwbuf->base);
	printf(" %d", ftwbuf->level);
	printf(" %s", fpath);
	printf(" %s", fpath + ftwbuf->base);
	printf(" %s\n", ppname);

	return 0;			/* To tell nftw() to continue */
}

int
main(int argc, char *argv[])
{
	int flags = 0;


	if (argc > 2 && strchr(argv[2], 'd') != NULL)
		flags |= FTW_DEPTH;
	if (argc > 2 && strchr(argv[2], 'p') != NULL)
		flags |= FTW_PHYS;
	if (argc > 2 && strchr(argv[2], 'c') != NULL)
		flags |= FTW_CHDIR;
	if (argc > 2 && strchr(argv[2], 'm') != NULL)
		flags |= FTW_MOUNT;

	printf("debug a\n");
	if (nftw((argc < 2) ? "." : argv[1], display_info, 20, flags) == -1)
	{
		perror("nftw");
		exit(EXIT_FAILURE);
	}


	exit(EXIT_SUCCESS);
}
