/**
 * glob.c - glob() and globfree() implementation
 *
 * Author: Bao Hexing <HexingB@qq.com>
 * Created: 28 April 2018
 *
 * Copyright © 2018, Bao Hexing. All Rights Reserved.
 */

#include <glob.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

enum state {
  E_START = 0,
  E_NEXT,          // the header is processed, now turn to next node in list
  E_DISCARD,       // the header node dismatches the pattern, discard it
  E_STORE,         // the header node mathes the pattern, store it
  E_SCOPE,         // process "["
  E_ASTERISK,      // process "*"
  E_GLOB_NOSPACE,  // malloc failed
  E_GLOB_ABORTED,  // read error
  E_GLOB_NOMATCH,  // list size is 0
  E_END            // pattern_pos points to the end of pattern
};

struct path_node {
  size_t path_length;  // length of path_name;
  const char * path_name;
  const char * pattern_pos;
  const char * path_pos;
  struct path_node * next;
};

struct path_list {
  struct path_node * head;
  struct path_node ** tail;

  // input arguments
  int error;
  int flags;
  const char * pattern;
  glob_t *pglob;
  int (*errfunc)(const char *, int);

  size_t allocated_count;
  size_t matched_count;
  size_t next_accepted_pos;
  DIR * dir;
  const char * pattern_pos;
};

struct pattern_state {
  enum state (*process)(struct path_list*);
};

static enum state iterate_entries(const char * path, struct path_list * list) {
  list->dir = opendir(path);
  if (list->dir == NULL) {
    return E_GLOB_ABORTED;
  }

  while (1) {
    errno = 0;
    struct dirent * direntry = readdir(list->dir);
    if (direntry == NULL && errno == 0) {
      break;  // end of entries
    }

    if (direntry == NULL) {
      closedir(list->dir);
      return E_GLOB_ABORTED;   // TODO: return an appropriate error code
    }

    // for every entry in this directory, allocate a path_node for future
    // processing.yes this occupies more space, but simplifies the code.
    size_t pathlength = strlen(path) + strlen(direntry->d_name) + 1;
    struct path_node * node =
        (struct path_node*)malloc(sizeof(struct path_node) + pathlength);
    if (node == NULL) {
      closedir(list->dir);
      return E_GLOB_NOSPACE;
    }
    char * pathname = (char*)(node + 1);
    if (strcmp(path, ".") == 0) {
      strcpy(pathname, direntry->d_name);
      node->path_pos = pathname;
    } else {
      strcpy(pathname, path);
      node->path_pos = pathname + strlen(path);
      strcat(pathname, direntry->d_name);
    }
    node->path_name = pathname;
    node->path_length = pathlength;
    node->pattern_pos = list->pattern_pos;
    node->next = NULL;

    // insert at the tail of the list
    *list->tail = node;
    list->tail = &node->next;
  }
  closedir(list->dir);
  return E_NEXT;
}

// check whether the pattern is an absolute path.
static enum state glob_start(struct path_list * list) {
  if (list->pattern == NULL
      || list->pattern[0] == '\0'
      || list->pattern[0] == '-') {
    return E_GLOB_NOMATCH;
  }

  const char * path = NULL;
  if (list->pattern[0] == '/') {
    path = "/";
    list->pattern_pos = list->pattern + 1;
  } else {
    path = ".";
    list->pattern_pos = list->pattern;
  }

  return iterate_entries(path, list);
}

static enum state glob_discard(struct path_list * list) {
  if (list->head == NULL) {
    return E_END;
  }

  struct path_node * head = list->head;
  list->head = head->next;
  // fprintf(stderr, "\t\tdiscard %s\n", head->path_name);
  free(head);
  return E_NEXT;
}

static enum state glob_store(struct path_list * list) {
  if (list->allocated_count <= list->next_accepted_pos) {
    list->allocated_count = list->next_accepted_pos + 16;
    char ** paths = realloc(list->pglob->gl_pathv,
                            list->allocated_count * sizeof(char*));
    if (paths == NULL) {
      return E_GLOB_NOSPACE;
    }
    memset(paths + list->next_accepted_pos, 0x0, 16 * sizeof(char*));
    list->pglob->gl_pathv = paths;
  }

  list->pglob->gl_pathv[list->next_accepted_pos] =
      strdup(list->head->path_name);
  if (list->pglob->gl_pathv[list->next_accepted_pos] == NULL) {
    return E_GLOB_NOSPACE;
  }
  // fprintf(stderr, "\t\tstore path %s\n", list->head->path_name);
  list->next_accepted_pos++;
  list->pglob->gl_pathc++;
  list->matched_count++;
  return E_DISCARD;
}

static enum state glob_scope(struct path_list * list) {
  return E_DISCARD;
}

static enum state glob_asterisk(struct path_list * list) {
  return E_DISCARD;
}

/*
 * process one path_node, the result will be in 4 state:
 *  1. the path dismatch the pattern, discard it
 *  2. the path match part of the pattern(need to process sub directories or
 *     files), iterate its subdirectories and files and create according
 *     path_node and discard this path_node
 *  3. the path match totally the pattern, remove it from list head and save it
 *     in glob structure
 *  4.
 */
static enum state glob_next(struct path_list * list) {
  if (list->head == NULL) {
    return E_END;
  }

  struct path_node * head = list->head;
  // fprintf(stderr, "\t\tprocessing %s\n", head->path_name);
  while (*head->path_pos != '\0' &&
         *head->pattern_pos != '\0') {
    switch(*head->pattern_pos) {
      case '?':
        ++head->path_pos;
        ++head->pattern_pos;
        break;
      case '[':
        return E_SCOPE;
      case '*':
        return E_ASTERISK;
      case '\\':
        fprintf(stderr, "got this\n");
      default:
        if (*head->path_pos != *head->pattern_pos) {
          return E_DISCARD;  // dismatch
        } else {
          ++head->path_pos;
          ++head->pattern_pos;
        }
        break;
    }
  }

  if (*head->path_pos == '\0' && *head->pattern_pos == '\0') {
    return E_STORE;
  }
  return E_DISCARD;
}

static enum state glob_error_no_space(struct path_list * list) {
  list->error = GLOB_NOSPACE;
  return E_END;
}

static enum state glob_error_read_error(struct path_list * list) {
  list->error = GLOB_ABORTED;
  return E_END;
}

static int candidate_list_init(struct path_list * list,
                                const char * pattern,
                                int flags,
                                int (*errfunc)(const char *, int),
                                glob_t * pglob) {
  list->head = NULL;
  list->tail = &list->head;
  list->errfunc = errfunc;
  list->error = 0;
  list->flags = flags;
  list->pattern = pattern;
  list->pglob = pglob;
  list->matched_count = 0;

  if (flags & GLOB_DOOFFS) {
    list->next_accepted_pos = list->pglob->gl_offs;
  } else {
    list->next_accepted_pos = list->pglob->gl_offs = 0;
  }

  if (flags & GLOB_APPEND) {
    list->next_accepted_pos += list->pglob->gl_pathc;
  } else {
    list->pglob->gl_pathc = 0;
    list->pglob->gl_pathv = NULL;
  }

  if (list->next_accepted_pos > 0) {
    char ** paths = realloc(list->pglob->gl_pathv,
                            list->next_accepted_pos * sizeof(char*));
    if (paths == NULL) {
      return GLOB_NOSPACE;
    }

    // initialize the reserved slots
    if ((flags & GLOB_APPEND) == 0) {
      for (size_t i = 0; i < list->pglob->gl_offs; ++i) {
        paths[i] = NULL;
      }
    }

    list->pglob->gl_pathv = paths;
  }

  list->allocated_count = 0;
  list->dir = NULL;
  return 0;
}

static void state_processor_init(struct pattern_state * states, int flags) {
  states[E_START].process = glob_start;
  states[E_NEXT].process = glob_next;
  states[E_DISCARD].process = glob_discard;
  states[E_STORE].process = glob_store;
  states[E_SCOPE].process = glob_scope;
  states[E_ASTERISK].process = glob_asterisk;
  states[E_GLOB_NOSPACE].process = glob_error_no_space;
  states[E_GLOB_ABORTED].process = glob_error_read_error;
  if (flags) {
    states[E_END].process = glob_end;
  } else {
    states[E_END].process = glob_end;
  }
}

int glob(const char *pattern,
         int flags,
         int (*errfunc)(const char *, int),
         glob_t *pglob) {
  struct path_list list;
  int ret = candidate_list_init(&list, pattern, flags, errfunc, pglob);
  if (ret != 0) {
    return ret;
  }

  struct pattern_state states[E_END + 1] = { {NULL} };
  state_processor_init(states, flags);

  enum state s = E_START;
  while (s != E_END) {
    s = states[s].process(&list);
  }

  if (list.matched_count == 0) {
    return GLOB_NOMATCH;
  }
  // process list
  return 0;
}

void globfree(glob_t *pglob) {
  for (size_t pos = pglob->gl_offs; pglob->gl_pathv[pos] != NULL; ++pos) {
    free(pglob->gl_pathv[pos]);
  }
  free(pglob->gl_pathv);
}
