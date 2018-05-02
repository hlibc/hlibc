#include <dirent.h>
#include "__dirent.h"
#include <errno.h>
#include <fcntl.h>
#include <fenv.h>
#include "libc.h"
#include <limits.h>
#include <poll.h>
#include <signal.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "syscall.h"
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/mount.h>
#include <sys/resource.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/uio.h>
#include <sys/utsname.h>
#include <sys/wait.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>

int access(const char *filename, int amode)
{
#ifdef	SYS_access
	return syscall(SYS_access, filename, amode);
#else
	return syscall(SYS_faccessat, AT_FDCWD, filename, amode, 0);
#endif
}

int chdir(const char *path)
{
	return syscall(SYS_chdir, path);
}

int chown(const char *path, uid_t uid, gid_t gid)
{
#ifdef	SYS_chown
	return syscall(SYS_chown, path, uid, gid);
#else
	return syscall(SYS_fchownat, AT_FDCWD, path, uid, gid, 0);
#endif
}

int close(int fd)
{
	return syscall(SYS_close, fd);
}

int dup2(int old, int new)
{
	int r;
#ifdef SYS_dup2
	while ((r=__syscall(SYS_dup2, old, new))==-EBUSY);
#else
	if (old==new) {
		r = __syscall(SYS_fcntl, old, F_GETFD);
		if (r >= 0) return old;
	} else {
		while ((r=__syscall(SYS_dup3, old, new, 0))==-EBUSY);
	}
#endif
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

int ftruncate(int fd, off_t length)
{
	return syscall(SYS_ftruncate, fd, __SYSCALL_LL_O(length));
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
	return syscall(SYS_getegid);
}

uid_t geteuid(void)
{
	return syscall(SYS_geteuid);
}

gid_t getgid(void)
{
	return syscall(SYS_getgid);
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
#ifdef	SYS_getpgrp
	return syscall(SYS_getpgrp);
#else
	return syscall(SYS_getpgid, 0);
#endif
}

pid_t getpid(void)
{
	return syscall(SYS_getpid);
}

pid_t getppid(void)
{
	return syscall(SYS_getppid);
}

pid_t getsid(pid_t pid)
{
	return syscall(SYS_getsid, pid);
}

uid_t getuid(void)
{
	return syscall(SYS_getuid);
}

int linkat(int fd1, const char *existing, int fd2, const char *new, int flag)
{
	return syscall(SYS_linkat, fd1, existing, fd2, new, flag);
}

int link(const char *existing, const char *new)
{
#ifdef	SYS_link
	return syscall(SYS_link, existing, new);
#else
	return syscall(SYS_linkat, AT_FDCWD, existing, new);
#endif
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

int pipe(int fd[2])
{
#ifdef	SYS_pipe
	return syscall(SYS_pipe, fd);
#else
	return syscall(SYS_pipe2, fd, 0);
#endif
}

ssize_t read(int fd, void *buf, size_t count)
{
	return syscall(SYS_read, fd, buf, count);
}

ssize_t readlinkat(int fd, const char *path, char *buf, size_t bufsize)
{
	return syscall(SYS_readlinkat, fd, path, buf, bufsize);
}

ssize_t readlink(const char *restrict path, char *restrict buf, size_t bufsize)
{
#ifdef SYS_readlink
	return syscall(SYS_readlink, path, buf, bufsize);
#else
	return syscall(SYS_readlinkat, AT_FDCWD, path, buf, bufsize);
#endif
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
#ifdef SYS_rmdir
	return syscall(SYS_rmdir, path);
#else
	return syscall(SYS_unlinkat, AT_FDCWD, path, AT_REMOVEDIR);
#endif
}

int symlinkat(const char *existing, int fd, const char *new)
{
	return syscall(SYS_symlinkat, existing, fd, new);
}

int symlink(const char *existing, const char *new)
{
#ifdef SYS_symlink
	return syscall(SYS_symlink, existing, new);
#else
	return syscall(SYS_symlinkat, existing, AT_FDCWD, new);
#endif
}

void sync(void)
{
	syscall(SYS_sync);
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

int unlinkat(int fd, const char *path, int flag)
{
	return syscall(SYS_unlinkat, fd, path, flag);
}

int unlink(const char *path)
{
#ifdef SYS_unlink
	return syscall(SYS_unlink, path);
#else
	return syscall(SYS_unlinkat, AT_FDCWD, path, 0);
#endif
}

ssize_t write(int fd, const void *buf, size_t count)
{
	return syscall(SYS_write, fd, buf, count);
}

ssize_t writev(int fd, const struct iovec *iov, int count)
{
	return syscall(SYS_writev, fd, iov, count);
}

int closedir(DIR *dir)
{
	int ret = close(dir->fd);
	free(dir);
	return ret;
}

int getdents(int fd, struct dirent *buf, size_t len)
{
	return syscall(SYS_getdents, fd, buf, len);
}

DIR *opendir(const char *name)
{
	int fd;
	DIR *dir;

	if ((fd = open(name, O_RDONLY|O_DIRECTORY|O_CLOEXEC)) < 0)
		return 0;
	if (!(dir = calloc(1, sizeof *dir))) {
		syscall(SYS_close, fd);
		return 0;
	}
	dir->fd = fd;
	return dir;
}

int getdents(int, struct dirent *, size_t);

struct dirent *readdir(DIR *dir)
{
	struct dirent *de;
	
	if (dir->buf_pos >= dir->buf_end) {
		int len = getdents(dir->fd, (void *)dir->buf, sizeof dir->buf);
		if (len <= 0) return 0;
		dir->buf_end = len;
		dir->buf_pos = 0;
	}
	de = (void *)(dir->buf + dir->buf_pos);
	dir->buf_pos += de->d_reclen;
	dir->tell = de->d_off;
	return de;
}

extern char **__environ;

int clearenv()
{
	__environ[0] = 0;
	return 0;
}

char *getenv(const char *name)
{
	int i;
	size_t l = strlen(name);
	if (!__environ || !*name || strchr(name, '='))
		return NULL;
	for (i=0; __environ[i] && (strncmp(name, __environ[i], l)
		|| __environ[i][l] != '='); i++);
	if (__environ[i])
		return __environ[i] + l+1;
	return NULL;
}

int __libc_start_main(
	int (*main)(int, char **, char **), int argc, char **argv,
	int (*init)(int, char **, char **), void (*fini)(void),
	void (*ldso_fini)(void))
{
	char **envp = argv+argc+1, **auxv = envp;

	/* assign the environment from envp */
	__environ = envp;
	do auxv++; while (*auxv);
	libc.auxv = (void *)++auxv;
	libc.ldso_fini = ldso_fini;
	libc.fini = fini;

	/* ssp would go here if it was supported */

	/* Execute constructors (static) linked into the application */
	if (init) init(argc, argv, envp);

	/* Pass control to to application */
	exit(main(argc, argv, envp));
	return 0;
}

extern char **__environ;
char **__env_map;

int __putenv(char *s, int a)
{
	int i=0, j=0;
	char *end = strchr(s, '=');
	size_t l = end-s+1;
	char **newenv = 0;
	char **newmap = 0;
	static char **oldenv;
	
	if (!end || l == 1) return -1;
	for (; __environ[i] && memcmp(s, __environ[i], l); i++);
	if (a) {
		if (!__env_map) {
			__env_map = calloc(2, sizeof(char *));
			if (__env_map) __env_map[0] = s;
		} else {
			for (; __env_map[j] && __env_map[j] != __environ[i]; j++);
			if (!__env_map[j]) {
				newmap = realloc(__env_map, sizeof(char *)*(j+2));
				if (newmap) {
					__env_map = newmap;
					__env_map[j] = s;
					__env_map[j+1] = NULL;
				}
			} else {
				free(__env_map[j]);
			}
		}
	}
	if (!__environ[i]) {
		newenv = malloc(sizeof(char *)*(i+2));
		if (!newenv) {
			if (a && __env_map) __env_map[j] = 0;
			return -1;
		}
		memcpy(newenv, __environ, sizeof(char *)*i);
		newenv[i] = s;
		newenv[i+1] = 0;
		__environ = newenv;
		free(oldenv);
		oldenv = __environ;
	}

	__environ[i] = s;
	return 0;
}

int putenv(char *s)
{
	return __putenv(s, 0);
}

int __putenv(char *s, int a);

int setenv(const char *var, const char *value, int overwrite)
{
	char *s;
	int l1, l2;

	if (!var || !*var || strchr(var, '=')) {
		errno = EINVAL;
		return -1;
	}
	if (!overwrite && getenv(var)) return 0;

	l1 = strlen(var);
	l2 = strlen(value);
	s = malloc(l1+l2+2);
	memcpy(s, var, l1);
	s[l1] = '=';
	memcpy(s+l1+1, value, l2);
	s[l1+l2+1] = 0;
	if (__putenv(s, 1)) {
		free(s);
		errno = ENOMEM;
		return -1;
	}
	return 0;
}

extern char **__environ;
extern char **__env_map;

int unsetenv(const char *name)
{
	int i, j;
	size_t l = strlen(name);

	if (!*name || strchr(name, '=')) {
		errno = EINVAL;
		return -1;
	}
again:
	for (i=0; __environ[i] && (memcmp(name, __environ[i], l) || __environ[i][l] != '='); i++);
	if (__environ[i]) {
		if (__env_map) {
			for (j=0; __env_map[j] && __env_map[j] != __environ[i]; j++);
			free (__env_map[j]);
			for (; __env_map[j]; j++)
				__env_map[j] = __env_map[j+1];
		}
		for (; __environ[i]; i++)
			__environ[i] = __environ[i+1];
		goto again;
	}
	return 0;
}

void abort(void)
{
	//raise(SIGABRT);
	for (;;);
}

void __assert_fail(const char *expr, const char *file, int line, const char *func)
{
	fprintf(stderr, "Assertion failed: %s (%s: %s: %d)\n", expr, file, func, line);
	fflush(NULL);
	abort();
}

#define COUNT 32

static struct fl
{
	struct fl *next;
	void (*f[COUNT])(void *);
	void *a[COUNT];
} builtin, *head;

void __funcs_on_exit()
{
	int i;
	void (*func)(void *), *arg;

	for (; head; head=head->next)
	{
		for (i=COUNT-1; i>=0 && !head->f[i]; i--)
			;
		if (i<0) 
			continue;
		func = head->f[i];
		arg = head->a[i];
		head->f[i] = 0; 
		func(arg); 
	}
}

int __cxa_atexit(void (*func)(void *), void *arg)
{
	int i;
	/* Defer initialization of head so it can be in BSS */
	if (!head) head = &builtin;

	/* If the current function list is full, add a new one */
	if (head->f[COUNT-1])
	{
		struct fl *new_fl = calloc(sizeof(struct fl), 1);
		if (!new_fl) 
			return -1;
	
		new_fl->next = head;
		head = new_fl;
	}

	/* Append function to the list. */
	for (i=0; i<COUNT && head->f[i]; i++)
		;
	head->f[i] = func;
	head->a[i] = arg;
	return 0;
}

static void call(void *p)
{
	((void (*)(void))(uintptr_t)p)();
}

int atexit(void (*func)(void))
{
	return __cxa_atexit(call, (void *)(uintptr_t)func);
}

void __funcs_on_exit();

void exit(int code)
{
	__funcs_on_exit();
	fflush(NULL);
	if (libc.fini) libc.fini();
	if (libc.ldso_fini) libc.ldso_fini();
	_Exit(code);
	for(;;);
}

void _Exit(int ec)
{
	syscall(SYS_exit_group, ec);
	syscall(SYS_exit, ec);
}

int raise(int sig)
{ 
	return sig;
}

int fcntl(int fd, int cmd, ...)
{
	long arg;
	va_list ap;
	va_start(ap, cmd);
	arg = va_arg(ap, long);
	va_end(ap);
	if (cmd == F_SETFL) arg |= O_LARGEFILE;
	if (cmd == F_SETLKW) return syscall(SYS_fcntl, fd, cmd, arg);
	if (cmd == F_GETOWN) return __syscall(SYS_fcntl, fd, cmd, arg);
	return syscall(SYS_fcntl, fd, cmd, arg);
}

int openat(int fd, const char *filename, int flags, ...)
{
	mode_t mode;
	va_list ap;
	va_start(ap, flags);
	mode = va_arg(ap, mode_t);
	va_end(ap);
	return syscall(SYS_openat, fd, filename, flags|O_LARGEFILE, mode);
}

int open(const char *filename, int flags, ...)
{

	mode_t mode;
	va_list ap;
	va_start(ap, flags);
	mode = va_arg(ap, mode_t);
	va_end(ap);
#ifdef SYS_open
	return syscall(SYS_open, filename, flags|O_LARGEFILE, mode);
#else
	return syscall(SYS_openat, AT_FDCWD, filename, flags|O_LARGEFILE, mode);
#endif

}

int fegetexceptflag(fexcept_t *fp, int mask)
{
	*fp = fetestexcept(mask);
	return 0;
}

int feholdexcept(fenv_t *envp)
{
	fegetenv(envp);
	return 0;
}

int feclearexcept(int mask)
{
	return 0;
}

int feraiseexcept(int mask)
{
	return 0;
}

int fetestexcept(int mask)
{
	return 0;
}

int fegetround(void)
{
	return 0;
}

int fesetround(int r)
{
	return 0;
}

int fegetenv(fenv_t *envp)
{
	return 0;
}

int fesetenv(const fenv_t *envp)
{
	return 0;
}

int fesetexceptflag(const fexcept_t *fp, int mask)
{
	feclearexcept(~*fp & mask);
	feraiseexcept(*fp & mask);
	return 0;
}

int feupdateenv(const fenv_t *envp)
{
	int ex = fetestexcept(FE_ALL_EXCEPT);
	fesetenv(envp);
	feraiseexcept(ex);
	return 0;
}

/*
void _start()
{
	_Exit(1);
}
*/
int brk(void *end)
{
	return -(syscall(SYS_brk, end) != (unsigned long)end);
}

int chroot(const char *path)
{
	return syscall(SYS_chroot, path);
}

int mount(const char *special, const char *dir, const char *fstype, unsigned long flags, const void *data)
{
	return syscall(SYS_mount, special, dir, fstype, flags, data);
}

void *sbrk(intptr_t inc)
{
	unsigned long cur = syscall(SYS_brk, 0);
	if (inc && syscall(SYS_brk, cur+inc) != cur+inc) return (void *)-1;
	return (void *)cur;
}

pid_t wait4(pid_t pid, int *status, int options, struct rusage *usage)
{
	return syscall(SYS_wait4, pid, status, options, usage);
}

int getpriority(int which, id_t who)
{
	int ret = syscall(SYS_getpriority, which, who);
	if (ret < 0) return ret;
	return 20-ret;
}

int ioctl(int fd, int req, ...)
{
	void *arg;
	va_list ap;
	va_start(ap, req);
	arg = va_arg(ap, void *);
	va_end(ap);
	return syscall(SYS_ioctl, fd, req, arg);
}

int setpriority(int which, id_t who, int prio)
{
	return syscall(SYS_getpriority, which, who, prio);
}

int uname(struct utsname *uts)
{
	return syscall(SYS_uname, uts);
}

int mlockall(int flags)
{
	return syscall(SYS_mlockall, flags);
}

int mlock(const void *addr, size_t len)
{
	return syscall(SYS_mlock, addr, len);
}

void *mmap(void *start, size_t len, int prot, int flags, int fd, off_t off)
{
	void *ret;
	if (sizeof(off_t) > sizeof(long))
		if (((long)off & 0xfff) | ((long)((unsigned long long)off>>(12 + 8*(sizeof(off_t)-sizeof(long))))))
			start = (void *)-1;
#ifdef SYS_mmap2
	ret = (void *)syscall(SYS_mmap2, start, len, prot, flags, fd, off>>12);
#else
	ret = (void *)syscall(SYS_mmap, start, len, prot, flags, fd, off);
#endif
	return ret;
}

int mprotect(void *addr, size_t len, int prot)
{
	size_t start, end;
	start = (size_t)addr & -PAGE_SIZE;
	end = (size_t)((char *)addr + len + PAGE_SIZE-1) & -PAGE_SIZE;
	return syscall(SYS_mprotect, start, end-start, prot);
}

int msync(void *start, size_t len, int flags)
{
	return syscall(SYS_msync, start, len, flags);
}

int munlockall(void)
{
	return syscall(SYS_munlockall);
}

int munlock(const void *addr, size_t len)
{
	return syscall(SYS_munlock, addr, len);
}

int munmap(void *start, size_t len)
{
	int ret;
	ret = syscall(SYS_munmap, start, len);
	return ret;
}

ssize_t sendto(int fd, const void *buf, size_t len, int flags, const struct sockaddr *addr, socklen_t alen)
{
	return socketcall(sendto, fd, buf, len, flags, addr, alen);
}

int socket(int domain, int type, int protocol)
{
	return socketcall(socket, domain, type, protocol, 0, 0, 0);
}

int execl(const char *path, const char *argv0, ...)
{
	int argc;
	va_list ap;
	va_start(ap, argv0);
	for (argc=1; va_arg(ap, const char *); argc++);
	va_end(ap);
	{
		int i;
		char *argv[argc+1];
		va_start(ap, argv0);
		argv[0] = (char *)argv0;
		for (i=1; i<argc; i++)
			argv[i] = va_arg(ap, char *);
		argv[i] = NULL;
		return execv(path, argv);
	}
}

int execle(const char *path, const char *argv0, ...)
{
	int argc;
	va_list ap;
	va_start(ap, argv0);
	for (argc=1; va_arg(ap, const char *); argc++);
	va_end(ap);
	{
		int i;
		char *argv[argc+1];
		char **envp;
		va_start(ap, argv0);
		argv[0] = (char *)argv0;
		for (i=1; i<argc; i++)
			argv[i] = va_arg(ap, char *);
		argv[i] = NULL;
		envp = va_arg(ap, char **);
		return execve(path, argv, envp);
	}
}

int execlp(const char *file, const char *argv0, ...)
{
	int argc;
	va_list ap;
	va_start(ap, argv0);
	for (argc=1; va_arg(ap, const char *); argc++);
	va_end(ap);
	{
		int i;
		char *argv[argc+1];
		va_start(ap, argv0);
		argv[0] = (char *)argv0;
		for (i=1; i<argc; i++)
			argv[i] = va_arg(ap, char *);
		argv[i] = NULL;
		return execvp(file, argv);
	}
}

extern char **__environ;

int execv(const char *path, char *const argv[])
{
	return execve(path, argv, __environ);
}

int execve(const char *path, char *const argv[], char *const envp[])
{
	return syscall(SYS_execve, path, argv, envp);
}

int execvp(const char *file, char *const argv[])
{
	const char *p, *z, *path = getenv("PATH");
	size_t l, k;

	errno = ENOENT;
	if (!*file) return -1;

	if (strchr(file, '/'))
		return execv(file, argv);

	if (!path) path = "/usr/local/bin:/bin:/usr/bin";
	k = strnlen(file, NAME_MAX+1);
	if (k > NAME_MAX) {
		errno = ENAMETOOLONG;
		return -1;
	}
	l = strnlen(path, PATH_MAX-1)+1;

	for(p=path; ; p=z) {
		char b[l+k+1];
		z = strchr(p, ':');
		if (!z) z = p+strlen(p);
		if (z-p >= l) {
			if (!*z++) break;
			continue;
		}
		memcpy(b, p, z-p);
		b[z-p] = '/';
		memcpy(b+(z-p)+(z>p), file, k+1);
		execv(b, argv);
		if (errno != ENOENT) return -1;
		if (!*z++) break;
	}
	return -1;
}

int fexecve(int fd, char *const argv[], char *const envp[])
{
	static const char proc[] = "/proc/self/fd/%d";
	char buf[sizeof proc + 3*sizeof(int)];
	snprintf(buf, sizeof buf, proc, fd);
	execve(buf, argv, envp);
	if (errno == ENOENT) errno = EBADF;
	return -1;
}

pid_t wait(int *status)
{
	return waitpid((pid_t)-1, status, 0);
}

int waitid(idtype_t type, id_t id, siginfo_t *info, int options)
{
	return syscall(SYS_waitid, type, id, info, options, 0);
}

pid_t waitpid(pid_t pid, int *status, int options)
{
	return syscall(SYS_wait4, pid, status, options, 0);
}

int poll(struct pollfd *fds, nfds_t n, int timeout)
{
#ifdef SYS_poll
	return syscall(SYS_poll, fds, n, timeout);
#else
	return syscall(SYS_ppoll, fds, n, timeout>=0 ?
		&((struct timespec){ .tv_sec = timeout/1000,
		.tv_nsec = timeout%1000*1000000 }) : 0, 0, _NSIG/8);
#endif
}

int pselect(int n, fd_set *rfds, fd_set *wfds, fd_set *efds, const struct timespec *ts, const sigset_t *mask)
{
	long data[2] = { (long)mask, 8 };
	struct timespec ts_tmp;
	if (ts) ts_tmp = *ts;
	return syscall(SYS_pselect6, n, rfds, wfds, efds, ts ? &ts_tmp : 0, data);
}

int select(int n, fd_set *rfds, fd_set *wfds, fd_set *efds, struct timeval *tv)
{
	return syscall(SYS_select, n, rfds, wfds, efds, tv);
}

int chmod(const char *path, mode_t mode)
{ 
#ifdef SYS_chmod
	return syscall(SYS_chmod, path, mode);
#else
	return syscall(SYS_fchmodat, AT_FDCWD, path, mode);
#endif
}

int fchmodat(int fd, const char *path, mode_t mode, int flag)
{
	return syscall(SYS_fchmodat, fd, path, mode, flag);
}

int fchmod(int fd, mode_t mode)
{
	return syscall(SYS_fchmod, fd, mode);
}

int fstatat(int fd, const char *path, struct stat *buf, int flag)
{
#ifdef SYS_fstatat
	return syscall(SYS_fstatat, fd, path, buf, flag);
#else
	return syscall(SYS_newfstatat, fd, path, buf, flag);
#endif
}

int fstat(int fd, struct stat *buf)
{
	return syscall(SYS_fstat, fd, buf);
}

int futimens(int fd, const struct timespec times[2])
{
	return utimensat(fd, 0, times, 0);
}

int lchmod(const char *path, mode_t mode)
{
	return fchmodat(AT_FDCWD, path, mode, AT_SYMLINK_NOFOLLOW);
}

int lstat(const char *restrict path, struct stat *restrict buf)
{
#ifdef SYS_lstat
        return syscall(SYS_lstat, path, buf);
#else
        return syscall(SYS_fstatat, AT_FDCWD, path, buf, AT_SYMLINK_NOFOLLOW);
#endif
}

int mkdirat(int fd, const char *path, mode_t mode)
{
	return syscall(SYS_mkdirat, fd, path, mode);
}

int mkfifoat(int fd, const char *path, mode_t mode)
{
	return mknodat(fd, path, mode | S_IFIFO, 0);
}

int mkfifo(const char *path, mode_t mode)
{
	return mknod(path, mode | S_IFIFO, 0);
}

int mknodat(int fd, const char *path, mode_t mode, dev_t dev)
{
	return syscall(SYS_mknodat, fd, path, mode, dev & 0xffff);
}

int stat(const char *restrict path, struct stat *restrict buf)
{
#ifdef	SYS_stat
	return syscall(SYS_stat, path, buf);
#else
	return syscall(SYS_fstatat, AT_FDCWD, path, buf, 0);
#endif
}

mode_t umask(mode_t mode)
{
	return syscall(SYS_umask, mode);
}

int utimensat(int fd, const char *path, const struct timespec times[2], int flags)
{
	return syscall(SYS_utimensat, fd, path, times, flags);
}

int tcgetattr(int fd, struct termios *tio)
{
	if (ioctl(fd, TCGETS, tio))
		return -1;
	return 0;
}

int tcsetattr(int fd, int act, const struct termios *tio)
{
	if (act < 0 || act > 2) {
		errno = EINVAL;
		return -1;
	}
	return ioctl(fd, TCSETS+act, tio);
}

int nanosleep(const struct timespec *req, struct timespec *rem)
{
	return syscall(SYS_nanosleep, req, rem);
}

