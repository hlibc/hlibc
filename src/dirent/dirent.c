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
	if ((dirp->fildes = open(dirname, O_DIRECTORY|O_RDONLY|O_CLOEXEC)) < 0)
	{
		closedir(dirp);
		return 0;
	}
	return dirp;
}

int closedir(DIR *dirp)
{
	int ret = close(dirp->fildes);
	free(dirp);
	return ret;
}

struct dirent *readdir(DIR *dirp)
{
	struct dirent *ret;
	size_t len = 0;

	if (dirp->position >= dirp->eob) {
		if (!(len = getdents(dirp->fildes, (struct dirent *)dirp->buffer, sizeof dirp->buffer)))
			return NULL;
		dirp->position = 0;
		dirp->eob = len;
	}
	ret = (struct dirent *)(dirp->buffer + dirp->position);
	dirp->position += ret->d_reclen;

	return ret;
}

