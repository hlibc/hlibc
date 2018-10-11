#include <sys/syscall.h>
#include <dirent.h>
int getdents(unsigned int fd, struct dirent *dirp, unsigned int count)
{
        return syscall(SYS_getdents, fd, dirp, count);
}

