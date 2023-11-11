#include "shell.h"

/**
 * get_environ -  string array copy of our environ
 * @inf: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
char **get_environ(info_t *inf)
{
	if (!inf->environ || inf->environ_changed)
	{
		inf->environ = l_to_strings(inf->env);
		inf->environ_changed = 0;
	}

	return (inf->environ);
}

/**
 * _unsetenv - Remove an environment
 * @inf: constant function prototype.
 * @v:string
 *  Return: 1 on delete or 0 otherwise
 */
int _unsetenv(info_t *inf, char *v)
{
	list_t *node = inf->env;
	size_t i = 0;
	char *b;

	if (node == NULL || v == NULL)
		return (0);

	while (node)
	{
		b = starts_with(node->str, v);
		if (b && *b == '=')
		{
			inf->environ_changed = delete_n_at_index(&(inf->env), i);
			i = 0;
			node = inf->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (inf->environ_changed);
}

/**
 * _setenv - Initialize a new environment,
 *             or modify if is existing
 * @inf: constant function prototype.
 * @v: string
 * @value: string
 * Return: 0
 */
int _setenv(info_t *inf, char *v, char *value)
{
	char *buff = NULL;
	list_t *node;
	char *b;

	if (v == NULL || value == NULL)
		return (0);

	buff = malloc(_strlen(v) + _strlen(value) + 2);
	if (!buff)
		return (1);
	_strcpy(buff, v);
	_strcat(buff, "=");
	_strcat(buff, value);
	node = inf->env;
	while (node)
	{
		b = starts_with(node->str, v);
		if (b && *b == '=')
		{
			free(node->str);
			node->str = buff;
			inf->environ_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_n_e(&(inf->env), buff, 0);
	free(buff);
	inf->environ_changed = 1;
	return (0);
}

