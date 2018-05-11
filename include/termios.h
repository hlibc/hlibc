#ifndef	_TERMIOS_H
#define	_TERMIOS_H

#ifdef __cplusplus
extern "C" {
#endif

#define __NEED_pid_t

#include <bits/alltypes.h>

typedef unsigned char cc_t;
typedef unsigned int speed_t;
typedef unsigned int tcflag_t;

#define NCCS 32

#include <bits/termios.h>
int tcgetattr (int, struct termios *);
int tcsetattr (int, int, const struct termios *);

#ifdef _GNU_SOURCE
void cfmakeraw(struct termios *);
int cfsetspeed(struct termios *, speed_t);
#endif

#ifdef __cplusplus
}
#endif

#endif
