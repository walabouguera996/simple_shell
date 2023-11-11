#include "shell.h"

/**
 * main - entry point
 * @argcount: arg count
 * @argvect: arg vector
 *
 * Return: 0 or 1 on error
 */
int main(int argcount, char **argvect)
{
	info_t inf[] = { INFO_INIT };
	int fd = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fd)
		: "r" (fd));

	if (argcount == 2)
	{
		fd = open(argvect[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputstr(argvect[0]);
				_eputstr(": 0: Can't open ");
				_eputstr(argvect[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		inf->readfd = fd;
	}
	populate_env_l(inf);
	read_h(inf);
	hsh(inf, argvect);
	return (EXIT_SUCCESS);
}

