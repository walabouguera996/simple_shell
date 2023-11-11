#include "shell.h"

/**
 * _strlen - the length of a string
 * @s: the string
 *
 * Return: integer
 */
int _strlen(char *s)
{
	int i = 0;

	if (!s)
		return (0);

	while (*s++)
		i++;
	return (i);
}

/**
 * _strcmp - performs lexicogarphic comparison of two strangs.
 * @s1: string 1
 * @s2:  string 2
 *
 * Return: negative if s1 < s2, positive if s1 > s2, null if s1 == s2
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * starts_with - checks if stf starts with sts
 * @sts: string to search
 * @stf: the substring to find
 *
 * Return: address of next char of sts or NULL
 */
char *starts_with(const char *sts, const char *stf)
{
	while (*stf)
		if (*stf++ != *sts++)
			return (NULL);
	return ((char *)sts);
}

/**
 * _strcat - concatenates two strings
 * @dest:  destination
 * @src:  source
 *
 * Return: pointer
 */
char *_strcat(char *dest, char *src)
{
	char *r = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (r);
}

