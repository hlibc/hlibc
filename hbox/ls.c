#include <stdio.h> 
#include <dirent.h>
#include <string.h>
#include <stdlib.h> 
#include <errno.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <grp.h>

/* 
	Copyright 2015-2018, C. Graff "ls"
*/ 

/* structs */
typedef struct {
	int plain;
	int alpha;
	int inode;
	int numer;
	int horiz;
	int hiddn;
	int recur;
	char *path;
	char **strings;
	char **output;
	char *home;
	size_t c; // count of *strings
	size_t refactor;// not yet used
} lstype;

/* functions */
int compare(const void*, const void*);
void list_dirs(char *, lstype);
void ls_error(char *, int);
void octtoperm(int);
void print_plain(size_t, lstype);
void print_strings(char **, size_t, size_t, int);
void prntstats(char *, lstype);
void shift_alpha(size_t, size_t, lstype);
int find_pattern(char *, size_t, size_t, lstype);

int main(int argc, char *argv[])
{ 
	int o;

	lstype g = { 0, 1, 0, 0, 0, 0 , 0, NULL, NULL, NULL, NULL, 0, 0};
	/* POSIX ls [-CFRacdilqrtu1][-H | -L  */
	while ((o = getopt (argc, argv, "lUinxhCaR")) != -1)
		switch (o) { 
			case 'l' : 
				g.plain = 1; 
				break;
			case 'U' : 
				g.alpha = 0; 
				break;
			case 'i' : 
				g.inode = 1; 
				break;
			case 'n' : 
				g.numer = 1; 
				break;
			case 'x' : 
				g.horiz = 1; 
				break;
			case 'C' : 
				g.plain = 0; 
				break;
			case 'a' : 
				g.hiddn = 1; 
				break;
			case 'R':
				g.recur = 1;
				break;
			case 'h' : 
				ls_error("Usage:   ls -lUinxhCaR [PATH(S)]\n", 0); 
				break;
			case '?' : 
				return 0; 
			default: 
				break;
		}

	argv += optind;
	argc -= optind;

	/* disable vertical alphabetization with -R (it's broken) */
	if (g.recur == 1)
		g.horiz = 1;
	
	g.home = getcwd(g.home, 100);
	

	if (argc == 0) 
	{
		g.path = ".";
		if (g.recur == 0 )
			list_dirs(".", g);
		if (g.recur == 1 )
			find_pattern(".", 1, 0, g);
	}
	while (argc > 0 && *argv)
	{ 
		g.path = *argv;
		if (g.recur == 0)
			list_dirs(*argv, g);
		if (g.recur == 1)
			find_pattern(*argv, strlen(*argv), 0, g);
		++argv;
	}

	free(g.home);
	return 0;
} 


void list_dirs(char *argvv, lstype g) 
{ 
	struct winsize w;
	DIR *a;
	struct dirent *b; 
	size_t max = 1;
	size_t len = 1; 
	size_t factor = 0;
	size_t refactor = 0;
	size_t c = 0;
	static size_t outs = 10024;

	if (g.output == NULL)
	{
		if (!(g.output = malloc(sizeof(char*) * outs)))
			ls_error("no mem", 1);
		if (!(g.strings = malloc(sizeof(char*) * outs)))
			ls_error("no mem", 1);
	}

	/* Discover and count directory entries */
	if ((a = opendir(argvv)))
	{
		while ((b = readdir(a)))
		{
			if ((g.hiddn != 1 && b->d_name[0] == '.' ))
				continue;
			len = strlen(b->d_name);
			
			if (c >= outs)
			{
				outs += outs;
				if (!(g.output = realloc(g.output, sizeof(char*) * outs)))
					ls_error("no mem", 1);
				if (!(g.strings = realloc(g.strings, sizeof(char*) * outs)))
					ls_error("no mem", 1);
			}
		
			if (!(g.strings[c] = malloc(len + 1)))
				ls_error("no mem", 1);
			memcpy(g.strings[c], b->d_name, len + 1);
		       	if (len > max)
			       	max = len;
			++c;
		}
	}
	
	else /* it's not a directory, so just lstat it */
	{
		prntstats(argvv, g);
		return;
	}

	if (max == 1)
		goto end;

	/* Obtain terminal information */ 
	ioctl(0, TIOCGWINSZ, &w);
	factor = w.ws_col / max;
	refactor = (w.ws_col - factor) / max;

	/* Alphabetize discovered entries */
	if (g.alpha == 1) 
		qsort(g.strings, c, sizeof (char*), compare);

	if (g.plain == 1) 
		print_plain(c, g); 
	
	if (g.plain == 0)
	{
		if (g.horiz == 1)
		{
			print_strings(g.strings, c - refactor -1, refactor, max);
			printf("\n"); 
		}
		else {
			shift_alpha(c, refactor, g); 
			print_strings(g.output, c, refactor, max); 
		} 
	} 
	end:
	
	if (a)
		closedir(a);
}

void shift_alpha(size_t c, size_t refactor, lstype g)
{
	/* Format columnar lists to alphabetize vertically */
	size_t cnt, sft, sftc, vary = 0;
	cnt = sft = sftc = vary = 0;
	while (cnt < c)
	{
		g.output[sft] = g.strings[cnt];
		sft = (sft + refactor);
		++sftc;
		if (sftc == (c / refactor) + 1)
		{
			++vary;
			sft = vary;
			sftc = 0;
		}
		++cnt;
	} 
}

void print_strings(char **s, size_t c, size_t refactor, int max)
{
	size_t i, z;
	for (i = 0, z = 0; i <= c + refactor; i++)
	{
		if ((s[i]))
		{
			printf("%-*s ", max, s[i]);
			free(s[i]);
		}
		if (++z % refactor == 0)
			printf("\n");
	} 
	free(s);
	fflush(stdout);
}

void print_plain(size_t c, lstype g)
{ 
	size_t i = 0;
	for (; i < c ; ++i) 
		prntstats(g.strings[i] ,g);
}

void ls_error(char *message, int i)
{ 
	if ( i > 0 )
		perror("Error: ");
	fprintf(stderr, "%s", message);
	exit (i);
}

void octtoperm(int octal)
{
	switch (octal & S_IFMT)
	{
		case S_IFBLK:
			printf("b");
			break;
		case S_IFCHR:
			printf("c");
			break;
		case S_IFDIR:
			printf("d");
			break;
		case S_IFIFO:
			printf("p");
			break;
		case S_IFLNK:
			printf("l");
			break;
		case S_IFREG:
			printf("-");
			break;
		case S_IFSOCK:
			printf("S");
			break;
		default:
			printf("?");
			break;

	}

	if (octal & S_IRUSR)
		printf("r");
	else
		printf("-");
	if (octal & S_IWUSR)
		printf("w");
	else
		printf("-");
	if (octal & S_IXUSR)
		printf("x");
	else
		printf("-");
	if (octal & S_IRGRP)
		printf("r");
	else
		printf("-");
	if (octal & S_IWGRP)
		printf("w");
	else
		printf("-");
	if (octal & S_IXGRP)
		printf("x");
	else
		printf("-");
	if (octal & S_IROTH)
		printf("r");
	else
		printf("-");
	if (octal & S_IWOTH)
		printf("w");
	else
		printf("-");

	if (octal & S_ISVTX && octal & S_IXOTH)
		printf("t");
	else if (octal & S_ISVTX)
		printf("T");
	else if (octal & S_IXOTH)
		printf("x");
	else
		printf("-");
	printf(" ");
}

int compare(const void *a, const void *b)
{
	return strcmp(*(char **)a, *(char **)b);
}

void prntstats(char *file, lstype g)
{
	struct stat sb = { 0 };
	if (lstat(file, &sb) != 0)
		return;
	octtoperm(sb.st_mode);
	printf(" ");
	if (g.inode == 1)
		printf("%-8ld ", sb.st_ino);
	printf("%-3ld ", sb.st_nlink);
	printf("%ld %ld ", (long int)sb.st_uid, (long int)sb.st_gid);
	printf("%8lld ", (long long int)sb.st_size);
	printf("%s\n", file); 
} 

int find_pattern(char *path, size_t tot, size_t last, lstype g)
{ 
	DIR *dir;
	struct dirent *d;
	char *spath = malloc(1);
	size_t dlen = 0; 
	
	printf("%s:\n", path);
	list_dirs(path, g);
	printf("\n");
				
	if (!(spath))
		return -1;
	
	if ((dir = opendir(path))) 
	{
		d = readdir(dir);

		while (d) 
		{
			dlen = strlen(d->d_name);
			last = (tot + dlen + 2); 
			spath = realloc(spath, last);
			if (!(spath))
				return -1;

			tot = sprintf(spath, "%s/%s", path, d->d_name); 

			if (d->d_type == DT_DIR &&
			   (strcmp( ".", d->d_name)) &&
			   (strcmp( "..", d->d_name))) {
				find_pattern(spath, tot, last, g);
			} 
			d = readdir(dir); 
		} 
	}

	free(spath);
	if (dir)
		closedir(dir);
	return 0;
}

