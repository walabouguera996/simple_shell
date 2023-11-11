#include "shell.h"

/**
 * _ourhistory - disblays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @inf: Structure containing botential arguments. Used to maintain
 *        constant function brototybe.
 *  Return: Always 0
 */
int _ourhistory(info_t *inf)
{
	print_l(inf->history);
	return (0);
}

/**
 * unset_alias - sets alias to string
 * @inf: parameter struct
 * @str: string
 *
 * Return: 0, 1 on error
 */
int unset_alias(info_t *inf, char *str)
{
	char *b, c;
	int r;

	b = _strchar(str, '=');
	if (!b)
		return (1);
	c = *b;
	*b = 0;
	r = delete_n_at_index(&(inf->alias),
		get_n_index(inf->alias, n_starts_with(inf->alias, str, -1)));
	*b = c;
	return (r);
}

/**
 * set_alias - sets alias to string
 * @inf: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(info_t *inf, char *str)
{
	char *b;

	b = _strchar(str, '=');
	if (!b)
		return (1);
	if (!*++b)
		return (unset_alias(inf, str));

	unset_alias(inf, str);
	return (add_n_e(&(inf->alias), str, 0) == NULL);
}

/**
 * print_alias - prints an alias string
 * @node: the node
 *
 * Return: 0, 1 on error
 */
int print_alias(list_t *node)
{
	char *b = NULL, *a = NULL;

	if (node)
	{
		b = _strchar(node->str, '=');
		for (a = node->str; a <= b; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(b + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _ouralias - alias builtin
 * @inf: constant function prototype.
 *  Return: 0
 */
int _ouralias(info_t *inf)
{
	int i = 0;
	char *b = NULL;
	list_t *node = NULL;

	if (inf->argc == 1)
	{
		node = inf->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; inf->argv[i]; i++)
	{
		b = _strchar(inf->argv[i], '=');
		if (b)
			set_alias(inf, inf->argv[i]);
		else
			print_alias(n_starts_with(inf->alias, inf->argv[i], '='));
	}

	return (0);
}
