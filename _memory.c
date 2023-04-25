#include "header.h"

/**
 * sfree - frees a pointer and NULLs the address
 * @ptr: address
 * Return: 1 if freed, otherwise 0.
 */
int sfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
