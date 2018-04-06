#include <string.h>
#include <inttypes.h>
#include <elf.h>
#include "pthread_impl.h"
#include "atomic.h"

void __stack_chk_fail(void)
{
	//a_crash();
}
