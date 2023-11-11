#include "shell.h"

/**
 * hsh - main shell loop
 * @inf: the parameter & return info struct
 * @argvect: the argument vector
 *
 * Return: 0 else 1 on error, or error code
 */
int hsh(info_t *inf, char **argvect)
{
	ssize_t t = 0;
	int builtin_r = 0;

	while (t != -1 && builtin_r != -2)
	{
		clear_inf(inf);
		if (inter(inf))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		t = get_input(inf);
		if (t != -1)
		{
			set_inf(inf, argvect);
			builtin_r = f_builtin(inf);
			if (builtin_r == -1)
				f_cmd(inf);
		}
		else if (inter(inf))
			_putchar('\n');
		free_inf(inf, 0);
	}
	write_h(inf);
	free_inf(inf, 1);
	if (!inter(inf) && inf->status)
		exit(inf->status);
	if (builtin_r == -2)
	{
		if (inf->err_num == -1)
			exit(inf->status);
		exit(inf->err_num);
	}
	return (builtin_r);
}

/**
 * f_builtin - finds a builtin command
 * @inf: the parameter & return inf struct
 *
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */
int f_builtin(info_t *inf)
{
	int i, builtinr = -1;
	builtin_t builtint[] = {
		{"exit", _ourexit},
		{"env", _ourenv},
		{"help", _ourhelp},
		{"history", _ourhistory},
		{"setenv", _oursetenv},
		{"unsetenv", _ourunsetenv},
		{"cd", _ourcd},
		{"alias", _ouralias},
		{NULL, NULL}
	};

	for (i = 0; builtint[i].type; i++)
		if (_strcmp(inf->argv[0], builtint[i].type) == 0)
		{
			inf->l_h++;
			builtinr = builtint[i].func(inf);
			break;
		}
	return (builtinr);
}

/**
 * f_cmd - finds a command in path
 * @inf: the parameter & return info struct
 *
 * Return: void
 */
void f_cmd(info_t *inf)
{
	char *path = NULL;
	int i, q;

	inf->path = inf->argv[0];
	if (inf->lc_f == 1)
	{
		inf->l_h++;
		inf->lc_f = 0;
	}
	for (i = 0, q = 0; inf->arg[i]; i++)
		if (!delim(inf->arg[i], " \t\n"))
			q++;
	if (!q)
		return;

	path = f_path(inf, _getenv(inf, "PATH="), inf->argv[0]);
	if (path)
	{
		inf->path = path;
		fork_cmd(inf);
	}
	else
	{
		if ((inter(inf) || _getenv(inf, "PATH=")
			|| inf->argv[0][0] == '/') && my_cmd(inf, inf->argv[0]))
			fork_cmd(inf);
		else if (*(inf->arg) != '\n')
		{
			inf->status = 127;
			print_error(inf, "not found\n");
		}
	}
}

/**
 * fork_cmd - forks to run cmd
 * @inf: parameter and info struct
 *
 * Return: void
 */
void fork_cmd(info_t *inf)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(inf->path, inf->argv, get_environ(inf)) == -1)
		{
			free_inf(inf, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(inf->status));
		if (WIFEXITED(inf->status))
		{
			inf->status = WEXITSTATUS(inf->status);
			if (inf->status == 126)
				print_error(inf, "Permission denied\n");
		}
	}
}
