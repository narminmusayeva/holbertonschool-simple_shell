#include "main.h"
/**
 * _strtok - Custom implementation of strtok
 * @str: String to tokenize
 * @delim: Delimiter character
 *
 * Return: Array of tokens
 */
char **_strtok(char *str, char delim)
{
	char **array, *start, *end;
	int i = 0, j = 1, max_tokens = 10;

	if (str == NULL)
		return (NULL);

	array = malloc(sizeof(char *) * max_tokens);

	if (array == NULL)
		return (NULL);

	while (str[i])
	{
		if (str[i] != delim)
		{
			start = str + i;
			while (str[i] != delim && str[i])
				i++;
			if (str[i] == '\0')
			{
				array[j - 1] = strdup(start);
				j++;
				break;
			}
			else
			{
				end = str + i;
				*end = '\0';
				array[j - 1] = strdup(start), *end = delim, start = end;
			}
			j++;
		}
		i++;
	}

	array[j - 1] = NULL;
	return (array);
}
