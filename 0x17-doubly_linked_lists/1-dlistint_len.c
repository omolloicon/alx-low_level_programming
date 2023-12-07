#include "lists.h"

/**
 * dlistint_len - number of nodes
 * @h: pointer
 * Return: nodes count
 */
size_t dlistint_len(const dlistint_t *h)
{
	size_t nodes = 0;

	if (!h)
		return (0);

	while (h)
	{
		nodes++;
		h = h->next;
	}

	return (nodes);
}
