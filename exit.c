#include "header.h"

/**
 **_strchr - character in a string
 *@d: string to parse
 *@e: character to find
 *Return: (s) a pointer to the memory area s
 */
char *_strchr(char *d, char e)
{
	do {
		if (*d == e)
			return (d);
	} while (*d++ != '\0');

	return (NULL);
}

/**
 **_strncpy - to copy a string
 *@dest: to be copied to
 *@src: to copy from
 *@n: characters to be copied
 *Return: the concatenated string
 */
char *_strncpy(char *dest, char *src, int n)
{
	int i, j;
	char *c = dest;

	i = 0;
	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (c);
}

/**
 **_strncat - concatenates the strings
 *@dest: string one
 *@src: string two
 *@n: bytes to be used
 *Return: the concatenated string
 */
char *_strncat(char *dest, char *src, int n)
{
	int i, j;
	char *c = dest;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0' && j < n)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	if (j < n)
		dest[i] = '\0';
	return (c);
}
