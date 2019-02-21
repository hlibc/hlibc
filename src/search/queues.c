#include <stddef.h>
#include <search.h>

struct queue
{
	struct queue *next;
	struct queue *prev;
};

void insque(void *element, void *pred)
{
	struct queue *node;
	struct queue *prev;
	struct queue *next;

	node = element;

	if((prev = pred) != NULL)
	{
		if((next = prev->next) != NULL)
		{
			next->prev = node;
		}

		prev->next = node;
	}
	else
	{
		next = NULL;
	}

	node->prev = prev;
	node->next = next;
}

void remque(void *element)
{
	struct queue *node;
	node = element;

	if(node->next != NULL)
	{
		node->next->prev = node->prev;
	}

	if(node->prev != NULL)
	{
		node->prev->next = node->next;
	}

	node->next = node->prev = NULL;
}
