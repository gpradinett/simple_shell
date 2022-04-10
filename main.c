#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "shell.h"

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
        if(!cmd)
        {
            exit(EXIT_SUCCESS);
        }

        if(cmd[0] == '\0' || strcmp(cmd, "\n") == 0)
        {
            free(cmd);
            continue;
        }

        if(strcmp(cmd, "exit\n") == 0)
        {
            free(cmd);
            break;
        }

        printf("%s", cmd);

        free(cmd);

    } while(1);

    exit(EXIT_SUCCESS);
}
