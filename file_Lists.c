#include "shell.h"

/**
 * add_n - adds a node to the start of the list
 * @head: address
 * @str: string
 * @n: node index
 *
 * Return: size
 */
list_t *add_n(list_t **head, const char *str, int n)
{
	list_t *n_head;

	if (!head)
		return (NULL);
	n_head = malloc(sizeof(list_t));
	if (!n_head)
		return (NULL);
	_memset((void *)n_head, 0, sizeof(list_t));
	n_head->n = n;
	if (str)
	{
		n_head->str = _strdup(str);
		if (!n_head->str)
		{
			free(n_head);
			return (NULL);
		}
	}
	n_head->next = *head;
	*head = n_head;
	return (n_head);
}

/**
 * add_n_e - adds a node to the end of the list
 * @head: address
 * @str: string
 * @n: node index
 *
 * Return: size
 */
list_t *add_n_e(list_t **head, const char *str, int n)
{
	list_t *n_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	n_node = malloc(sizeof(list_t));
	if (n_node == NULL)
		return (NULL);
	_memset((void *)n_node, 0, sizeof(list_t));
	n_node->n = n;
	if (str)
	{
		n_node->str = _strdup(str);
		if (!n_node->str)
		{
			free(n_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = n_node;
	}
	else
		*head = n_node;
	return (n_node);
}

/**
 * print_l_s - prints only the str element of a list_t
 * @pfn: pointer to first node
 *
 * Return: size
 */
size_t print_l_s(const list_t *pfn)
{
	size_t i = 0;

	while (pfn)
	{
		_puts(pfn->str ? pfn->str : "(nil)");
		_puts("\n");
		pfn = pfn->next;
		i++;
	}
	return (i);
}

/**
 * delete_n_at_index - deletes node
 * @head: address
 * @index: index
 *
 * Return: 1 or 0 on failure
 */
int delete_n_at_index(list_t **head, unsigned int index)
{
	list_t *node, *p_n;
	unsigned int i = 0;

	if (head == NULL || *head == NULL)
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
		if (i == index)
		{
			p_n->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		i++;
		p_n = node;
		node = node->next;
	}
	return (0);
}

/**
 * free_l - frees all nodes of a list
 * @head_ptr: address
 *
 * Return: void
 */
void free_l(list_t **head_ptr)
{
	list_t *node, *next_node, *head;

	if (head_ptr == NULL || *head_ptr == NULL)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;
}
