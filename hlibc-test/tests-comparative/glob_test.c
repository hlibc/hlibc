/**
 * glob_test.c - glob test
 *
 * Author: Bao Hexing <HexingB@qq.com>
 * Created: 28 April 2018
 *
 * Copyright © 2018, Bao Hexing. All Rights Reserved.
 */

#include <glob.h>
#include <unistd.h>
#include <stdio.h>
#include <dirent.h>

static void debug(const glob_t * globbuf, size_t start_pos) {
  size_t i = 0;
  fprintf(stderr, "gl_pathc = %lu\n", globbuf->gl_pathc);
  for (i = start_pos; globbuf->gl_pathv[i] != NULL; ++i) {
    fprintf(stderr, "gl_pathv[%lu] = %s\n", i, globbuf->gl_pathv[i]);
  }
  fprintf(stderr, "gl_offs = %lu\n", globbuf->gl_offs);
}

int eff(const char * path, int error) {
  fprintf(stderr, "path: %s error: %d\n", path, error);
  return 0;
}

int main(int argc, char *argv[]) {
  int ret = 0;
  glob_t globbuf;

  if (argc > 1) {
    globbuf.gl_offs = 2;
    ret = glob(argv[1], GLOB_DOOFFS, eff, &globbuf);
    fprintf(stderr, "first call return %d\n", ret);
    debug(&globbuf, globbuf.gl_offs);
    globbuf.gl_pathv[0] = "ls";
    globbuf.gl_pathv[1] = "-l";
  }

  if (argc > 2) {
    // globbuf.gl_offs = 3; // is that would overwrite the result of previous call?
    ret = glob(argv[2], GLOB_DOOFFS | GLOB_APPEND, eff, &globbuf);
    fprintf(stderr, "second call return %d\n", ret);
    debug(&globbuf, globbuf.gl_offs);
    globbuf.gl_pathv[2] = "-a";
  }

  execvp("ls", &globbuf.gl_pathv[0]);
  return 0;
}
