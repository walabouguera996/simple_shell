#include "shell.h"

/**
 * get_h_f - gets the history file
 * @inf: parameter struct
 *
 * Return: allocated string containg history file
 */

char *get_h_f(info_t *inf)
{
	char *buff, *dir;

	dir = _getenv(inf, "HOME=");
	if (!dir)
		return (NULL);
	buff = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!buff)
		return (NULL);
	buff[0] = 0;
	_strcpy(buff, dir);
	_strcat(buff, "/");
	_strcat(buff, HIST_FILE);
	return (buff);
}

/**
 * write_h - creates a file, or appends to an existing file
 * @inf: parameter
 *
 * Return: 1 , else -1
 */
int write_h(info_t *inf)
{
	ssize_t fd;
	char *fn = get_h_f(inf);
	list_t *node = NULL;

	if (!fn)
		return (-1);

	fd = open(fn, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(fn);
	if (fd == -1)
		return (-1);
	for (node = inf->history; node; node = node->next)
	{
		_putstrfd(node->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_h - reads history from file
 * @inf: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int read_h(info_t *inf)
{
	int i, last = 0, lc = 0;
	ssize_t fd, rdlen, fs = 0;
	struct stat st;
	char *buff = NULL, *fn = get_h_f(inf);

	if (!fn)
		return (0);

	fd = open(fn, O_RDONLY);
	free(fn);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fs = st.st_size;
	if (fs < 2)
		return (0);
	buff = malloc(sizeof(char) * (fs + 1));
	if (!buff)
		return (0);
	rdlen = read(fd, buff, fs);
	buff[fs] = 0;
	if (rdlen <= 0)
		return (free(buff), 0);
	close(fd);
	for (i = 0; i < fs; i++)
		if (buff[i] == '\n')
		{
			buff[i] = 0;
			build_h_l(inf, buff + last, lc++);
			last = i + 1;
		}
	if (last != i)
		build_h_l(inf, buff + last, lc++);
	free(buff);
	inf->histcount = lc;
	while (inf->histcount-- >= HIST_MAX)
		delete_n_at_index(&(inf->history), 0);
	renumber_h(inf);
	return (inf->histcount);
}

/**
 * build_h_l - adds entry to a history linked list
 * @inf: Structure containing potential arguments. Used to maintain
 * @buff: bufffer
 * @lc: the history linecount, histcount
 *
 * Return: 0
 */
int build_h_l(info_t *inf, char *buff, int lc)
{
	list_t *node = NULL;

	if (inf->history)
		node = inf->history;
	add_n_e(&node, buff, lc);

	if (!inf->history)
		inf->history = node;
	return (0);
}

/**
 * renumber_h - renumbers the history linked list after changes
 * @inf: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */
int renumber_h(info_t *inf)
{
	list_t *node = inf->history;
	int i = 0;

	while (node)
	{
		node->n = i++;
		node = node->next;
	}
	return (inf->histcount = i);
}
