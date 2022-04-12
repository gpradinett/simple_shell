#include "shell.h"
/**
 *sigintHandler - makes it so shell does not end on ^C
 *@sig_num: signal reference
 *Return: void no return
 */

void sigintHandler(int sig_num)
{
	(void)sig_num;
	signal(SIGINT, sigintHandler);
	write(1, "\n$ ", 3);
}
/**
 *runexe - runs an executable file
 *@commands: an array of arguments
 *Return: 0 on success
 */

int runexe(char **commands)
{
	pid_t child;
	int status;
	char *no_dir = commands[0];

	{
		commands[0] = get_file_path(commands[0]);
		if (access(no_dir, X_OK) == 0 && commands[0] == NULL)
		{
			free(commands[0]);
			commands[0] = no_dir;
		}
		else
			free(no_dir);
	}
	if (commands[0] != NULL)
	{       child = fork();
		if (child == -1)
		{       write(1, "Fork Failed\n", 12);
			return (1);             }
		else if (child == 0)
		{
			execve(commands[0], commands, __environ);
		}
		else
			wait(&status);  }
	return (0);
}

/**
 *runcommand - takes the command lines and runs the appropriate function
 *@commands: command line
 *@buffer: the buffer for commands, passed here to be freed if exit is used
 *Return: Either a function call or NULL
 */

int (*runcommand(char **commands, char *buffer))(char **, char *)
{
	bi_t bia[] = {
		{"exit", sl_exit},
		{"env", sl_env},
		{NULL, NULL}
	};
	int i, bic = 2;

	if (buffer == NULL)
		buffer = " ";
	for (i = 0; i < bic; i++)
	{
		if (_strcmp(commands[0], bia[i].bi) == 0)
			return (bia[i].f);
	}
	return (NULL);
}

/**
 *cnf - prints error message if command not found
 *@pn: program name (av[0])
 *@cn: command name (commands[0])
 *@i: command number
 *Return: void no return
 */

void cnf(char *pn, char *cn, int i)
{

	char *stri = "nil";

	stri = _itoa(stri, i);
	write(STDERR_FILENO, pn, _strlen(pn));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, stri, _strlen(stri));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, cn, _strlen(cn));
	write(STDERR_FILENO, ": not found\n", 12);
	free(stri);
}

/**
 *main - entry point for the shell Sherlock
 *@ac: number of arguments
 *@av: array of arguments
 *@env: the enviroment
 *Return: 0
 */

int main(int ac, char **av, char **env)
{
	int fb = 0, i = 1;
	size_t bufsize = 1024;
	char *buf, **coms, *pn = av[0], *cn;

	signal(SIGINT, sigintHandler);
	while (1)
	{
		buf = (char *)malloc(bufsize * sizeof(char));
		if (buf == NULL)
			exit(1);
		if (isatty(STDIN_FILENO))
			write(1, "$ ", 2);
		fb = getline(&buf, &bufsize, stdin);
		if (fb == EOF)
		{	free(buf);
			exit(0); }
		if (isatty(STDIN_FILENO))
			buf = watson(buf);
		if (*buf == '\n')
			free(buf);
		else
		{	coms = sherlock(buf, " ");
			if (checkbuiltins(coms[0]) == 1)
				(*runcommand(coms, buf))(coms, buf);
			else
			{	cn = _strdup(coms[0]);
				runexe(coms);
				if (coms[0] == NULL)
					cnf(pn, cn, i);
				free(cn); }
			free(buf);
			free_d_ptr(coms); }
		i++;
	}
	(void)ac;
	(void)env;
	return (0);
}
