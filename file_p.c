#include "shell.h"

/**
 * my_cmd - determines if a file is an executable command
 * @inf: the info struct
 * @path: path
 *
 * Return: 1 if true else 0
 */
int my_cmd(info_t *inf, char *path)
{
	struct stat st;

	(void)inf;
	if (path == NULL || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dupli_chars - duplicates characters
 * @paths: the PATH string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer
 */
char *dupli_chars(char *paths, int start, int stop)
{
	static char buff[1024];
	int i = 0, q = 0;

	for (q = 0, i = start; i < stop; i++)
		if (paths[i] != ':')
			buff[q++] = paths[i];
	buff[q] = 0;
	return (buff);
}

/**
 * f_path - finds this cmd in the path string
 * @inf: the info struct
 * @paths: the path string
 * @cmd: the cmd to find
 *
 * Return: path of cmd or NULL
 */
char *f_path(info_t *inf, char *paths, char *cmd)
{
	int i = 0, c_p = 0;
	char *path;

	if (!paths)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (my_cmd(inf, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!paths[i] || paths[i] == ':')
		{
			path = dupli_chars(paths, c_p, i);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (my_cmd(inf, path))
				return (path);
			if (!paths[i])
				break;
			c_p = i;
		}
		i++;
	}
	return (NULL);
}
