#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "shell.h"

void print_prompt1(void)
{
    fprintf(stderr, "#cisfun$ ");
}

void print_prompt2(void)
{
    fprintf(stderr, "> ");
}
