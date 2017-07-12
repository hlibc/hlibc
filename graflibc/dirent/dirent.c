#include <mydirent.h>

//int fstat(int fd, struct stat *);
/* opendir: open a directory for readdir calls */
MYDIR *myopendir(char *dirname)
{
	int fd;
	struct mystat stbuf;
	MYDIR *dp;
	if ((fd = open(dirname, O_RDONLY, 0)) == -1
	|| fstat(fd, &stbuf) == -1
	|| (stbuf.st_mode & S_IFMT) != S_IFDIR
	|| (dp = malloc(sizeof(MYDIR))) == NULL)
		return NULL;
	dp->fd = fd;
	return dp;
}
/* closedir: close directory opened by opendir */
void myclosedir(MYDIR *dp)
{
	if (dp)
	{
		close(dp->fd);
		free(dp);
	}
}
//#include <sys/dir.h>
/* local directory structure */
/* readdir: read directory entries in sequence */
MYDirent *myreaddir(MYDIR *dp)
{

	struct mydirent dirbuf;
	static MYDirent d;
	/* local directory structure */
	/* return: portable structure */
	while (read(dp->fd, (char *) &dirbuf, sizeof(dirbuf)) == sizeof(dirbuf)) 
	{
		if (dirbuf.d_ino == 0) /* slot not in use */
			continue;
		d.ino = dirbuf.d_ino;
		strncpy(d.name, dirbuf.d_name, DIRSIZ);
		d.name[DIRSIZ] = '\0'; /* ensure termination */
		return &d;
	}
	return NULL;
}
