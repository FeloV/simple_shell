#include "shell.h"

/**
 * hsh - the function that performs the shell iteration
 * @info: the first parameter
 * @av: the second parameter
 *
 * Return: it returns 0 on success else 1
 */
int hsh(info_t *info, char **av)
{
	int br = 0;
	ssize_t i;

	for (i = 0; i != -1 && br != -2;)
	{
		clear_info(info);
		if (interactive(info))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		i = get_input(info);
		if (i != -1)
		{
			set_info(info, av);
			br = find_builtin(info);
			if (br == -1)
				find_cmd(info);
		}
		else if (interactive(info))
			_putchar('\n');
		free_info(info, 0);
	}
	write_history(info);
	free_info(info, 1);
	if (!interactive(info) && info->status)
		exit(info->status);
	if (br == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (br);
}

/**
 * find_builtin - the function that searchs default commands
 * @info: an argument that returns struct
 *
 * Return: returns -1 if command not found, 1 if command found not successfull
 * 	0 if builtin executed successfully,
 * 	2 if builtin signals exit()
 */
int find_builtin(info_t *info)
{
	int k = 0;
	int br = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	while (builtintbl[k].type)
		if (_strcmp(info->argv[0], builtintbl[k].type) == 0)
		{
			info->line_count++;
			br = builtintbl[k].func(info);
			break;
		}
		k++;
	return (br);
}

/**
 * find_cmd - the function that searchs command in PATH
 * @info: the argument passed to the function
 * Return: doen't have return value
 */
void find_cmd(info_t *info)
{
	char *path = NULL;
	int i;
	int j;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (i = 0, j = 0; info->arg[i]; i++)
		if (!is_delim(info->arg[i], " \t\n"))
			j++;
	if (!j)
		return;

	path = find_path(info, _getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_cmd(info);
	}
	else
	{
		if ((interactive(info) || _getenv(info, "PATH=")
					|| info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
			fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}

/**
 * fork_cmd - the functions that forks an exec
 * @info: the argument passed to the function
 * Return: does'nt have return value
 */
void fork_cmd(info_t *info)
{
	pid_t cpi;

	cpi = fork();
	if (cpi == -1)
	{
		perror("Error:");
		return;
	}
	if (cpi == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}

