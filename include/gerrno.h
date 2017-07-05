


/* These error macros were obtained from POSIX and then poulated by scraping an
 * an x86_64 host. */

#define EPERM 		1  	/* "Operation not permitted."		*/
#define ENOENT 		2  	/* "No such file or directory."		*/
#define ESRCH 		3  	/* "No such process."			*/
#define EINTR 		4  	/* "Interrupted function."		*/

#define ENXIO 		6  	/* "No such device or address."		*/
#define E2BIG 		7  	/* "Argument list too long."		*/
#define ENOEXEC 	8  	/* "Executable file format error."	*/

#define ECHILD 		10  	/* "No child processes."		*/
#define EAGAIN 		11  	/* "Resource unavailable, try again."	*/
#define ENOMEM 		12  	/* "Not enough space."			*/
#define EACCES 		13  	/* "Permission denied."			*/
#define EFAULT 		14  	/* "Bad address." 			*/

#define EBUSY 		16  	/* "Device or resource busy." 		*/
#define EEXIST 		17  	/* "File exists." 			*/
#define EXDEV 		18  	/* "Cross-device link."			*/
#define ENODEV 		19  	/* "No such device."			*/
#define ENOTDIR 	20  	/* "Not a directory."			*/
#define EISDIR 		21  	/* "Is a directory."			*/
#define EINVAL 		22  	/* "Invalid argument."			*/
#define ENFILE 		23  	/* "Too many files open in system." 	*/
#define EMFILE 		24  	/* "Too many open files."		*/
#define ENOTTY 		25  	/* "Inappropriate I/O control operation." */
#define ETXTBSY 	26  	/* "Text file busy."			*/
#define EFBIG 		27  	/* "File too large." 			*/
#define ENOSPC 		28  	/* "No space left on device."		*/
#define ESPIPE 		29  	/* "Invalid seek."			*/
#define EROFS 		30  	/* "Read-only file system."		*/
#define EMLINK 		31  	/* "Too many links."			*/
#define EPIPE 		32  	/* "Broken pipe."				*/
#define EDOM 		33  	/* "Mathematics argument out of doma ." */
#define ERANGE 		34  	/* "Result too large."			*/

#define ENAMETOOLONG 	36  	/* "Filename too long."			*/
#define ENOLCK 		37  	/* "No locks available."			*/
#define ENOSYS 		38  	/* "Function not supported."		*/
#define ENOTEMPTY 	39  	/* "Directory not empty."			*/
#define ELOOP 		40  	/* "Too many levels of symbolic links." 	*/

#define ENOMSG 		42  	/* "No message of the desired type." 	*/
#define EIDRM 		43  	/* "Identifier removed." 			*/ 


#define ENOSTR 		60  	/* "Not a STREAM."			*/ 
#define ENODATA 	61  	/* "No msg is avail on STREAM head."	*/ 
#define ETIME 		62  	/* "Stream ioctl() timeout."		*/
#define ENOSR 		63  	/* "No STREAM resources."			*/ 


#define ENOLINK 	67  	/* "Reserved."				*/ 


#define EPROTO 		71  	/* "Protocol error."			*/
#define EMULTIHOP 	72  	/* "Reserved."				*/

#define EBADMSG 	74  	/* "Bad message." 			*/
#define EOVERFLOW 	75  	/* "Val too large to be stored in data type." */


#define EILSEQ 		84  	/* "Illegal byte sequence."		*/


#define ENOTSOCK 	88  	/* "Not a socket."			*/
#define EDESTADDRREQ 	89  	/* "Destination address required." 	*/
#define EMSGSIZE 	90  	/* "Message too large."			*/
#define EPROTOTYPE 	91  	/* "Protocol wrong type for socket." 	*/
#define ENOPROTOOPT 	92  	/* "Protocol not available."		*/
#define EPROTONOSUPPORT 93  	/* "Protocol not supported."		*/

#define EOPNOTSUPP 	95  	/* "Operation not supported on socket." 	*/

#define EAFNOSUPPORT 	97  	/* "Address family not supported." 	*/
#define EADDRINUSE 	98  	/* "Address in use." 			*/
#define EADDRNOTAVAIL 	99  	/* "Address not available." 		*/
#define ENETDOWN 	100  	/* "Network is down."			*/
#define ENETUNREACH 	101  	/* "Network unreachable."			*/
#define ENETRESET 	102  	/* "Connection aborted by network." 	*/
#define ECONNABORTED 	103  	/* "Connection aborted." 			*/
#define ECONNRESET 	104  	/* "Connection reset." 			*/
#define ENOBUFS 	105  	/* "No buffer space available."		*/ 
#define EISCONN 	106  	/* "Socket is connected."			*/ 
#define ENOTCONN 	107  	/* "The socket is not connected."		*/


#define ETIMEDOUT 	110  	/* "Connection timed out."		*/
#define ECONNREFUSED 	111  	/* "Connection refused." 			*/
#define EHOSTUNREACH 	113  	/* "Host is unreachable." 		*/
#define EALREADY 	114  	/* "Connection already in progress." 	*/
#define EINPROGRESS 	115  	/* "Operation in progress."		*/
#define ESTALE 		116  	/* "Reserved."				*/


#define EDQUOT 		122  	/* "Reserved." 				*/ 

#define EWOULDBLOCK EAGAIN 	/* "Operation would block (EAGAIN) ..." */
/* missing */
/* #define EBADF *//* Bad file descriptor.				*/ 
/* #define ECANCELED  */  	/* Operation canceled.			*/ 
/* #define EDEADLK *//* Resource deadlock would occur.			*/ 
/* #define EIO *//* I/O error.						*/ 
/* #define ENOTSUP  */  	/* Not supported.			*/ 


