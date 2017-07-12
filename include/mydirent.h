#define NAME_MAX 14
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/types.h>
//#include <sys/stat.h>
#include <fcntl.h>

/* longest filename component; */
/* system-dependent */
typedef struct { /* portable directory entry */
        long ino;  /* inode number */
        char name[NAME_MAX+1]; /* name + '\0' terminator */

} MYDirent;
typedef struct {
        int fd;
        MYDirent d;
} MYDIR;
/* minimal DIR: no buffering, etc. */
/* file descriptor for the directory */
/* the directory entry */
MYDIR *myopendir(char *dirname);
MYDirent *myreaddir(MYDIR *dfd);
void myclosedir(MYDIR *dfd);

char *name;
//struct stat stbuf;
//int stat(char *, struct stat *);
//stat(name, &stbuf)

struct mystat
{
        dev_t st_dev;
        ino_t st_ino;
        short st_mode;
        short st_nlink;
        short st_uid;
        short st_gid;
        dev_t st_rdev;
        off_t st_size;
        //time_t st_atime;
        //time_t st_mtime;
        //time_t st_ctime;
};
#define S_IFMT 0160000
#define S_IFDIR 0040000
#define S_IFCHR 0020000
#define S_IFBLK 0060000
#define S_IFREG 0010000


#ifndef DIRSIZ
#define DIRSIZ 14
#endif
struct mydirent { /* directory entry */
        ino_t d_ino;  /* inode number */
        char d_name[DIRSIZ]; /* long name does not have '\0' */
	int d_type;
};
MYDIR *myopendir(char *);
void myclosedir(MYDIR *);
MYDirent *myreaddir(MYDIR *);

