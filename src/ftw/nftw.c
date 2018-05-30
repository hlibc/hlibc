/**
 * nftw.c - nftw implementation
 *
 * Author: Bao Hexing <HexingB@qq.com>
 * Created:	 5 January 2018
 *
 * Copyright © 2018, Bao Hexing. All Rights Reserved.
 */

#include <ftw.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>

struct name_node {
	char *name;
	int flag;
	int processed; // 0 if not proccessed, or 1
	struct stat statbuf;
	struct FTW ftwbuf;
	struct name_node *next;
};

struct name_list {
	struct name_node *head;
	struct stat statbuf; // stat info of target(top) directory
	int flags;
};

static struct name_node * new_item(const char *name,
                                   int flag,
                                   const struct stat * statbuf,
                                   const struct FTW * ftwbuf)
{
	struct name_node *node = (struct name_node*)malloc(sizeof(struct name_node));
	if (node == NULL) {
		return NULL;
	}

	node->name = (char*)name;
	node->flag = flag;
	node->processed = 0;
	node->statbuf = *statbuf;
	node->ftwbuf = *ftwbuf;
	node->next = NULL;
	return node;
}

static int get_type(const char *path, int flags, struct stat * statbuf)
{
	int ret;

	errno = 0;
	ret = lstat(path, statbuf);
	if (ret == -1 && errno == EACCES) {
		memset(statbuf, 0, sizeof(struct stat));
		return FTW_NS;
	}

	if (ret == -1) {
		return -1;
	}

	if ((statbuf->st_mode & S_IFMT) == S_IFLNK) {
		if ((flags & FTW_PHYS) == FTW_PHYS) {
			return FTW_SL;
		} else {
			ret = stat(path, statbuf);
			if (ret == -1) {
				memset(statbuf, 0, sizeof(struct stat));
				return FTW_SLN;
			}
		}
	}

	int flag = FTW_F;
	if ((statbuf->st_mode & S_IFMT) == S_IFDIR) {
		flag = FTW_D;
		if ((flags & FTW_DEPTH) == FTW_DEPTH) {
			flag = FTW_DP;
		}

		if (access(path, R_OK) != 0) {
			errno = 0;
			flag = FTW_DNR;
		}
	}

	return flag;
}

static int init_name_list(const char *path,
                          int flags,
                          struct name_list *list)
{
	struct stat statbuf;
	struct FTW ftwbuf = {0, 0};
	char * root = strdup(path);
	if (root == NULL) {
		return -1;
	}

	if (strlen(root) > 1 && root[strlen(root) - 1] == '/') {
		root[strlen(root) - 1] = '\0';
	}

	char * last_slash = strrchr(root, '/');
	if (last_slash != NULL) {
		ftwbuf.base = last_slash - root + 1;
	}

	int flag = get_type(path, flags, &statbuf);
	if (flag == -1) {
		free(root);
		return -1;
	}

	list->head = new_item(root, flag, &statbuf, &ftwbuf);
	list->flags = flags;
	// for check of whether files are in the same file system as path
	list->statbuf = statbuf;
	if (list->head == NULL) {
		free(root);
		return -1;
	}
	return 0;
}

static int deinit_name_list(struct name_list *list)
{
	struct name_node *node;
	while (list->head != NULL) {
		node = list->head;
		list->head = node->next;
		free(node->name);
		free(node);
	}
	return 0;
}

static int push(const char *name,
                const struct FTW * ftwbuf,
                struct name_list *list)
{
	struct name_node *node = NULL;
	struct stat statbuf;

	int flag = get_type(name, list->flags, &statbuf);
	if (flag == -1) {
		return -1;
	}

	if ((list->flags & FTW_MOUNT) == FTW_MOUNT &&
			statbuf.st_dev != list->statbuf.st_dev) {
		return 0;
	}

	node = new_item(name, flag, &statbuf, ftwbuf);
	if (node == NULL) {
		return -1;
	}

	node->next = list->head;
	list->head = node;
	return 0;
}

static struct name_node * pop(struct name_list * list)
{
	if (list == NULL || list->head == NULL) {
		return NULL;
	}

	struct name_node *head = list->head;
	list->head = head->next;
	return head;
}

static int walk(const char *path,
                const struct FTW * topftw,
                struct name_list *list)
{
	struct FTW ftwbuf;
	char * full_path = NULL;
	struct dirent *dir_entry = NULL;
	DIR *dir = opendir(path);
	if (dir == NULL) {
		return -1;
	}

	ftwbuf.base = strlen(path) + 1; // including '/'
	ftwbuf.level = topftw->level + 1;

	errno = 0;

	while ((dir_entry = readdir(dir)) != NULL) {
		if (strcmp(dir_entry->d_name, "..") == 0 ||
				strcmp(dir_entry->d_name, ".") == 0) {
			continue;
		}
		full_path = (char*)malloc(ftwbuf.base + 1 /* for '\0' */ + strlen(dir_entry->d_name));
		strcpy(full_path, path);
		strcat(full_path, "/");
		strcat(full_path, dir_entry->d_name);
		if (push(full_path, &ftwbuf, list) == -1) {
			closedir(dir);
			return -1;
		}
	}

	if (dir_entry == NULL && errno != 0) {
		closedir(dir);
		return -1;
	}

	closedir(dir);
	return 0;
}

static int change_dir(struct name_node *node, struct name_list *list)
{
	if ((list->flags & FTW_CHDIR) == FTW_CHDIR) {
		if (node->flag == FTW_D || node->flag == FTW_DP) {
			return chdir(node->name);
		}

		char * last_slash = strrchr(node->name, '/');
		if (last_slash == NULL) {
			return 0;
		}

		*last_slash = '\0';
		int ret = chdir(node->name);
		*last_slash = '/';
		return ret;
	}

	return 0;
}

static int nftw_internal(struct name_node *node,
                         int (*fn)(const char *, const struct stat *, int, struct FTW *),
                         struct name_list *list)
{
	int ret = 0;
	if ((list->flags & FTW_DEPTH) == FTW_DEPTH &&
			node->flag == FTW_DP && // a directory can be read
			node->processed == 0) { // first encountered, not processed
		// push back this node
		node->processed = 1;
		node->next = list->head;
		list->head = node;

		// push children files
		return walk(node->name, &node->ftwbuf, list);
	}

	ret = change_dir(node, list);
	if (ret != 0) {
		free(node->name);
		free(node);
		return ret;
	}

	ret = fn(node->name, &node->statbuf, node->flag, &node->ftwbuf);

	if (ret == 0 &&
			(list->flags & FTW_DEPTH) == 0 &&
			node->flag == FTW_D &&
			walk(node->name, &node->ftwbuf, list) != 0) {
		ret = -1;
	}

	free(node->name);
	free(node);
	return ret;
}

int nftw(const char *path,
         int (*fn)(const char *, const struct stat *, int, struct FTW *),
         int fd_limit,
         int flags)
{
	struct name_list list;
	struct name_node *node = NULL;
	int ret = init_name_list(path, flags, &list);
	if (ret == -1) {
		return -1;
	}

	while ((node = pop(&list)) != NULL) {
		ret = nftw_internal(node, fn, &list);
		if (ret != 0) {
			deinit_name_list(&list);
			return ret;
		}
	}

    (void)fd_limit;
	return 0;
}

