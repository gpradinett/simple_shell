#include "shell.h"

/**
 * _getenv - gets the environmental vairable's value
 * @name: Name of environmental varialble to access
 * Return: pointer to environmental variable value
 */


char *_getenv(const char *name)
{
	int i, j;

	for (i = 0; __environ[i]; i++)
	{
		for (j = 0; 1; j++)
		{
			if (name[j] == '\0' && __environ[i][j] == '=')
				return (&(__environ[i][j + 1]));
			else if (name[j] == __environ[i][j])
				continue;
			else
				break;
		}
	}
	return (NULL);
}

/**
 *_strdup - creates a copy of a string using malloc
 *@str: the string to be copied
 *Return: the pointer to the copy of the string
 */

char *_strdup(char *str)
{
	char *cpy;
	int i, k;

	if (str == NULL)
		return (NULL);

	for (k = 0; str[k] != '\0'; k++)
	{}

	cpy = malloc((k + 1) * sizeof(char));

	if (cpy == NULL)
		return (NULL);

	for (i = 0; str[i] != '\0'; i++)
	{
		cpy[i] = str[i];
	}
	cpy[i] = str[i];

	return (cpy);

}
