#include "shell.h"

/**
 * _strlen - the function that retuns no. of chars
 * @s: the string argument passed to the function
 *
 * Return: the no. of character in a string
 */
int _strlen(char *s)
{
	int k = 0;

	if (!s)
		return (0);

	while (*s++)
		k++;
	return (k);
}

/**
 * _strcmp - performs lexicogarphic comparision.
 * @s1: the first string argument
 * @s2: the second string argument
 * Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
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
 * starts_with - checks if needle starts with haystack
 * @haystack: string to search
 * @needle: the substring to find
 *
 * Return: address of next char of haystack or NULL
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _strcat - the function that adds two strings together
 * @dest: the first string
 * @src: the second string
 * Return: points to the dest buffer
 */
char *_strcat(char *dest, char *src)
{
	char *y = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (y);
}

