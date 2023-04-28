#include "shell.h"

/**
 * add_node - supplies node to start of list
 * @head: head node address pointer
 * @str: string to field of node
 * @num: history node index
 *
 * Return: list size
 */
list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *headnw;

	if (!head)
		return (NULL);
	headnw = malloc(sizeof(list_t));
	if (!headnw)
		return (NULL);
	_memset((void *)headnw, 0, sizeof(list_t));
	headnw->num = num;
	if (str)
	{
		headnw->str = _strdup(str);
		if (!headnw->str)
		{
			free(headnw);
			return (NULL);
		}
	}
	headnw->next = *head;
	*head = headnw;
	return (headnw);
}

/**
 * add_node_end - node added to end the list
 * @head: head node address pointer
 * @str: string to field of node
 * @num: history node index
 *
 * Return: list size
 */
list_t *add_node_end(list_t **head, const char *str, int num)
{
	list_t *nodenw, *node;

	if (!head)
		return (NULL);

	node = *head;
	nodenw = malloc(sizeof(list_t));
	if (!nodenw)
		return (NULL);
	_memset((void *)nodenw, 0, sizeof(list_t));
	nodenw->num = num;
	if (str)
	{
		while (node->next)
			node = node->next;
		node->next = nodenw;
	}
	else
		*head = nodenw;
	return (nodenw);
}

/**
 * print_list_str - prints string elements only (list_t linked list)
 * @h: first node pointer
 *
 * Return: list size
 */
size_t print_list_str(const list_t *h)
{
	size_t k = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		k++;
	}
	return (k);
}

/**
 * delete_node_at_index - at a given index, deletes the node
 * @head: first node address pointer
 * @index: index of node to be removed
 *
 * Return: 1 on success, 0 otherwise
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
	list_t *node, *nodebf;
	unsigned int k = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (k == index)
		{
			nodebf->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		k++;
		nodebf = node;
		node = node->next;
	}
	return (0);
}

/**
 * free_list - frees all nodes on a list
 * @head_ptr: head node address pointer
 *
 * Return: void
 */
void free_list(list_t **head_ptr)
{
	list_t *node, *nodenxt, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		nodenxt = node->next;
		free(node->str);
		free(node);
		node = nodenxt;
	}
	*head_ptr = NULL;
}
