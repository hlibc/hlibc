/*
	kill.c
	Copyright (c), zhiayang
*/

#include <signal.h>
#include <sys/syscall.h>

int kill(pid_t pid, int sig)
{
	syscall(SYS_kill, pid, sig);
}

int killpg(int pgrp, int sig)
{
	/* kill() says that if pid < 0, then -pid is the proc group to kill */
	return kill(-pgrp, sig);
}
