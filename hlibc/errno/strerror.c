#include <gerrno.h>
#include <gstring.h>

char *gstrerror(int errnum)
{
	if (errnum > 0 && errnum < 128)
		return _messages[errnum];
	return _messages[0];
}
