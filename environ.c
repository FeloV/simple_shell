#include "shell.h"

/**
 * _myenv - this function displays the current environment
 * @info: Structure argument
 * Return: Always 0
 */
int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _getenv - the function that gets the value of an env variable
 * @info: Structure argument
 * @name: env var name
 * Return: the value
 */
char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *ptr;

	while (node)
	{
		ptr = starts_with(node->str, name);
		if (ptr && *ptr)
			return (ptr);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - the function that Initialize a new environment variable
 * @info: Structure argument
 *  Return: Always 0
 */
int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - the function that Remove an environment variable
 * @info: Structure argument.
 * Return: Always 0
 */
int _myunsetenv(info_t *info)
{
	int k;

	if (info->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (k = 1; k <= info->argc; k++)
		_unsetenv(info, info->argv[k]);

	return (0);
}

/**
 * populate_env_list - populates env linked list
 * @info: Structure argument
 * Return: Always 0
 */
int populate_env_list(info_t *info)
{
	size_t k;
	list_t *node = NULL;

	for (k = 0; environ[k]; k++)
		add_node_end(&node, environ[k], 0);
	info->env = node;
	return (0);
}
