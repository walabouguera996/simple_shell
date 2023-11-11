#include "shell.h"

/**
 * _strcpy - copies a string
 * @dest: destination
 * @src: source
 *
 * Return: pointer
 */
char *_strcpy(char *dest, char *src)
{
	int i = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}

/**
 *_strdup - duplicates a string.
 * @str:  string.
 *
 * Return: pointer.
 */
char *_strdup(const char *str)
{
	int len = 0;
	char *r;

	if (str == NULL)
		return (NULL);
	while (*str++)
		len++;
	r = malloc(sizeof(char) * (len + 1));
	if (!r)
		return (NULL);
	for (len++; len--;)
		r[len] = *--str;
	return (r);
}

/**
 *_puts - prints an input string
 *@str:  string
 *
 * Return: void
 */
void _puts(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_putchar(str[i]);
		i++;
	}
}

/**
 * _putchar - writes the character c to stdout
 * @c: character.
 *
 * Return: 1 or -1
 */
int _putchar(char c)
{
	static int i;
	static char buff[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buff, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buff[i++] = c;
	return (1);
}

