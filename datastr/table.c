#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
	Two list model:
	morecore adds to the master list

	free() adds to the free list (or free table)

	delnode deletes a node contained with the free list
	from the master list and the free list. 

*/
struct nlist { 
	struct nlist *next; 
	char *name; 
	char *defn; 
};

#define HASHSIZE 101
static struct nlist *hashtab[HASHSIZE]; 
unsigned hash(char *s)
{
	unsigned hashval;
	for (hashval = 0; *s != '\0'; s++)
		hashval = *s + 31 * hashval;
	return hashval % HASHSIZE;
}

struct nlist *lookup(char *s)
{
	struct nlist *np;
	for (np = hashtab[hash(s)]; np != NULL; np = np->next)
		if (strcmp(s, np->name) == 0)
			return np; 
	return NULL; 
}
struct nlist *lookup(char *);

struct nlist *install(char *name, char *defn)
{
	struct nlist *np;
	unsigned hashval;
	if ((np = lookup(name)) == NULL) {
		np = malloc(sizeof(*np));
		if (np == NULL || (np->name = strdup(name)) == NULL)
			return NULL;
		hashval = hash(name);
		np->next = hashtab[hashval];
		hashtab[hashval] = np;
	} else 
		free(np->defn); 
	if ((np->defn = strdup(defn)) == NULL)
		return NULL;
	return np;
}


int main(void)
{ 
	return 0;
}
