#include "../internal/internal.h"
#include <sys/syscall.h>
#include <dirent.h>
#include <stdlib.h>

DIR *opendir(const char *dirname)
{
	DIR *dirp;
	if (!(dirp = calloc(1, sizeof *dirp))) {
		return 0;
	}
	if ((dirp->fd = open(dirname, O_DIRECTORY|O_RDONLY|O_CLOEXEC)) < 0)
	{
		closedir(dirp);
		return 0;
	}
	return dirp;
}

int closedir(DIR *dirp)
{
	int ret = close(dirp->fd);
	free(dirp);
	return ret;
}


