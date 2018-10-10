#include <sys/select.h>
#include <sys/syscall.h>

int select(int nfds, fd_set *restrict readfds, fd_set *restrict writefds, fd_set *restrict errorfds, struct timeval *restrict timeout)
{
        return __syscall(SYS_select, nfds, readfds, writefds, errorfds, timeout);
}

