/**
 * memmove.c - tests for memmove, memcpy, strcpy, etc
 *
 * Author: Bao Hexing <HexingB@qq.com>
 * Created: 24 May 2018
 *
 * Copyright © 2018, Bao Hexing. All Rights Reserved.
 */

#include <stdio.h>
#include <string.h>

int main(void) {
	char buf[256] = {0};

	strcpy(buf, "The quick brown fox jumps over the lazy dog.");
	fprintf(stdout, "%s\n", buf);

	char * p = strstr(buf, "lazy");
	if (p != NULL) {
		strcat(p, "clumzy");
		fprintf(stdout, "%s\n", p);
	}

	p = strrchr(buf, 's');
	if (p != NULL) {
			strcpy(p, "dog lazy the over");
	}
	fprintf(stdout, "%s\n", buf);

	p = strstr(buf, "fox");
	p = memmove(p, buf, 100);
	fprintf(stdout, "%s\n", buf);

	int ret = memcmp(buf, p, 16);
	if (ret == 0) {
			fprintf(stdout, "identical\n");
	} else {
			fprintf(stdout, "not equal\n");
	}

	// TODO other string related tests.

	return 0;
}
