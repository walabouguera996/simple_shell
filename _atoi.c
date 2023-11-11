#include "shell.h"

/**
 * inter - returns true if shell is interactive
 * @inf: struct address
 *
 * Return: 1 if inter else 0
 */
int inter(info_t *inf)
{
	return (isatty(STDIN_FILENO) && inf->readfd <= 2);
}

/**
 * delim - checks if character is a delimeter or not
 * @c: character
 * @delimeter: string
 * Return: 1 if true and 0 if false
 */
int delim(char c, char *delimeter)
{
	while (*delimeter)
		if (*delimeter++ == c)
			return (1);
	return (0);
}

/**
 *_alpha - checks for alphabetic character
 *@c: character
 *Return: 1
 */

int _alpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *_atoi - converts a string to an integer
 *@s: string
 *Return: int
 */

int _atoi(char *s)
{
	int i, x = 1, y = 0, z;
	unsigned int result = 0;

	for (i = 0;  s[i] != '\0' && y != 2; i++)
	{
		if (s[i] == '-')
			x *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			y = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (y == 1)
			y = 2;
	}

	if (x == -1)
		z = -result;
	else
		z = result;

	return (z);
}
