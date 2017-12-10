#define HASH 10111

size_t hash(size_t inode)
{
	return (inode + 31) % HASH;
}

size_t *hashtab[HASH];

int populatetab(size_t inode)
{
	size_t *np;

	for ( np = hashtab[hash(inode)] ; np != NULL ; free(np), np = NULL)
		if ( inode == *np )
			 return 0;

	np = malloc(sizeof(size_t));
	*np = inode;
	hashtab[hash(inode)] = np ;
	return 1;
}

void destroytab()
{
	size_t i = 0;
	while ( i < HASH || hashtab[i] )
	{
		free(hashtab[i]);
		hashtab[i] = NULL;
		++i;
	}
}


