#include "shell.h"

/**
 * _erroratoi - string to integer
 * @s: string
 * Return:int else -1 on error
 */
int _erroratoi(char *s)
{
	int i = 0;
	unsigned long int k = 0;

	if (*s == '+')
		s++;  /* TODO: why does this make main return 255? */
	for (i = 0;  s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			k *= 10;
			k += (s[i] - '0');
			if (k > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (k);
}

/**
 * print_error - prints an error message
 * @inf:  inf struct
 * @errorstr: error type
 * Return: int else -1 on error
 */
void print_error(info_t *inf, char *errorstr)
{
	_eputstr(inf->fname);
	_eputstr(": ");
	print_decimal(inf->l_h, STDERR_FILENO);
	_eputstr(": ");
	_eputstr(inf->argv[0]);
	_eputstr(": ");
	_eputstr(errorstr);
}

/**
 * print_decimal - prints a decimal n
 * @input: the input
 * @fd: file descriptor
 *
 * Return: int
 */
int print_decimal(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int i, h = 0;
	unsigned int _abs_, cur;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		h++;
	}
	else
		_abs_ = input;
	cur = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + cur / i);
			h++;
		}
		cur %= i;
	}
	__putchar('0' + cur);
	h++;

	return (h);
}

/**
 * convert_num - converter function, a clone of itoa
 * @n: integer
 * @base: base
 * @y: argument flag
 *
 * Return: string
 */
char *convert_num(long int n, int base, int y)
{
	static char *arr;
	static char bufffer[50];
	char x = 0;
	char *ptr;
	unsigned long nm = n;
		if (!(y & CONVERT_UNSIGNED) && n < 0)
	{
		nm = -n;
		x = '-';

	}
	arr = y & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &bufffer[49];
	*ptr = '\0';

	do	{
		*--ptr = arr[nm % base];
		nm /= base;
	} while (nm != 0);

	if (x)
		*--ptr = x;
	return (ptr);
}

/**
 * remove_comments - function replaces '#' with '\0'
 * @buff: address
 *
 * Return: 0
 */
void remove_comments(char *buff)
{
	int i;

	for (i = 0; buff[i] != '\0'; i++)
		if (buff[i] == '#' && (!i || buff[i - 1] == ' '))
		{
			buff[i] = '\0';
			break;
		}
}
