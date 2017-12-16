#include <limits.h>
#include <unistd.h>
#include "syscall.h"
#include "libc.h"
#include <sys/resource.h>
#include "syscall.h"
#include <unistd.h>
#include <errno.h>
#include "syscall.h"
#include <string.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <string.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <sys/uio.h> 
#define _GNU_SOURCE
#include <sys/time.h>

int access(const char *filename, int amode)
{
	return syscall(SYS_access, filename, amode);
}
unsigned alarm(unsigned seconds)
{
	return syscall(SYS_alarm, seconds);
}
int chdir(const char *path)
{
	return syscall(SYS_chdir, path);
}
int chown(const char *path, uid_t uid, gid_t gid)
{
	return syscall(SYS_chown, path, uid, gid);
}
int close(int fd)
{
	return syscall(SYS_close, fd);
}
int dup2(int old, int new)
{
	int r;
	while ((r=__syscall(SYS_dup2, old, new))==-EBUSY);
	return __syscall_ret(r);
}
int dup(int fd)
{
	return syscall(SYS_dup, fd);
}
void _exit(int status)
{
	_Exit(status);
}
char *getcwd(char *buf, size_t size)
{
	char tmp[PATH_MAX];
	if (!buf) buf = tmp, size = PATH_MAX;
	if (syscall(SYS_getcwd, buf, size) < 0) return 0;
	return buf == tmp ? strdup(buf) : buf;
}
gid_t getegid(void)
{
	return __syscall(SYS_getegid);
}
uid_t geteuid(void)
{
	return __syscall(SYS_geteuid);
}
gid_t getgid(void)
{
	return __syscall(SYS_getgid);
}
int getgroups(int count, gid_t list[])
{
	return syscall(SYS_getgroups, count, list);
}
int gethostname(char *name, size_t len)
{
	size_t i;
	struct utsname uts;
	if (uname(&uts)) return -1;
	if (len > sizeof uts.nodename) len = sizeof uts.nodename;
	for (i=0; i<len && (name[i] = uts.nodename[i]); i++);
	if (i==len) name[i-1] = 0;
	return 0;
}
char *getlogin(void)
{
	return getenv("LOGNAME");
}
pid_t getpgid(pid_t pid)
{
	return syscall(SYS_getpgid, pid);
}
pid_t getpgrp(void)
{
	return __syscall(SYS_getpgrp);
}
pid_t getpid(void)
{
	return __syscall(SYS_getpid);
}
pid_t getppid(void)
{
	return __syscall(SYS_getppid);
}
pid_t getsid(pid_t pid)
{
	return syscall(SYS_getsid, pid);
}
uid_t getuid(void)
{
	return __syscall(SYS_getuid);
}
int lchown(const char *path, uid_t uid, gid_t gid)
{
	return syscall(SYS_lchown, path, uid, gid);
}
int linkat(int fd1, const char *existing, int fd2, const char *new, int flag)
{
	return syscall(SYS_linkat, fd1, existing, fd2, new, flag);
}
int link(const char *existing, const char *new)
{
	return syscall(SYS_link, existing, new);
}
off_t lseek(int fd, off_t offset, int whence)
{
#ifdef SYS__llseek
	off_t result;
	return syscall(SYS__llseek, fd, offset>>32, offset, &result, whence) ? -1 : result;
#else
	return syscall(SYS_lseek, fd, offset, whence);
#endif
}
int nice(int inc)
{
#ifdef SYS_nice
	return syscall(SYS_nice, inc);
#else
	return setpriority(PRIO_PROCESS, 0, getpriority(PRIO_PROCESS, 0)+inc);
#endif
}
int pause(void)
{
	return syscall(SYS_pause);
}
int pipe(int fd[2])
{
	return syscall(SYS_pipe, fd);
}
ssize_t pread(int fd, void *buf, size_t size, off_t ofs)
{
	return syscall(SYS_pread, fd, buf, size, __SYSCALL_LL_O(ofs));
}
ssize_t pwrite(int fd, const void *buf, size_t size, off_t ofs)
{
	return syscall(SYS_pwrite, fd, buf, size, __SYSCALL_LL_O(ofs));
}
ssize_t read(int fd, void *buf, size_t count)
{
	return syscall(SYS_read, fd, buf, count);
}
ssize_t readlinkat(int fd, const char *path, char *buf, size_t bufsize)
{
	return syscall(SYS_readlinkat, fd, path, buf, bufsize);
}
ssize_t readlink(const char *path, char *buf, size_t bufsize)
{
	return syscall(SYS_readlink, path, buf, bufsize);
}
ssize_t readv(int fd, const struct iovec *iov, int count)
{
	return syscall(SYS_readv, fd, iov, count);
}
int renameat(int oldfd, const char *old, int newfd, const char *new)
{
	return syscall(SYS_renameat, oldfd, old, newfd, new);
}
int rmdir(const char *path)
{
	return syscall(SYS_rmdir, path);
}
int symlinkat(const char *existing, int fd, const char *new)
{
	return syscall(SYS_symlinkat, existing, fd, new);
}
int symlink(const char *existing, const char *new)
{
	return syscall(SYS_symlink, existing, new);
}
void sync(void)
{
	__syscall(SYS_sync);
}
pid_t tcgetpgrp(int fd)
{
	int pgrp;
	if (ioctl(fd, TIOCGPGRP, &pgrp) < 0)
		return -1;
	return pgrp;
}
int tcsetpgrp(int fd, pid_t pgrp)
{
	int pgrp_int = pgrp;
	return ioctl(fd, TIOCSPGRP, &pgrp_int);
}
int truncate(const char *path, off_t length)
{
	return syscall(SYS_truncate, path, __SYSCALL_LL_O(length));
}
unsigned ualarm(unsigned value, unsigned interval)
{
	struct itimerval it = {
		.it_interval.tv_usec = interval,
		.it_value.tv_usec = value
	};
	setitimer(ITIMER_REAL, &it, &it);
	return it.it_value.tv_sec*1000000 + it.it_value.tv_usec;
}
int unlinkat(int fd, const char *path, int flag)
{
	return syscall(SYS_unlinkat, fd, path, flag);
}
int unlink(const char *path)
{
	return syscall(SYS_unlink, path);
}
ssize_t write(int fd, const void *buf, size_t count)
{
	return syscall(SYS_write, fd, buf, count);
}
ssize_t writev(int fd, const struct iovec *iov, int count)
{
	return syscall(SYS_writev, fd, iov, count);
}
