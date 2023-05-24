#include "shell.h"

/**
 * _strcpy - the function that duplicates string
 * @dest: the destination string argument
 * @src: the source string argument
 * Return: points to the destination address
 */
char *_strcpy(char *dest, char *src)
{
	int j = 0;

	if (dest == src || src == 0)
		return (dest);
	for (; src[j];)
	{
		dest[j] = src[j];
		j++;
	}
	dest[j] = 0;
	return (dest);
}

/**
 * _strdup - the function that replicates string
 * @str: the string argument passed to the function
 * Return: points to the address of replicated str
 */
char *_strdup(const char *str)
{
	char *r;
	int l = 0;

	if (str == NULL)
		return (NULL);
	while (*str++)
		l++;
	r = malloc(sizeof(char) * (l + 1));
	if (!r)
		return (NULL);
	for (l++; l--;)
		r[l] = *--str;
	return (r);
}

/**
 * _puts - the function that displays an input string
 * @str: the string argument passed to the fun
 *
 * Return: void
 */
void _puts(char *str)
{
	int j = 0;

	if (!str)
		return;
	while (str[j] != '\0')
	{
		_putchar(str[j]);
		j++;
	}
}

/**
 * _putchar - this function writes c to stdout
 * @c: character argument passed to fun
 * Return: On success 1.
 * On error, -1 is returned.
 */
int _putchar(char c)
{
	static int k;
	static char b[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || k >= WRITE_BUF_SIZE)
	{
		write(1, b, k);
		k = 0;
	}
	if (c != BUF_FLUSH)
		b[k++] = c;
	return (1);
}

