/**
 * dir.c -
 *
 * Author: Bao Hexing <HexingB@qq.com>
 * Created:	1 May 2018
 *
 * Copyright © 2018, Bao Hexing. All Rights Reserved.
 */

#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <errno.h>

int main(int argc, char *argv[])
{
	if (argc < 2)
		return 0;
	DIR * dir = opendir(argv[1]);
	if (dir == NULL) {
		fprintf(stderr, "failed to open %s\n", argv[1]);
		return -1;
	}

	while (1) {
		errno = 0;
		struct dirent * ent = readdir(dir);
		if (ent == NULL && errno == 0) {
			// end
			break;
		} else if (ent == NULL && errno != 0) {
			fprintf(stderr, "failed to readdir\n");
			break;
		} else {
			fprintf(stderr, "%s\n", ent->d_name);
		}
	}

	return 0;
}
