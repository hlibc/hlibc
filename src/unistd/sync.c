#include <sys/syscall.h>
#include <unistd.h>

void sync(void)
{
        syscall(SYS_sync);
}

