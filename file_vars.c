#include "shell.h"

/**
 * my_chain - test if current char  is a chain delimeter
 * @inf:  parameter
 * @buff: the char
 * @b: address
 *
 * Return: 1 if chain delimeter else 0
 */
int my_chain(info_t *inf, char *buff, size_t *b)
{
	size_t j = *b;

	if (buff[j] == '|' && buff[j + 1] == '|')
	{
		buff[j] = 0;
		j++;
		inf->cmd_b_t = CMD_OR;
	}
	else if (buff[j] == '&' && buff[j + 1] == '&')
	{
		buff[j] = 0;
		j++;
		inf->cmd_b_t = CMD_AND;
	}
	else if (buff[j] == ';') /* found end of this command */
	{
		buff[j] = 0; /* replace semicolon with null */
		inf->cmd_b_t = CMD_CHAIN;
	}
	else
		return (0);
	*b = j;
	return (1);
}

/**
 * check_chain - checks  continue chaining based on last status
 * @inf: the parameter
 * @buff: the char
 * @b: address
 * @i: position
 * @leng: length
 *
 * Return: Void
 */
void check_chain(info_t *inf, char *buff, size_t *b, size_t i, size_t leng)
{
	size_t j = *b;

	if (inf->cmd_b_t == CMD_AND)
	{
		if (inf->status)
		{
			buff[i] = 0;
			j = leng;
		}
	}
	if (inf->cmd_b_t == CMD_OR)
	{
		if (!inf->status)
		{
			buff[i] = 0;
			j = leng;
		}
	}

	*b = j;
}

/**
 * rep_alias - replaces an aliases in the tokenized string
 * @inf: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int rep_alias(info_t *inf)
{
	int i;
	list_t *node;
	char *b;

	for (i = 0; i < 10; i++)
	{
		node = n_starts_with(inf->alias, inf->argv[0], '=');
		if (node == NULL)
			return (0);
		free(inf->argv[0]);
		b = _strchar(node->str, '=');
		if (!b)
			return (0);
		b = _strdup(b + 1);
		if (!b)
			return (0);
		inf->argv[0] = b;
	}
	return (1);
}

/**
 * rep_vars - replaces vars in the tokenized string
 * @inf: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int rep_vars(info_t *inf)
{
	int i = 0;
	list_t *node;

	for (i = 0; inf->argv[i]; i++)
	{
		if (inf->argv[i][0] != '$' || !inf->argv[i][1])
			continue;

		if (!_strcmp(inf->argv[i], "$?"))
		{
			rep_string(&(inf->argv[i]),
				_strdup(convert_num(inf->status, 10, 0)));
			continue;
		}
		if (!_strcmp(inf->argv[i], "$$"))
		{
			rep_string(&(inf->argv[i]),
				_strdup(convert_num(getpid(), 10, 0)));
			continue;
		}
		node = n_starts_with(inf->env, &inf->argv[i][1], '=');
		if (node)
		{
			rep_string(&(inf->argv[i]),
				_strdup(_strchar(node->str, '=') + 1));
			continue;
		}
		rep_string(&inf->argv[i], _strdup(""));

	}
	return (0);
}

/**
 * rep_string - replaces string
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 if replaced else 0
 */
int rep_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}

