#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <grp.h>

int find_pattern(char *, size_t, size_t);

int main(int argc, char *argv[])
{
	if (argc > 1)
		find_pattern(argv[1], strlen(argv[1]), 0);
	else
		find_pattern(".", 1, 0);
	return 0;
}

int find_pattern(char *path, size_t tot, size_t last)
{ 
	DIR *dir;
	struct dirent *d;
	char *spath = NULL;
	size_t dlen = 0;
	
	if ((dir = opendir(path))) 
	{
		d = readdir(dir);
		while (d) 
		{ 
			dlen = strlen(d->d_name);
			
			last = (tot + dlen + 2); /* +2 = '/' + '\0' */
			spath = realloc(spath, last);
			if (!(spath))
				return -1;
			tot = sprintf(spath, "%s/%s", path, d->d_name);
	
			if ( strcmp( ".", d->d_name) && 
			   ( strcmp( "..", d->d_name)) )
			{
				printf("%s\n", spath);
			}

			if ( d->d_type == DT_DIR &&
			   ( strcmp( ".", d->d_name)) &&
			   ( strcmp( "..", d->d_name))) 
				find_pattern(spath, tot, last);
			d = readdir(dir);
		}
		
	}
	if (spath)
		free(spath);
	if(dir)
		closedir(dir);
	return 0;
}

