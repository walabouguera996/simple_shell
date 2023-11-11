#include "shell.h"

/**
 * _ourenv - prints the current environment
 * @inf: constant function
 * Return: 0
 */
int _ourenv(info_t *inf)
{
	print_l_s(inf->env);
	return (0);
}

/**
 * _getenv - gets the value of an environ variable
 * @inf: constant function
 * @name: env var name
 *
 * Return: value
 */
char *_getenv(info_t *inf, const char *name)
{
	list_t *node = inf->env;
	char *b;

	while (node)
	{
		b = starts_with(node->str, name);
		if (b && *b)
			return (b);
		node = node->next;
	}
	return (NULL);
}

/**
 * _oursetenv - Initialize a new environment
 *             or modify if existing
 * @inf: constant function
 *  Return: 0
 */
int _oursetenv(info_t *inf)
{
	if (inf->argc != 3)
	{
		_eputstr("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(inf, inf->argv[1], inf->argv[2]))
		return (0);
	return (1);
}

/**
 * _ourunsetenv - Remove an environment variable
 * @inf: constant function brototybe.
 *  Return: 0
 */
int _ourunsetenv(info_t *inf)
{
	int i;

	if (inf->argc == 1)
	{
		_eputstr("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= inf->argc; i++)
		_unsetenv(inf, inf->argv[i]);

	return (0);
}

/**
 * populate_env_l - populates env linked list
 * @inf: constant function brototybe.
 * Return: 0
 */
int populate_env_l(info_t *inf)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_n_e(&node, environ[i], 0);
	inf->env = node;
	return (0);
}
