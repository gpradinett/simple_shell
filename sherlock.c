#include "shell.h"
/**
 * sherlock - Seperates input into seprate words using a
 * delmiter and removes \n
 * @str: Input sent to shell
 * @delim: Delimiter to use to seperate commands and arguments
 * Return: pointer to pointers of the words found.
 */

char **sherlock(char *str, const char *delim)
{
	unsigned int i, j, end = 0, word = 0, mark = 0, dnum = 0;
	char **words;

	dnum = count_delim(str, delim);
	words = malloc(sizeof(char *) * (dnum + 2));
	words[dnum + 1] = '\0';
	if (words == NULL)
		return (NULL);
	for (i = 0; str[i]; i++)
	{
		for (j = 0; str[i + j] == delim[j] || delim[j] == '\0'
			     || str[i + 1] == '\0'; j++)
		{
			if (str[i + 1] == '\0')
			{
				end = 1;
				i++;
			}
			if (delim[j] == '\0' || str[i] == '\0')
			{

				words[word] = malloc(sizeof(char) * (i - mark + 1));
				if (words[word] == NULL)
				{
					free_d_ptr(words);
					return (NULL);
				}
				set_word(str, words, word, mark, i);
				word++;
				mark = i + j;
				i += j - 1;
				break;
			}
		}
		if (end == 1)
			break;
	}
	return (words);
}

/**
 * free_d_ptr - free's a double pointer
 * @ptr: Double pointer to free
 * Return: none
 */

void free_d_ptr(char **ptr)
{
	int i = 0;

	while (ptr[i])
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
}


/**
 * count_delim - counts the number of delmimters found in a string
 * when it hits a newline, it replaces it with \0 and ends
 * @str: string to check
 * @delim: delimiter to check for
 * Return: number of delimitres found in string
 */

int count_delim(char *str, const char *delim)
{
	int i, j, dnum = 0;

	for (i = 0; str[i]; i++)
	{
		if (str[i] == '\n')
		{
			str[i] = '\0';
			break;
		}
		for (j = 0; str[i + j] == delim[j] || delim[j] == '\0'; j++)
		{
			if (delim[j] == '\0')
			{
				dnum++;
				i += j - 1;
				break;
			}
		}
	}
	return (dnum);
}

/**
 * set_word - loops through a string from mark to i and assigns that value to a
 * char pointer in an array of char pointers
 * @str: String to loop through
 * @words: Array of char pointers
 * @word: Element of array to set
 * @mark: Starting point in string
 * @i: Ending point in string
 * Return: none
 */


void set_word(char *str, char **words, unsigned int word, unsigned int mark,
	     unsigned int i)
{
	unsigned int k = 0;

	for (k = 0; k <= (i - mark); k++)
	{
		if (k == (i - mark))
			(words[word][k]) = '\0';
		else
			(words[word][k]) = str[mark + k];
	}
}

/**
 *watson - helper function for sherlock that trims excess spaces
 *@str: the string being trimmed
 *Return: the new string
 */

char *watson(char *str)
{
	int i, j = 0;
	char *strtea;

	strtea = malloc(sizeof(char) * _strlen(str));
	if (strtea == NULL)
	{
		write(1, "Failed to malloc\n", 16);
		return (NULL);
	}

	for (i = 0; str[i] == ' '; i++)
	{}
	for (; str[i] != '\0'; i++)
	{
		while (str[i] == ' ' && (str[i + 1] == ' '
					 || str[i + 1] == '\0'
					 || str[i + 1] == '\n'))
			i++;
		strtea[j] = str[i];
		j++;
	}
	free(str);
	return (strtea);
}
