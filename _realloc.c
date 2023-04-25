#include "simple_shell.h"

/**
 * realloc - reallocates
 *@ptr: pointer
 *@old_size: size of previous block
 *@new_size: size of new block
 *Return: pointer to da ol'block nameen.
 */
void *realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	p = malloc(new_size);
	if (!p)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (p);
}

/**
 * memset - memory with a constant byte
 *@s: pointer to the memory area
 *@b: byte to fill *s with
 *@n: bytes to be filled
 *Return: (s) a pointer to the memory area s
 */
char *memset(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s[i] = b;
	return (s);
}

/**
 * tfree - frees a string of strings
 *@pp: string of strings
 */
void tfree(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a);
}
