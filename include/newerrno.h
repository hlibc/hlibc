char *__errno_table[] = {
    "No such file or directory.", // ENOENT	2
    "Interrupted function.", // EINTR	4
    "Argument list too long.", // E2BIG	7
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

    "Operation canceled.", // ECANCELED		125

    "Connection aborted.", // ECONNABORTED	103
    "Connection refused.", // ECONNREFUSED	111
    "Connection reset.", // ECONNRESET		104



    "Reserved.", // EDQUOT	122



    "Host is unreachable.", // EHOSTUNREACH	113


    "Operation in progress.", // EINPROGRESS	115


    "I/O error.", // EIO	121
    "Socket is connected.", // EISCONN	104




    "Message too large.", // EMSGSIZE	90
    "Reserved.", // EMULTIHOP	72
    "Filename too long.", // ENAMETOOLONG
    "Network is down.", // ENETDOWN
    "Connection aborted by network.", // ENETRESET
    "Network unreachable.", // ENETUNREACH
    "Too many files open in system.", // ENFILE
    "No buffer space available.", // ENOBUFS
    "No message is available on the STREAM head read queue.", // ENODATA
    "No such device.", // ENODEV
    "Executable file format error.", // ENOEXEC
    "No locks available.", // ENOLCK
    "Reserved.", // ENOLINK
    "Not enough space.", // ENOMEM
    "No message of the desired type.", // ENOMSG
    "Protocol not available.", // ENOPROTOOPT
    "No space left on device.", // ENOSPC
    "No STREAM resources.", // ENOSR
    "Not a STREAM.", // ENOSTR
    "Functionality not supported.", // ENOSYS
    "The socket is not connected.", // ENOTCONN
    "Not a directory or a symbolic link to a directory.", // ENOTDIR
    "Directory not empty.", // ENOTEMPTY
    "State not recoverable.", // ENOTRECOVERABLE
    "Not a socket.", // ENOTSOCK
    "Not supported.", // ENOTSUP
    "Inappropriate I/O control operation.", // ENOTTY
    "No such device or address.", // ENXIO
    "Operation not supported on socket.", // EOPNOTSUPP
    "Value too large to be stored in data type.", // EOVERFLOW
    "Previous owner died.", // EOWNERDEAD
    "Operation not permitted.", // EPERM
    "Broken pipe.", // EPIPE
    "Protocol error.", // EPROTO
    "Protocol not supported.", // EPROTONOSUPPORT
    "Protocol wrong type for socket.", // EPROTOTYPE
    "Result too large.", // ERANGE
    "Read-only file system.", // EROFS
    "Invalid seek.", // ESPIPE
    "No such process.", // ESRCH
    "Reserved.", // ESTALE
    "Stream ioctl() timeout.", // ETIME
    "Connection timed out.", // ETIMEDOUT
    "Text file busy.", // ETXTBSY
    "Operation would block.", // EWOULDBLOCK
    "Cross-device link.",  // EXDEV
    "" };

