/* 	signal is a nop. this is not really acceptable but allows us to
	build GNU bc without modifying the software. A future impl of signal
	should go here!! 
*/
#include <signal.h>
typedef void (*sighandler_t)(int);
sighandler_t signal(int signum, sighandler_t handler)
{
	sighandler_t ret = { 0 };
	(void)signum;
	(void)handler;
	return ret;
}
