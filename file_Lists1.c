#include "shell.h"

/**
 * l_len - length of linked list
 * @pfn: pointer
 *
 * Return: size
 */
size_t l_len(const list_t *pfn)
{
	size_t i = 0;

	while (pfn)
	{
		pfn = pfn->next;
		i++;
	}
	return (i);
}

/**
 * l_to_strings - array of strings
 * @head: pointer
 *
 * Return: array
 */
char **l_to_strings(list_t *head)
{
	list_t *node = head;
	size_t i = l_len(head), j;
	char **strs;
	char *str;

	if (head == NULL || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}


/**
 * print_l - prints elements of a list_t
 * @pfn: pointer to first node
 *
 * Return: size
 */
size_t print_l(const list_t *pfn)
{
	size_t i = 0;

	while (pfn)
	{
		_puts(convert_num(pfn->n, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(pfn->str ? pfn->str : "(nil)");
		_puts("\n");
		pfn = pfn->next;
		i++;
	}
	return (i);
}

/**
 * n_starts_with - returns node
 * @node: pointer
 * @prefix: string to match
 * @c: character
 *
 * Return: match node or 0
 */
list_t *n_starts_with(list_t *node, char *prefix, char c)
{
	char *b = NULL;

	while (node)
	{
		b = starts_with(node->str, prefix);
		if (b && ((c == -1) || (*b == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_n_index - gets the index of a node
 * @head: pointer
 * @node: pointer
 *
 * Return: index of node or -1
 */
ssize_t get_n_index(list_t *head, list_t *node)
{
	size_t i = 0;

	while (head)
	{
		if (head == node)
			return (i);
		head = head->next;
		i++;
	}
	return (-1);
}
