#ifndef	_SYS_WAIT_H
#define	_SYS_WAIT_H
#ifdef __cplusplus
extern "C" {
#endif

#include <signal.h>

#define __NEED_pid_t
#define __NEED_id_t
#define __NEED_siginfo_t
#include <bits/types.h>

typedef int idtype_t;

pid_t wait (int *);
int waitid (idtype_t, id_t, siginfo_t *, int);
pid_t waitpid (pid_t, int *, int );

#ifdef _GNU_SOURCE
#include <sys/resource.h>
pid_t wait3 (int *, int, struct rusage *);
pid_t wait4 (pid_t, int *, int, struct rusage *);
#endif

#define WNOHANG    1
#define WUNTRACED  2

#define WSTOPPED   2
#define WEXITED    4
#define WCONTINUED 8
#define WNOWAIT    0x1000000

#define P_ALL  0
#define P_PID  1
#define P_PGID 2

#ifndef WEXITSTATUS
#define WEXITSTATUS(s) (((s) & 0xff00) >> 8)
#define WTERMSIG(s) ((s) & 0x7f)
#define WSTOPSIG(s) WEXITSTATUS(s)
#define WCOREDUMP(s) ((s) & 0x80)
#define WIFEXITED(s) (!WTERMSIG(s))
#define WIFSTOPPED(s) (((s) & 0xff) == 0x7f)
#define WIFSIGNALED(s) (((signed char) (((s) & 0x7f) + 1) >> 1) > 0)
#define WIFCONTINUED(s) ((s) == 0xffff)
#endif

#ifdef __cplusplus
}
#endif
#endif
