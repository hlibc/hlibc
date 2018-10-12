#ifndef _SEARCH_H
#define _SEARCH_H

#ifdef __cplusplus
extern "C" {
#endif

#define __NEED_size_t
#include <bits/types.h>

typedef enum { FIND, ENTER } ACTION;
typedef enum { preorder, postorder, endorder, leaf } VISIT;

typedef struct {
	char *key;
	void *data;
} ENTRY;

int hcreate(size_t);
void hdestroy(void);
ENTRY *hsearch(ENTRY, ACTION);

#ifdef _GNU_SOURCE
struct ENTRY_LIST;
struct hsearch_data
{
    struct ENTRY_LIST ** buckets;
    size_t bucket_size;
    size_t item_size;
};

int hcreate_r(size_t nel, struct hsearch_data *htab);
int hsearch_r(ENTRY item, ACTION action, ENTRY **retval,
			  struct hsearch_data *htab);
void hdestroy_r(struct hsearch_data *htab);
#endif

void insque(void *, void *);
void remque(void *);

void *lsearch(const void *, void *, size_t *, size_t,
	int (*)(const void *, const void *));
void *lfind(const void *, const void *, size_t *, size_t,
	int (*)(const void *, const void *));

void *tdelete(const void *, void **, int(*)(const void *, const void *));
void *tfind(const void *, void *const *, int(*)(const void *, const void *));
void *tsearch(const void *, void **, int (*)(const void *, const void *));
void twalk(const void *, void (*)(const void *, VISIT, int));

#ifdef _GNU_SOURCE
struct qelem {
	struct qelem *q_forw, *q_back;
	char q_data[1];
};
#endif

#ifdef __cplusplus
}
#endif

#endif
