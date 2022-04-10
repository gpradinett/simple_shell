#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "shell.h"

/*
 * print_prompt1: The first function prints the first prompt string.
 * print_prompt2: The second function prints the second prompt string,
 *
 */


/*The first function prints the first prompt string, 
which you usually see when the shell is waiting for you to enter a command*/
void print_prompt1(void)
{
    fprintf(stderr, "#cisfun$ ");
}

/*The second function prints the second prompt string,
which is printed by the shell when you enter a multi-line command*/
void print_prompt2(void)
{
    fprintf(stderr, "> ");
}
