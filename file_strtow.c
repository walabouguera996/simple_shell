#include "shell.h"

/**
 * **strtow - splits a string  Repeat delimiters are ignored
 * @str: string
 * @deli: delimeter
 * Return: pointer  or NULL on failure
 */

char **strtow(char *str, char *deli)
{
	int i, j, q, m, nw = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!deli)
		deli = " ";
	for (i = 0; str[i] != '\0'; i++)
		if (!delim(str[i], deli) && (delim(str[i + 1], deli) || !str[i + 1]))
			nw++;

	if (nw == 0)
		return (NULL);
	s = malloc((1 + nw) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < nw; j++)
	{
		while (delim(str[i], deli))
			i++;
		q = 0;
		while (!delim(str[i + q], deli) && str[i + q])
			q++;
		s[j] = malloc((q + 1) * sizeof(char));
		if (!s[j])
		{
			for (q = 0; q < j; q++)
				free(s[q]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < q; m++)
			s[j][m] = str[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}

/**
 * **strtow2 - splits a string
 * @str: string
 * @deli:  delimeter
 * Return: a pointer or NULL on failure
 */
char **strtow2(char *str, char deli)
{
	int i, j, q, m, nw = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
		if ((str[i] != deli && str[i + 1] == deli) ||
		    (str[i] != deli && !str[i + 1]) || str[i + 1] == deli)
			nw++;
	if (nw == 0)
		return (NULL);
	s = malloc((1 + nw) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < nw; j++)
	{
		while (str[i] == deli && str[i] != deli)
			i++;
		q = 0;
		while (str[i + q] != deli && str[i + q] && str[i + q] != deli)
			q++;
		s[j] = malloc((q + 1) * sizeof(char));
		if (!s[j])
		{
			for (q = 0; q < j; q++)
				free(s[q]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < q; m++)
			s[j][m] = str[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}

