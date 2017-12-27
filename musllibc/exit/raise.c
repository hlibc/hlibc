#include <signal.h>
#include <errno.h>
#include <stdint.h>
#include "syscall.h"

int raise(int sig)
{ 
	return sig;
}
