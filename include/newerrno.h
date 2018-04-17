char *__errno_table[] = {
    "Operation not permitted.", // EPERM	1
    "No such file or directory.", // ENOENT	2 
    "No such process.", // ESRCH	3
    "Interrupted function.", // EINTR	4
    "Argument list too long.", // E2BIG	7
    "Executable file format error.", // ENOEXEC	8
    "Bad file descriptor.", // EBADF	9
    "No child processes.", // ECHILD		10
    "Resource unavailable, try again.", // EAGAIN	11
    "Not enough space.", // ENOMEM	12
    "Permission denied.", // EACCES	13
    "Bad address.", // EFAULT	14
    "Device or resource busy.", // EBUSY	16
    "File exists.", // EEXIST	17
    "Cross-device link.",  // EXDEV	18
	
    "No such device.", // ENODEV	19
    "Not a directory or a symbolic link to a directory.", // ENOTDIR	20
    "Is a directory.", // EISDIR	21
    "Invalid argument.", // EINVAL	22
    "File descriptor value too large.", // EMFILE	23
    "Text file busy.", // ETXTBSY	26
    "File too large.", // EFBIG	27

    "No space left on device.", // ENOSPC	28 
    "Invalid seek.", // ESPIPE	29
    "Read-only file system.", // EROFS	30
    "Too many links.", // EMLINK	31
    "Broken pipe.", // EPIPE	32
    "Mathematics argument out of domain of function.", // EDOM	33
    "Result too large.", // ERANGE	34


    "Resource deadlock would occur.", // EDEADLK	35
    "Filename too long.", // ENAMETOOLONG	36
    "Too many levels of symbolic links.", // ELOOP	40
    "Identifier removed.", // EIDRM	43

    "Not a STREAM.", // ENOSTR	60
     "No message is available on the STREAM head read queue.", // ENODATA 61   
    "Stream ioctl() timeout.", // ETIME	62
    "No STREAM resources.", // ENOSR	63
    "Protocol error.", // EPROTO	71
    "Reserved.", // EMULTIHOP	72
    "Bad message.", // EBADMSG	74
    "Value too large to be stored in data type.", // EOVERFLOW	75

    "Illegal byte sequence.", // EILSEQ		84
    "Not a socket.", // ENOTSOCK	88
    "Destination address required.", // EDESTADDRREQ	89
    "Message too large.", // EMSGSIZE	90
    "Protocol wrong type for socket.", // EPROTOTYPE	91
    "Protocol not supported.", // EPROTONOSUPPORT	93
    "Operation not supported on socket.", // EOPNOTSUPP		95
    "Not supported.", // ENOTSUP	95
    "Address family not supported.", // EAFNOSUPPORT	97
    "Address in use.", // EADDRINUSE	98
    "Address not available.",  // EADDRNOTAVAIL	99 
    "Connection already in progress.", // EALREADY	114 

    "Network is down.", // ENETDOWN	100
    "Network unreachable.", // ENETUNREACH	101
    "Connection aborted by network.", // ENETRESET	102
    "Connection aborted.", // ECONNABORTED	103 
    "Connection reset.", // ECONNRESET		104 

    "No buffer space available.", // ENOBUFS	105
    "Socket is connected.", // EISCONN	106
    "The socket is not connected.", // ENOTCONN	107
    "Connection timed out.", // ETIMEDOUT	110
    "Connection refused.", // ECONNREFUSED	111
    "Host is unreachable.", // EHOSTUNREACH	113
    "Operation in progress.", // EINPROGRESS	115
    "I/O error.", // EIO	121
    "Reserved.", // EDQUOT	122
    "Operation canceled.", // ECANCELED		125 






    "Too many files open in system.", // ENFILE		23


    "Previous owner died.", // EOWNERDEAD	130
    "State not recoverable.", // ENOTRECOVERABLE	131

    "No locks available.", // ENOLCK	37
    "Reserved.", // ENOLINK	67
    
    "No message of the desired type.", // ENOMSG	42
    "Protocol not available.", // ENOPROTOOPT	92

    "Functionality not supported.", // ENOSYS	38


    "Directory not empty.", // ENOTEMPTY	39


    "Inappropriate I/O control operation.", // ENOTTY
    "No such device or address.", // ENXIO









    "Reserved.", // ESTALE	116



    "Operation would block.", // EWOULDBLOCK	EAGAIN

    "" };

