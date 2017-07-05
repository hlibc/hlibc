#include <gstdio.h>

GFILE _IO_stream[FOPEN_MAX] = {
        { 0, _READ, NULL, NULL, NULL, 0, 0},
        { 1, _WRITE | _LNBUF, NULL, NULL, NULL, 0, 0},
        { 2, _WRITE | _UNBUF, NULL, NULL, NULL, 0, 0}
};

