#include "shell.h"

/**
 * input_buff - bufffers chained commands
 * @inf: parameter struct
 * @buff: address
 * @leng: address
 *
 * Return: bytes
 */
ssize_t input_buff(info_t *inf, char **buff, size_t *leng)
{
	ssize_t t = 0;
	size_t len_p = 0;

	if (!*leng) /* if nothing left in the bufffer, fill it */
	{
		/*bfree((void **)inf->cmd_buff);*/
		free(*buff);
		*buff = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		t = getline(buff, &len_p, stdin);
#else
		t = _getline(inf, buff, &len_p);
#endif
		if (t > 0)
		{
			if ((*buff)[t - 1] == '\n')
			{
				(*buff)[t - 1] = '\0'; /* remove trailing newline */
				t--;
			}
			inf->lc_f = 1;
			remove_comments(*buff);
			build_h_l(inf, *buff, inf->histcount++);
			/* if (_strchr(*buff, ';')) is this a command chain? */
			{
				*leng = t;
				inf->cmd_buff = buff;
			}
		}
	}
	return (t);
}

/**
 * get_input - gets a line minus the newline
 * @inf: parameter struct
 *
 * Return: bytes read
 */
ssize_t get_input(info_t *inf)
{
	static char *buff; /* the ';' command chain bufffer */
	static size_t i, j, leng;
	ssize_t t = 0;
	char **buff_p = &(inf->arg), *b;

	_putchar(BUF_FLUSH);
	t = input_buff(inf, &buff, &leng);
	if (t == -1) /* EOF */
		return (-1);
	if (leng)	/* we have commands left in the chain bufffer */
	{
		j = i; /* init new iterator to current buff position */
		b = buff + i; /* get pointer for return */

		check_chain(inf, buff, &j, i, leng);
		while (j < leng) /* iterate to semicolon or end */
		{
			if (my_chain(inf, buff, &j))
				break;
			j++;
		}

		i = j + 1; /* increment past nulled ';'' */
		if (i >= leng) /* reached end of bufffer? */
		{
			i = leng = 0; /* reset position and length */
			inf->cmd_b_t = CMD_NORM;
		}

		*buff_p = b; /* pass bacq pointer to current command position */
		return (_strlen(b)); /* return length of current command */
	}

	*buff_p = buff; /* else not a chain, pass bacq bufffer from _getline() */
	return (t); /* return length of bufffer from _getline() */
}

/**
 * read_buff - reads a bufffer
 * @inf: parameter struct
 * @buff: bufffer
 * @i: size
 *
 * Return: t
 */
ssize_t read_buff(info_t *inf, char *buff, size_t *i)
{
	ssize_t t = 0;

	if (*i)
		return (0);
	t = read(inf->readfd, buff, READ_BUF_SIZE);
	if (t >= 0)
		*i = t;
	return (t);
}

/**
 * _getline - gets the next line of input from STDIN
 * @inf: parameter struct
 * @ptr: address of pointer to bufffer, preallocated or NULL
 * @length: size of preallocated ptr bufffer if not NULL
 *
 * Return: s
 */
int _getline(info_t *inf, char **ptr, size_t *length)
{
	static char buff[READ_BUF_SIZE];
	static size_t i, leng;
	size_t q;
	ssize_t t = 0, s = 0;
	char *b = NULL, *new_b = NULL, *c;

	b = *ptr;
	if (b && length)
		s = *length;
	if (i == leng)
		i = leng = 0;

	t = read_buff(inf, buff, &leng);
	if (t == -1 || (t == 0 && leng == 0))
		return (-1);

	c = _strchar(buff + i, '\n');
	q = c ? 1 + (unsigned int)(c - buff) : leng;
	new_b = _realloc(b, s, s ? s + q : q + 1);
	if (!new_b) /* MALLOC FAILURE! */
		return (b ? free(b), -1 : -1);

	if (s)
		_strncat(new_b, buff + i, q - i);
	else
		_strncpy(new_b, buff + i, q - i + 1);

	s += q - i;
	i = q;
	b = new_b;

	if (length)
		*length = s;
	*ptr = b;
	return (s);
}

/**
 * sigintHandler - blocqs ctrl-C
 * @signal_n: the signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int signal_n)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}

