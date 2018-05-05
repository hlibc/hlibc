/**
 * ftw.c - ftw implementation
 *
 * Author: Bao Hexing <HexingB@qq.com>
 * Created:	 2 January 2018
 *
 * Copyright © 2018, Bao Hexing. All Rights Reserved.
 */

#include <ftw.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>

struct name_node {
	char *name;
	struct name_node *next;
};

struct name_list {
	struct name_node *head;
};

static struct name_node * new_item(const char *name)
{
	struct name_node *node = (struct name_node*)malloc(sizeof(struct name_node));
	if (node == NULL) {
		return NULL;
	}

	node->name = (char*)name;
	node->next = NULL;
	return node;
}

static int init_name_list(const char * path, struct name_list *list)
{
	char * root = strdup(path);
	if (root == NULL) {
		return -1;
	}

	if (strlen(root) > 1 && root[strlen(root) - 1] == '/') {
		root[strlen(root) - 1] = '\0';
	}

	list->head = new_item(root);
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

static int push(const char *name, struct name_list *list)
{
	struct name_node *node = new_item(name);
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

static int walk(const char *path, struct name_list *list)
{
	char * full_path = NULL;
	struct dirent *dir_entry = NULL;
	DIR *dir = opendir(path);
	if (dir == NULL) {
		return -1;
	}

	errno = 0;

	while ((dir_entry = readdir(dir)) != NULL) {
		if (strcmp(dir_entry->d_name, "..") == 0 ||
				strcmp(dir_entry->d_name, ".") == 0) {
			continue;
		}
		full_path = (char*)malloc(strlen(path) + 2 + strlen(dir_entry->d_name));
		strcpy(full_path, path);
		strcat(full_path, "/");
		strcat(full_path, dir_entry->d_name);
		if (push(full_path, list) == -1) {
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

static int ftw_internal(const char *path,
                        int (*fn)(const char *name, const struct stat *ptr, int flag),
                        struct name_list *list)
{
	struct stat buf;
	int flag = 0;
	int ret = lstat(path, &buf);
	if (ret == -1) {
		return -1;
	}

	if ((buf.st_mode & S_IFMT) == S_IFLNK) {
		ret = stat(path, &buf);
	}

	if (ret != 0) {
		flag = FTW_NS;
		memset(&buf, 0, sizeof(struct stat));
	}

	switch(buf.st_mode & S_IFMT) {
		case S_IFDIR:
			if (access(path, R_OK) == 0) {
				flag = FTW_D;
			} else {
				errno = 0;
				flag = FTW_DNR;
			}
			break;
		case S_IFLNK:
			if (flag != FTW_NS) {
				flag = FTW_F;
			}
			break;
		case S_IFIFO:
		case S_IFCHR:
		case S_IFBLK:
		case S_IFSOCK:
		case S_IFREG:
			flag = FTW_F;
			break;
		default:
			break;
	}

	ret = fn(path, &buf, flag);
	if (ret != 0) {
		return ret;
	}

	if ((buf.st_mode & S_IFMT) == S_IFDIR && flag != FTW_DNR) {
		ret = walk(path, list);
		if (ret == -1) {
			return ret;
		}
	}

	return 0;
}

int ftw(const char *path,
        int (*fn)(const char *, const struct stat *ptr, int flag),
        int ndirs)
{
	struct name_list list;
	struct name_node *node = NULL;
	int ret = init_name_list(path, &list);
	if (ret == -1) {
		return -1;
	}

	while ((node = pop(&list)) != NULL) {
		ret = ftw_internal(node->name, fn, &list);
		free(node->name);
		free(node);

		if (ret != 0) {
			deinit_name_list(&list);
			return ret;
		}
	}

	return 0;
}

