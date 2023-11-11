#include "shell.h"

/**
 * _ourexit - exits the shell
 * @inf: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: exits with a given exit status
 *         (0) if inf.argv[0] != "exit"
 */
int _ourexit(info_t *inf)
{
	int chdir;

	if (inf->argv[1])  /* If there is an exit arguement */
	{
		chdir = _erroratoi(inf->argv[1]);
		if (chdir == -1)
		{
			inf->status = 2;
			print_error(inf, "Illegal number: ");
			_eputstr(inf->argv[1]);
			_eputchar('\n');
			return (1);
		}
		inf->err_num = _erroratoi(inf->argv[1]);
		return (-2);
	}
	inf->err_num = -1;
	return (-2);
}

/**
 * _ourcd - changes the current directory of the process
 * @inf: constant function prototype.
 *  Return: 0
 */
int _ourcd(info_t *inf)
{
	char *s, *d, buffer[1024];
	int w;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!inf->argv[1])
	{
		d = _getenv(inf, "HOME=");
		if (!d)
			w = /* TODO: what should this be? */
				chdir((d = _getenv(inf, "PWD=")) ? d : "/");
		else
			w = chdir(d);
	}
	else if (_strcmp(inf->argv[1], "-") == 0)
	{
		if (!_getenv(inf, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(inf, "OLDPWD=")), _putchar('\n');
		w = /* TODO: what should this be? */
			chdir((d = _getenv(inf, "OLDPWD=")) ? d : "/");
	}
	else
		w = chdir(inf->argv[1]);
	if (w == -1)
	{
		print_error(inf, "can't cd to ");
		_eputstr(inf->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(inf, "OLDPWD", _getenv(inf, "PWD="));
		_setenv(inf, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _ourhelp - changes the current dectory of the process
 * @inf: constant function prototype.
 *  Return: Always 0
 */
int _ourhelp(info_t *inf)
{
	char **arg_array;

	arg_array = inf->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_array); /* temp att_unused workaround */
	return (0);
}
