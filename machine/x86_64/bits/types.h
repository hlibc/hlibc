#ifndef __HAS_TYPES__
#define __HAS_TYPES__

typedef unsigned long size_t;

typedef long ssize_t;

typedef long ptrdiff_t;

typedef __builtin_va_list va_list;

typedef int wchar_t;

typedef int wint_t;

typedef int wctrans_t;

typedef int wctype_t;

typedef signed char int8_t;

typedef short       int16_t;

typedef int         int32_t;

typedef long        int64_t;

typedef unsigned char      uint8_t;

typedef unsigned short     uint16_t;

typedef unsigned int       uint32_t;

typedef unsigned long      uint64_t;

typedef unsigned short     __uint16_t;

typedef unsigned int       __uint32_t;

typedef unsigned long      __uint64_t;

typedef int8_t    int_fast8_t;

typedef int       int_fast16_t;

typedef int       int_fast32_t;

typedef int64_t   int_fast64_t;

typedef unsigned char      uint_fast8_t;

typedef unsigned int       uint_fast16_t;

typedef unsigned int       uint_fast32_t;

typedef uint64_t           uint_fast64_t;

typedef long          intptr_t;

typedef unsigned long uintptr_t;

typedef double float_t;

typedef double double_t;

typedef long time_t;

typedef long suseconds_t;

struct timeval { time_t tv_sec; long tv_usec; };

struct timespec { time_t tv_sec; long tv_nsec; };

typedef int pid_t;

typedef int id_t;

typedef unsigned int uid_t;

typedef unsigned int gid_t;

typedef int key_t;

typedef long off_t;

typedef unsigned int mode_t;

typedef unsigned long nlink_t;

typedef unsigned long long ino_t;

typedef unsigned long dev_t;

typedef long blksize_t;

typedef long long blkcnt_t;

typedef unsigned long long fsblkcnt_t;

typedef unsigned long long fsfilcnt_t;

typedef void * timer_t;

typedef int clockid_t;

typedef long clock_t;

typedef struct { unsigned long __bits[128/sizeof(long)]; } sigset_t;

typedef struct __siginfo siginfo_t;

typedef unsigned int socklen_t;

typedef unsigned short sa_family_t;

typedef unsigned short in_port_t;

typedef unsigned int in_addr_t;

struct in_addr { in_addr_t s_addr; };

typedef int nl_item;

typedef struct __locale * locale_t;

struct iovec { void *iov_base; size_t iov_len; };

#endif
