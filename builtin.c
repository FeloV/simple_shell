#include "shell.h"

/**
 * _myexit - the function that exits the shell
 * @info: Structure argument
 * Return: exits with a given exit status
 * (0) if info.argv[0] != "exit"
 */
int _myexit(info_t *info)
{
	int e;

	if (info->argv[1])
	{
		e = _erratoi(info->argv[1]);
		if (e == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = _erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _mycd - the function thatchanges the current directory
 * @info: Structure argument
 * Return: Always 0
 */
int _mycd(info_t *info)
{
	char *s;
	char *dir, buffer[1024];
	int cr;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = _getenv(info, "HOME=");
		if (!dir)
			cr = /* TODO: what should this be? */
				chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
		else
			cr = chdir(dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		cr = /* TODO: what should this be? */
			chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
	}
	else
		cr = chdir(info->argv[1]);
	if (cr == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _myhelp - the fun. that changes the current directory
 * @info: Structure argument
 * Return: Always 0
 */
int _myhelp(info_t *info)
{
	char **arg;

	arg = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg);
	return (0);
}
