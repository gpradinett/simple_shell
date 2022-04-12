#include "shell.h"

/**
 *sl_exit - shell built in Exit
 *@commands: an array of command arguments
 *@buffer: a buffer for reading in commands, passed
 *here to be freed
 *Return: exit status
 */

int sl_exit(char **commands, char *buffer)
{
	if (commands[1])
	{
		int i = _atoi(commands[1]);

		if (i == -1)
		{
			write(1, "Illegal number\n", 15);
			return (1);
		}
		free(buffer);
		free_d_ptr(commands);
		exit(i);
	}
	free(buffer);
	free_d_ptr(commands);
	exit(0);
}

/**
 * sl_env - prints current enviroment
 * @commands: array of commands
 * @buffer: passed for freeing if exit
 * Return: 1
 */

int sl_env(char **commands, char *buffer)
{
	int i;
	unsigned int varsize;

	(void)commands;
	(void)buffer;
	for (i = 0; __environ[i]; i++)
	{
		if (i > 0)
			write(1, "\n", 1);
		varsize = _strlen(__environ[i]);
		write(1, __environ[i], varsize);
	}
	write(1, "\n", 1);
	return (1);
}

/**
 *checkbuiltins - checks to see if is built in command
 *@str: command being checked
 *Return: 1 if builtin, 0 if not
 */

int checkbuiltins(char *str)
{
	if (_strcmp("exit", str) == 0)
		return (1);
	if (_strcmp("env", str) == 0)
		return (1);
	return (0);
}
