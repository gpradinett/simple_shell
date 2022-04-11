#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "shell.h"
#include "source.h"
#include "parser.h"
#include "executor.h"

/*
 * _getline: The first function prints the prompt string.
 * print_prompt1(): reads the next line of input
 *
 */

int main(int argc, char **argv)
{
	char *cmd;

	do

	{
	/*first prints the shell's prompt*/
	print_prompt1();
	/*then we read a command*/
	cmd = _getline();
	/*If there's an error reading the command, we exit the shell.*/
	if (!cmd)
	{
		exit(EXIT_SUCCESS);
	}
	/*If the command is empty, we skip this input and continue with the loop*/
	if (cmd[0] == '\0' || strcmp(cmd, "\n") == 0)
	{
		free(cmd);
		continue;
	}
	/* If the command is exit, we exit the shell,*/
	/* Otherwise, we echo back the command,*/
	/* free the memory we used to store the command, and continue with the loop*/
	if (strcmp(cmd, "exit\n") == 0)
	{
		free(cmd);
		break;
	}
	/* printf("%s", cmd);*/
	struct source_s src;

	src.buffer   = cmd;
	src.bufsize  = strlen(cmd);
	src.curpos   = INIT_SRC_POS;
	parse_and_execute(&src);
	free(cmd);

	} while (1);

	exit(EXIT_SUCCESS);
}
