#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <stdio.h>
#include <stdlib.h>
#include <search.h>
#include <string.h>

static char *data[] = { "alpha", "bravo", "charlie", "delta",
	 "echo", "foxtrot", "golf", "hotel", "india", "juliet",
	 "kilo", "lima", "mike", "november", "oscar", "papa",
	 "quebec", "romeo", "sierra", "tango", "uniform",
	 "victor", "whisky", "x-ray", "yankee", "zulu"
};

int hcreate_test()
{
	ENTRY e, *ep;
	int i;

	hcreate(30);

	for (i = 0; i < 24; i++) {
	   e.key = data[i];
	   /* data is just an integer, instead of a
		  pointer to something */
	   e.data = (void *) i;
	   ep = hsearch(e, ENTER);
	   /* there should be no failures */
	   if (ep == NULL) {
		   fprintf(stderr, "entry failed\n");
		   return -1;
	   }
	}

	for (i = 22; i < 26; i++) {
	   /* print two entries from the table, and
		  show that two are not in the table */
	   e.key = data[i];
	   ep = hsearch(e, FIND);
	   printf("%s -> %s:%d\n", e.key,
			  ep ? ep->key : "NULL", ep ? (int)(ep->data) : 0);
	}
	hdestroy();
	return 0;
}

int reentrant_hcreate_test(void)
{
	ENTRY e, *ep;
	int i, ret;

	struct hsearch_data htab;
	memset(&htab, 0, sizeof(struct hsearch_data));

	hcreate_r(30, &htab);

	for (i = 0; i < 24; i++) {
		e.key = data[i];
		/* data is just an integer, instead of a
		   pointer to something */
		e.data = (void *) i;
		ret = hsearch_r(e, ENTER, &ep, &htab);
		/* there should be no failures */
		if (ret == 0) {
			fprintf(stderr, "entry failed\n");
			return -1;
		}
	}

	for (i = 2; i < 26; i++) {
		/* print two entries from the table, and
		   show that two are not in the table */
		e.key = data[i];
		e.data = (void*) 1000;
		ret = hsearch_r(e,  i == 25 ? ENTER : FIND, &ep, &htab);
		if (ret == 0) {
			printf("%s -> %s:%d\n", e.key, "NULL", 0);
		} else {
			printf("%s -> %s:%d\n", e.key,
			   ep->key, (int)(ep->data));
		}
	}
	hdestroy_r(&htab);
	return 0;
}

int main(void)
{
	if (hcreate_test() != 0) {
		printf("hcreate_test() failed\n");
		exit(EXIT_FAILURE);
	}
	printf("hcreate_test() done\n");

	if (reentrant_hcreate_test() != 0) {
		printf("reentrant_hcreate_test() failed\n");
		exit(EXIT_FAILURE);
	}
	printf("reentrant_hcreate_test() done\n");

	exit(EXIT_SUCCESS);
}
