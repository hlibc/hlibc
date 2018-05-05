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
  fprintf(stderr, "gl_pathc = %lu\n", globbuf->gl_pathc);
  for (size_t i = start_pos; globbuf->gl_pathv[i] != NULL; ++i) {
    fprintf(stderr, "gl_pathv[%lu] = %s\n", i, globbuf->gl_pathv[i]);
  }
  fprintf(stderr, "gl_offs = %lu\n", globbuf->gl_offs);
}

int eff(const char * path, int error) {
  fprintf(stderr, "path: %s error: %d\n", path, error);
  return 0;
}

void test(const char * pattern) {
  glob_t globbuf;

  globbuf.gl_offs = 2;
  int ret = glob("hello].c", GLOB_DOOFFS, eff, &globbuf);

  debug(&globbuf, globbuf.gl_offs);
  fprintf(stderr, "glob return %d GLOB_NOSPACE=%d GLOB_ABORTED=%d GLOB_NOMATCH=%d\n",
          ret, GLOB_NOSPACE, GLOB_ABORTED, GLOB_NOMATCH);

  /* ret = glob("../\*\/\*.bak", GLOB_DOOFFS | GLOB_APPEND, eff, &globbuf); */

  /* debug(&globbuf, 2); */
  /* fprintf(stderr, "glob return %d\n", ret); */

  globbuf.gl_pathv[0] = "ls";
  globbuf.gl_pathv[1] = "-l";
  execvp("ls", &globbuf.gl_pathv[0]);
}

int main(int argc, char *argv[]) {
  test(argv[1]);
  #if 0
  DIR * dir = opendir(argv[1]);
  while (1) {
    struct dirent * direntry = readdir(dir);
    if (direntry == NULL) {
      fprintf(stderr, "null read\n");
      break;
    }
    fprintf(stderr, "readdir: %s\n", direntry->d_name);
  }
  #endif
  return 0;
}
