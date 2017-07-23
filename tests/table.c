#include <string.h>
#include <stdlib.h>
#include <stdio.h>

size_t hbuckets = 1000;

size_t primes[9] = {
        31,
        62,
        237,
        251,
        65521,
        131071,
        262139,
        524287,
        1327144009
};

struct nlist {     		/* table entry: */
        struct nlist *next;   	/* next entry in chain */
        char *name;             /* defined name */
        char *defn;             /* replacement text */
};

//static struct nlist *hashtab[hbuckets]; /* pointer table */
static struct nlist **hashtab; /* dynamically allocated pointer table */

struct nlist *lookup(char *);
struct nlist *install(char *, char *);
unsigned hash(char *);
void initialize_table(size_t);
void destroy_table(void);

void initialize_table(size_t i)
{ 
	hashtab = calloc(1000, sizeof(struct nlist) * i); 
}

void destroy_table(void)
{ 
	free(hashtab);
}

unsigned hash(char *s)
{
        /* hash: form hash value for string s */
        unsigned hashval;
        for (hashval = 0; *s != '\0'; s++)
                hashval = *s + primes[0] * hashval;
        return hashval % hbuckets;
}

struct nlist *lookup(char *s)
{
        struct nlist *np;
        for (np = hashtab[hash(s)]; np != NULL; np = np->next)
                if (strcmp(s, np->name) == 0)
                        return np;
        return NULL;
}

struct nlist *install(char *name, char *defn)
{
        /* install: put (name, defn) in hashtab */
        struct nlist *np;
        unsigned hashval;
        if ((np = lookup(name)) == NULL) { /* not found */
                np = malloc(sizeof(*np));
                if (np == NULL || (np->name = strdup(name)) == NULL)
                        return NULL;
                hashval = hash(name);
                np->next = hashtab[hashval];
                hashtab[hashval] = np;
        } else     /* already there */
                free(np->defn);   /*free previous defn */
        if ((np->defn = strdup(defn)) == NULL)
                return NULL;
        return np;
}

void destroytab()
{
        struct nlist *np;
	struct nlist *last[hbuckets];
	size_t i = 0;
	size_t j = 0;
        while ( i < hbuckets )
        {
		if (hashtab[i])
		{
			for (j=0, np = hashtab[i]; np != NULL; np = np->next, ++j)
			{ 
				free(np->name);
				free(np->defn);
				last[j] = np; 
			} 
			while ( j-- )
				free(last[j]);
		}
                ++i;
        }
}


/* start of driver code */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h> 
#include <limits.h> 

struct hold {
	off_t level[100]; 
	int depth; 
	off_t block;
	size_t lastd; 
} hold = { {0}, 0, 1024, 0};  // this should be 512 for posix compat


int durecurse(char *, size_t, int *);


int main (int argc, char *argv[]) 
{ 

	int i, opt[7] = { 0, 0, 0, 0, 0, 0, 0}; /* -aHkLsXl */
	struct stat sb;

	while ((i = getopt (argc, argv, "aHkLsxl")) != -1) 
		switch (i) {
			case 'a': 
				opt[0] = 1; 
				break; 
			case 'H': 
				opt[1] = 1; 
				break; // -H follow sumbolic links  .. not done
			case 'k': 
				opt[2] = 1;
				hold.block = 1024;
				break; 
			case 'L': 
				opt[3] = 1; 
				break;
			case 's': 
				opt[4] = 1; 
				break; 
                        case 'x': 
				opt[5] = 1; 
				break; 
			case 'l': 
				opt[6] = 1; 
				break; 
			default: 
				break;
		} 
        argv += optind;
        argc -= optind; 
	
	initialize_table(1000);
	while(*argv) 
	{
		lstat(*argv, &sb); 
		hold.lastd = sb.st_dev;
		hold.level[1] = 0;

		if ( durecurse(*argv, strlen(*argv), opt) ) 
		{
			printf("%zu\t%s\n", hold.level[1] + 4, *argv); 
			destroytab(); 
		}
		++argv; 
	} 
	destroy_table();
	return 0;
} 


int durecurse(char *path, size_t len, int *opt)
{
	int c;
	size_t i = 0;
        DIR *dir;
        struct dirent *dentry; 
        char *spath = malloc(1);
	struct stat sb;
	size_t dlen = 0;
	
	if (!(spath))
		return -1;
       
	++hold.depth;

        if ( ( dir = opendir(path) ) )
        { 
                dentry = readdir(dir);
                while ( dentry ) 
                {
			dlen = strlen(dentry->d_name);
			spath = realloc(spath, dlen + len + 2);
			if (!(spath))
				return -1; 
                        len = sprintf(spath, "%s/%s", path, dentry->d_name); 
                        if ( strcmp( ".", dentry->d_name) &&
                            strcmp( "..", dentry->d_name) )
                        { 
				
				if (opt[5] == 1 ) // -x
					lstat(spath, &sb); 
			
				if (opt[5] == 0 || hold.lastd != sb.st_dev )
                                	if ( dentry->d_type == DT_DIR )
						durecurse(spath, len, opt); 
		
				if ( opt[3] == 1 ) // -L 
					stat(spath, &sb); 
				else
					lstat(spath, &sb); 
			
				char temp[4096] = { 0 };
				sprintf(temp, "%zu", (size_t)sb.st_ino);
				if (install(temp, temp))
				{ 
					i = ( sb.st_blocks * 512 ) / hold.block; 

					if (opt[0] == 1 && dentry->d_type == DT_REG) // -a 
						printf("%zu\t%s\n", i, spath ); 
					c = 1;
					while ( c <= 35 ) 
						hold.level[c++] += i;
                           	}
				if ( dentry->d_type == DT_DIR )	
				{ 	
					if ( opt[4] == 0 ) // -s 
					{
                               	         	printf("%zu", hold.level[hold.depth]);
						printf("\t%s\n", spath );
					}
                               	        hold.level[hold.depth] = 0; 
					--hold.depth; 
				} 
				c = hold.depth;
				while ( c <= 35 ) 
                               		hold.level[++c] = 0; 
			} 
                        dentry = readdir(dir); 
                } 
                closedir(dir);
		free(spath); 
        }
        else
	{ 
		lstat(path, &sb);
		printf("%zu\t%s\n", (size_t)(sb.st_blocks * 512 ) /hold.block, path); 
		return 0;
	} 
	
        return 1; 
}


