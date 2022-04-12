#include "shell.h"

/**
 *_strcmp - compares two strings
 *@s1: first string
 *@s2: second string
 *Return: the first difference of strings
 */

int _strcmp(char *s1, char *s2)
{
	int i;

	for (i = 0; s1[i] != '\0' || s2[i] != '\0'; i++)
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
	}
	return (0);
}

/**
 * *dircat - Concatenates dir + / + file and retuns a pointer to its location
 * in memory.
 * @dir: directory that contains file
 * @file: name of file
 * Return: pointer to new string on sucess, NULL on fail.
 */

char *dircat(char *dir, char *file)
{
	size_t i, j;
	char *temp;

	temp = malloc(sizeof(char) * (_strlen(dir) + _strlen(file) + 2));
	if (temp == NULL)
		return (NULL);
	for (i = 0; dir[i] != '\0'; i++)
	{
		temp[i] = dir[i];
	}
	temp[i] = '/';
	i++;
	for (j = 0; file[j] != '\0'; j++)
	{
		temp[i + j] = file[j];
	}
	temp[i + j] = '\0';
	return (temp);
}

/**
 * _strlen - retuns the length of a string without the null char
 * @str: string
 * Return: length of string
 */

size_t _strlen(char *str)
{
	size_t i = 0;

	while (str[i])
	{
		i++;
	}
	return (i);
}


/**
 *_atoi - converts string to int
 *@str: string being converted
 *Return: -1 if illegal number, else the converted int
 */

int _atoi(char *str)
{
	int i, n = 0;

	if (str == NULL)
		return (-1);
	for (i = 0; str[i] != '\0'; i++)
	{
		if (str[i] < '0' || str[i] > '9')
			return (-1);
		n = (n * 10) + (str[i] - '0');
	}
	return (n);
}


/**
 *_itoa - converts int to string
 *@stri: a string
 *@i: int being converted
 *Return: a string
 */

char *_itoa(char *stri, int i)
{
	int j, n;

	n = i;
	for (j = 1; (n / 10) != 0; j++)
		n = n / 10;

	stri = malloc(sizeof(char) * (j + 1));
	if (stri == NULL)
		return (NULL);

	stri[j] = '\0';
	j--;
	for (; j >= 0; j--)
	{
		stri[j] = (i % 10) + '0';
		i = i / 10;
	}
	return (stri);
}
