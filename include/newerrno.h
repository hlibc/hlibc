char *__errno_table[] = {
    "No such file or directory.", // ENOENT	2 
    "Interrupted function.", // EINTR	4
    "Argument list too long.", // E2BIG	7
    "Executable file format error.", // ENOEXEC	8
    "Bad file descriptor.", // EBADF	9
    "No child processes.", // ECHILD		10
    "Resource unavailable, try again.", // EAGAIN	11
    "Permission denied.", // EACCES	13
    "Bad address.", // EFAULT	14
    "Device or resource busy.", // EBUSY	16
    "File exists.", // EEXIST	17
    "Is a directory.", // EISDIR	21
    "Invalid argument.", // EINVAL	22
    "File descriptor value too large.", // EMFILE	23
    "File too large.", // EFBIG	27
    "Too many links.", // EMLINK	31
    "Mathematics argument out of domain of function.", // EDOM	33
    "Resource deadlock would occur.", // EDEADLK	35
    "Too many levels of symbolic links.", // ELOOP	40
    "Identifier removed.", // EIDRM	43
    "Bad message.", // EBADMSG	74
    "Illegal byte sequence.", // EILSEQ		84
    "Destination address required.", // EDESTADDRREQ	89
    "Address family not supported.", // EAFNOSUPPORT	97
    "Address in use.", // EADDRINUSE	98
    "Address not available.",  // EADDRNOTAVAIL	99 
    "Connection already in progress.", // EALREADY	114 
    "Connection aborted.", // ECONNABORTED	103 
    "Connection reset.", // ECONNRESET		104 
    "Connection refused.", // ECONNREFUSED	111
    "Host is unreachable.", // EHOSTUNREACH	113
    "Operation in progress.", // EINPROGRESS	115
    "Reserved.", // EDQUOT	122
    "Operation canceled.", // ECANCELED		125 
    "I/O error.", // EIO	121
    "Socket is connected.", // EISCONN	104 
    "Message too large.", // EMSGSIZE	90
    "Reserved.", // EMULTIHOP	72
    "Filename too long.", // ENAMETOOLONG	36
    "Network is down.", // ENETDOWN	100
    "Connection aborted by network.", // ENETRESET	102
    "Network unreachable.", // ENETUNREACH	101
    "Too many files open in system.", // ENFILE		23
    "No buffer space available.", // ENOBUFS	105
    "No message is available on the STREAM head read queue.", // ENODATA 61
    "No such device.", // ENODEV	19

    "No locks available.", // ENOLCK	37
    "Reserved.", // ENOLINK	67
    "Not enough space.", // ENOMEM	12
    "No message of the desired type.", // ENOMSG	42
    "Protocol not available.", // ENOPROTOOPT	92
    "No space left on device.", // ENOSPC	28
    "No STREAM resources.", // ENOSR	63
    "Not a STREAM.", // ENOSTR	60
    "Functionality not supported.", // ENOSYS	38
    "The socket is not connected.", // ENOTCONN	107
    "Not a directory or a symbolic link to a directory.", // ENOTDIR	20
    "Directory not empty.", // ENOTEMPTY	39
    "State not recoverable.", // ENOTRECOVERABLE	131
    "Not a socket.", // ENOTSOCK	88
    "Not supported.", // ENOTSUP	95
    "Inappropriate I/O control operation.", // ENOTTY
    "No such device or address.", // ENXIO
    "Operation not supported on socket.", // EOPNOTSUPP		95
    "Value too large to be stored in data type.", // EOVERFLOW	75
    "Previous owner died.", // EOWNERDEAD	130
    "Operation not permitted.", // EPERM	1
    "Broken pipe.", // EPIPE	32
    "Protocol error.", // EPROTO	71
    "Protocol not supported.", // EPROTONOSUPPORT	93
    "Protocol wrong type for socket.", // EPROTOTYPE	91
    "Result too large.", // ERANGE	34
    "Read-only file system.", // EROFS	30
    "Invalid seek.", // ESPIPE	29
    "No such process.", // ESRCH	3
    "Reserved.", // ESTALE	116
    "Stream ioctl() timeout.", // ETIME	62
    "Connection timed out.", // ETIMEDOUT	110
    "Text file busy.", // ETXTBSY	26
    "Operation would block.", // EWOULDBLOCK	EAGAIN
    "Cross-device link.",  // EXDEV	18
    "" };

