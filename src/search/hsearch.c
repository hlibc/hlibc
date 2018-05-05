/**
 * hsearch.c - hcreate/hsearch/hdestroy and their reentrant counterparts
 *
 * Author: Bao Hexing <HexingB@qq.com>
 * Created: 25 December 2017
 *
 * Copyright © 2017, Bao Hexing. All Rights Reserved.
 */

#define _GNU_SOURCE
#include <search.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

struct ENTRY_LIST
{
	ENTRY entry;
	struct ENTRY_LIST * next;
};

static size_t create_buckets(struct ENTRY_LIST *** buckets, size_t bucket_size)
{
	*buckets = calloc(sizeof(struct ENTRY_LIST*), bucket_size);
	return bucket_size;
}

static long int hash_key(const char * key, size_t bucket_size)
{
	long int hash;
	for (hash = 5381; *key != '\0'; ++key) {
		hash += ((hash << 5) + hash) + *key;
	}
	return hash % bucket_size;
}

int hcreate_r(size_t nel, struct hsearch_data *htab)
{
	htab->item_size = 0;
	htab->bucket_size = create_buckets(&htab->buckets, nel);
	if (htab->buckets == NULL) {
		errno = ENOMEM;
		return 0;
	}
	return 1;
}

int hsearch_r(ENTRY item, ACTION action, ENTRY **retval,
			  struct hsearch_data *htab)
{
	long int hash = hash_key(item.key, htab->bucket_size);
	struct ENTRY_LIST * bucket = htab->buckets[hash];

	struct ENTRY_LIST * iter = bucket;
	while (iter != NULL) {
		if (strcmp(iter->entry.key, item.key) == 0) {
			break;
		}
		iter = iter->next;
	}

	if (iter == NULL && action == FIND) {
		errno = ESRCH;
		return 0;
	}

	if (iter == NULL && action == ENTER) {
		iter = malloc(sizeof(struct ENTRY_LIST));
		if (iter == NULL) {
			errno = ENOMEM;
			return 0;
		}

		iter->entry = item;
		iter->next = bucket;
		htab->buckets[hash] = iter;
		htab->item_size++;
		*retval = &iter->entry;
		return 1;
	}

	*retval = &iter->entry;
	return 1;
}

void hdestroy_r(struct hsearch_data *htab)
{
	struct ENTRY_LIST * head = NULL;
	size_t i;
	for (i = 0; i < htab->bucket_size; ++i) {
		while (htab->buckets[i] != NULL) {
			head = htab->buckets[i];
			htab->buckets[i] = head->next;
			free(head);
		}
	}
	free(htab->buckets);
	htab->item_size = 0;
}

struct hsearch_data hash_table;

int hcreate(size_t nel)
{
	memset(&hash_table, 0, sizeof(struct hsearch_data));
	return hcreate_r(nel, &hash_table);
}

ENTRY *hsearch(ENTRY item, ACTION action)
{
	ENTRY * retval = NULL;
	int ret = hsearch_r(item, action, &retval, &hash_table);
	return ret == 0 ? NULL : retval;
}

void hdestroy(void)
{
	hdestroy_r(&hash_table);
}
