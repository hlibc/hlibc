/**
 * fwrite.c - fwrite test
 *
 * Author: Bao Hexing <HexingB@qq.com>
 * Created: 29 May 2018
 *
 * Copyright © 2018, Bao Hexing. All Rights Reserved.
 */

#include <stdio.h>
#include <string.h>
int main(void)
{
	char * ptr = "hello, hlibc\nhello, world\nhello, graff\n";
	size_t ret = fwrite(ptr, 1, strlen(ptr), stdout);
	fprintf(stdout, "ret = %zu\n", ret);
	return 0;
}
