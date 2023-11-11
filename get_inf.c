#include "shell.h"

/**
 * clear_inf - initializes info_t
 * @inf: address
 */
void clear_inf(info_t *inf)
{
	inf->arg = NULL;
	inf->argv = NULL;
	inf->path = NULL;
	inf->argc = 0;
}

/**
 * set_inf - initializes info_t
 * @inf: address
 * @argvect: argument vector
 */
void set_inf(info_t *inf, char **argvect)
{
	int i = 0;

	inf->fname = argvect[0];
	if (inf->arg)
	{
		inf->argv = strtow(inf->arg, " \t");
		if (!inf->argv)
		{

			inf->argv = malloc(sizeof(char *) * 2);
			if (inf->argv)
			{
				inf->argv[0] = _strdup(inf->arg);
				inf->argv[1] = NULL;
			}
		}
		for (i = 0; inf->argv && inf->argv[i]; i++)
			;
		inf->argc = i;

		rep_alias(inf);
		rep_vars(inf);
	}
}

/**
 * free_inf - frees info_t
 * @inf: struct address
 * @allf: true if freeing all fields
 */
void free_inf(info_t *inf, int allf)
{
	ffree(inf->argv);
	inf->argv = NULL;
	inf->path = NULL;
	if (allf)
	{
		if (!inf->cmd_buff)
			free(inf->arg);
		if (inf->env)
			free_l(&(inf->env));
		if (inf->history)
			free_l(&(inf->history));
		if (inf->alias)
			free_l(&(inf->alias));
		ffree(inf->environ);
			inf->environ = NULL;
		bfree((void **)inf->cmd_buff);
		if (inf->readfd > 2)
			close(inf->readfd);
		_putchar(BUF_FLUSH);
	}
}

