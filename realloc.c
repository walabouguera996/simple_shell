#include "shell.h"

/**
 **_memset - fills memory with a constant byte
 *@s: the pointer
 *@byte: the byte
 *@n: int
 *Return: pointer
 */
char *_memset(char *s, char byte, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s[i] = byte;
	return (s);
}

/**
 * ffree - frees a string of strings
 * @ss: string of strings
 */
void ffree(char **ss)
{
	char **a = ss;

	if (!ss)
		return;
	while (*ss)
		free(*ss++);
	free(a);
}

/**
 * _realloc - reallocates a block of memory
 * @ptr: pointer
 * @o_size: size of byte for old block
 * @n_size: size of byte for new block
 *
 * Return: pointer
 */
void *_realloc(void *ptr, unsigned int o_size, unsigned int n_size)
{
	char *b;

	if (!ptr)
		return (malloc(n_size));
	if (!n_size)
		return (free(ptr), NULL);
	if (n_size == o_size)
		return (ptr);

	b = malloc(n_size);
	if (!b)
		return (NULL);

	o_size = o_size < n_size ? o_size : n_size;
	while (o_size--)
		b[o_size] = ((char *)ptr)[o_size];
	free(ptr);
	return (b);
}

