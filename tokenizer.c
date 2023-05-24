#include "shell.h"

/**
 * **strtow - this function divides a string into words.
 * @str: the given string argument
 * @d: delimeter argument passed to the function
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **strtow(char *str, char *d)
{
	int i, j, k, m, numwords = 0;
	char **f;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (i = 0; str[i] != '\0'; i++)
		if (!is_delim(str[i], d) && (is_delim(str[i + 1], d) || !str[i + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	f = malloc((1 + numwords) * sizeof(char *));
	if (!f)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (is_delim(str[i], d))
			i++;
		k = 0;
		while (!is_delim(str[i + k], d) && str[i + k])
			k++;
		f[j] = malloc((k + 1) * sizeof(char));
		if (!f[j])
		{
			for (k = 0; k < j; k++)
				free(f[k]);
			free(f);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			f[j][m] = str[i++];
		f[j][m] = 0;
	}
	f[j] = NULL;
	return (f);
}

/**
 * **strtow2 - the function that divides string into words
 * @str: the given string argument
 * @d: the delimeter argument
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **strtow2(char *str, char d)
{
	int i, j, k, m, numwords = 0;
	char **f;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
		if ((str[i] != d && str[i + 1] == d) ||
				    (str[i] != d && !str[i + 1]) || str[i + 1] == d)
			numwords++;
	if (numwords == 0)
		return (NULL);
	f = malloc((1 + numwords) * sizeof(char *));
	if (!f)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (str[i] == d && str[i] != d)
			i++;
		k = 0;
		while (str[i + k] != d && str[i + k] && str[i + k] != d)
			k++;
		f[j] = malloc((k + 1) * sizeof(char));
		if (!f[j])
		{
			for (k = 0; k < j; k++)
				free(f[k]);
			free(f);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			f[j][m] = str[i++];
		f[j][m] = 0;
	}
	f[j] = NULL;
	return (f);
}

