#include <dirent.h>
#include <unistd.h>
#include "__dirent.h"
#include "libc.h"

void rewinddir(DIR *dir)
{

	lseek(dir->fd, 0, SEEK_SET);
	dir->buf_pos = dir->buf_end = 0;
	dir->tell = 0;

}
