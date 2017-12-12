#include <assert.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

typedef struct object
{
	size_t size;
	struct object *next;
	int free;
}object;

void *base = NULL;

object *find_free_block(object **last, size_t size)
{
	object *current = base;
	while (current && !(current->free && current->size >= size)) {
		*last = current;
		current = current->next;
	}
	return current;
}

object *request_space(object *last, size_t size)
{
	object *block;
	block = sbrk(0);
	void *request = sbrk(size + sizeof(object));
	if (request == (void *)-1) {
		return NULL;
	}

	if (last) {
		last->next = block; // NULL on first request.
	}

	block->size = size;
	block->next = NULL;
	block->free = 0;
	return block;
}
void *malloc(size_t size)
{
	object *block;

	if (size <= 0) {
		return NULL;
	}

	if (!base) {
		block = request_space(NULL, size);
		if (!block) {
			return NULL;
		}
		base = block;
	}
	else {
		object *last = base;
		block = find_free_block(&last, size);
		if (!block) {
			block = request_space(last, size);
			if (!block) {
				return NULL;
			}
		}
		else {
			block->free = 0;
		}
	}

	return (block + 1);
}

object *get_block_ptr(void *ptr)
{
	return (object *)ptr - 1;
}

void free(void *ptr)
{
	object *block_ptr;
	if (!ptr) {
		return;
	}
	block_ptr = (object *)ptr - 1;
	block_ptr->free = 1;
}

void *realloc(void *ptr, size_t size)
{
	void *new_ptr;
	object *block_ptr;
	if (!ptr) {
		return malloc(size);
	}

	block_ptr = (object *)ptr - 1;
	if (block_ptr->size >= size) {
		return ptr;
	}
	
	if(!(new_ptr = malloc(size))) 
		return NULL;

	memcpy(new_ptr, ptr, block_ptr->size);
	free(ptr);
	return new_ptr;
}

void *calloc(size_t nelem, size_t elsize)
{
	size_t size = nelem * elsize;
	void *ptr = malloc(size);
	if (ptr) {
		memset(ptr, 0, size);
	}
	return ptr;
}
