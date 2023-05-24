#include "shell.h"

/**
 * bfree - this function frees a pointer
 * @ptr: address of the pointer argument
 * Return: 1 if freed, otherwise 0.
 */
int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
