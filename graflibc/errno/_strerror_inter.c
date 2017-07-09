#include <gerrno.h>

/* x86 */
char *_messages[150] = {
	"Unknown error code\0",			/* (not used)	0	*/
	"Operation not permitted.\0",		/* EPERM	1	*/
	"No such file or directory.\0",		/* ENOENT	2	*/
	"No such process.\0",			/* ESRCH	3	*/
	"Interrupted function.\0",		/* EINTR	4	*/
	"\0",					/* ?		5	*/
	"No such device or address.\0",		/* ENXTA	6	*/
	"Argument list too long.\0",		/* E2BIG	7	*/
	"Executable file format error.\0",	/* ENOEXEC	8	*/
	"\0",					/* ?		9	*/
	"No child processes.\0",		/* ECHILD	10	*/
	"Resource unavailable, try again.\0", 	/* EAGAIN	11	*/
	"Not enough space.\0", 			/* ENOMEM	12	*/
	"Permission denied.\0",			/* EACCESS	13	*/
	"Bad address.\0",			/* EFAULT	14	*/
	"\0",					/* ?		15	*/
	"Device or resource busy.\0",		/* EBUSY	16	*/
	"File exists.\0",			/* EEXIST	17	*/
	"Cross-device link.\0",			/* EXDEV	18	*/
	"No such device.\0",			/* ENODEV	19	*/
	"Not a directory.\0",			/* ENOTDIR	20	*/
	"Is a directory.\0",			/* EISDIR	21	*/
	"Invalid argument.\0",			/* EINVAL	22	*/
	"Too many files open in system.\0",	/* ENFILE	23	*/
	"Too many open files.\0",		/* EMFILE	24	*/
	"Inappropriate I/O control operation.\0",/*ENOTTY	25	*/
	"Text file busy.\0",			/* ETXTBSY	26	*/
	"File too large.\0",			/* EFBIG	27	*/
	"No space left on device.\0",		/* ENOSPC	28	*/
	"Invalid seek.\0",			/* ESPIPE	29	*/
	"Read-only file system.\0",		/* EROFS	30	*/
	"Too many links.\0",			/* EMLINK	31	*/
	"Broken pipe.\0",			/* EPIPE	32	*/
	"Mathematics argument out of doma.\0",	/* EDOM		33	*/
	"Result too large.\0",			/* ERANGE	34	*/
	"\0"					/* ?		35	*/
	"Filename too long.\0",			/* ENAMETOOLONG	36	*/
	"No locks available.\0",		/* ENOLCK	37	*/
	"Function not supported.\0",		/* ENOSYS	38	*/
	"Directory not empty.\0",		/* ENOTEMPTY	39	*/
	"Too many levels of symbolic links.\0",	/* ELOOP	40	*/
	"\0",					/* ?		41	*/
	"No message of the desired type.\0",	/* ENOMSG	42	*/
	"Identifier removed.\0",		/* EIDRM	43	*/ 
	"\0",					/* ? 		44	*/
	"\0",					/* ? 		45	*/
	"\0",					/* ? 		46	*/
	"\0",					/* ?		47	*/
	"\0",					/* ? 		48	*/
	"\0",					/* ?		49	*/
	"\0",					/* ?		50	*/
	"\0",					/* ? 		51	*/
	"\0",					/* ?		52	*/
	"\0",					/* ? 		53	*/
	"\0",					/* ?		54	*/
	"\0",					/* ? 		55	*/
	"Not a STREAM.\0",			/* ENOSTR	60	*/
	"No msg is avail on STREAM head.\0",	/* ENODATA	61	*/
	"Stream ioctl() timeout.\0",		/* ETIME	62	*/
	"No STREAM resources.\0",		/* ENOSR	63	*/
	"\0",					/* ?		64	*/
	"\0",					/* ?		65	*/
	"\0",					/* ? 		66	*/
	"Reserved.\0",				/* ENOLINK	67	*/
	"\0",					/* ?		68	*/
	"\0",					/* ? 		69	*/
	"\0",					/* ?		70	*/
	"Protocol error.\0",			/* EPROTO	71	*/
	"Reserved.\0",				/* EMULTIHOP	72	*/
	"\0",					/* ?		73	*/
	"Bad message.\0",			/* EBADMSG	74	*/
	"Val too large to be stored in data type.\0",/*EOVERFLOW	75	*/
	"\0",					/* ?		76	*/
	"\0",					/* ?		77	*/
	"\0",					/* ? 		78	*/
	"\0",					/* ?		79	*/
	"\0",					/* ? 		80	*/
	"\0",					/* ?		81	*/
	"\0",					/* ?		82	*/
	"\0",					/* ? 		83	*/
	"Illegal byte sequence.\0",		/* EILSEQ	84	*/
	"\0",					/* ?		85	*/
	"\0",					/* ?		86	*/
	"\0",					/* ?		87	*/
	"Not a socket.\0",			/* ENOTSOCK	88	*/
	"Destination address required.\0",	/* EDESTADDRREQ	89	*/
	"Message too large.\0",			/* EMSGSIZE	90	*/
	"Protocol wrong type for socket.\0",	/* EPROTOTYPE	91	*/
	"Protocol not available.\0",		/* ENOPROTOOPT	92	*/
	"Protocol not supported.\0", 	/* EPROTONOSUPPORT	93	*/
	"\0",					/* ?		94	*/
	"Operation not supported on socket.\0",	/* EOPNOTSUPP	95	*/
	"Address family not supported.\0",	/* EAFNOSUPPORT	97	*/
	"Address in use.\0",			/* EADDRINUSE	98	*/
	"Address not available.\0",	/* EADDRNOTAVAIL	99	*/
	"Network is down.\0",			/* ENETDOWN	100	*/
	"Network unreachable.\0",		/* ENETUNREACH	101	*/
	"Connection aborted by network.\0",	/* ENETRESET	102	*/
	"Connection aborted.\0",		/* ECONNABORTED 103	*/
	"Connection reset.\0",			/* ECONNRESET	104	*/
	"No buffer space available.\0",		/* ENOBUFS	105	*/
	"Socket is connected.\0",		/* EISCONN	106	*/
	"The socket is not connected.\0",	/* ENOTCONN	107	*/
	"\0",					/* ?		108	*/
	"\0",					/* ?		109	*/
	"Connection timed out.\0",		/* ETIMEDOUT	110	*/
	"Connection refused.\0",		/* ECONNREFUSED	111	*/
	"\0",					/* ?		112	*/
	"Host is unreachable.\0",		/* EHOSTUNREACH	113	*/
	"Connection already in progress.\0",	/* EALREADY	114	*/
	"Operation in progress.\0",		/* EINPROGRESS	115	*/
	"Reserved.\0",				/* ESTALE	116	*/
	"\0",					/* ?		117	*/
	"\0",					/* ?		118	*/
	"\0",					/* ?		119	*/
	"\0",					/* ?		120	*/
	"\0",					/* ?		121	*/
	"Reserved.\0",				/* EDQUOT	122	*/ 
	"\0",					/* 			*/
	"\0",					/* 			*/
	"\0",					/* 			*/
	"\0",					/*			*/
	"\0",					/* 			*/ 
	"\0",					/* 			*/
	"\0",					/* 			*/
	"\0",					/* 			*/
	"\0",					/* 			*/
	"\0",					/* 			*/ 
	"\0",					/* 			*/
	"\0",					/* 			*/
	"\0",					/* 			*/
	"\0",					/* 			*/
	"\0",					/* 			*/
	
};
