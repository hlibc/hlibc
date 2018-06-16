#include "../internal/internal.h"

FILE _IO_stream[FOPEN_MAX] = {	{ 0, _READ, NULL, NULL, NULL, 0, 0, { 0 }, 0 },
			{ 1, _WRITE | _LNBUF, NULL, NULL, NULL, 0, 0, { 0 }, 0 },
			{ 2, _WRITE | _UNBUF, NULL, NULL, NULL, 0, 0, { 0 }, 0 }};

FILE *stdin = (&_IO_stream[0]);
FILE *stdout = (&_IO_stream[1]);
FILE *stderr = (&_IO_stream[2]);
