#include <errno.h>
#include "main.h"
/**
  * arg_counter - counts number of arguments
  * @buf: user input
  * @size: size of user input
  * Return: number of argumnets
  */
int arg_counter(char *buf, int size)
{
	int count = 0, i;

	for (i = 1; i < size; i++)
		count += ((buf[i - 1] == ' ' &&
					(buf[i] != ' ' && buf[i] != '\n')) ||
				(i == 1 &&
				 buf[i - 1] != ' '));
	return (count);
}
/**
  * get_command - format command line arguments
  * @buf: buffer for storing user input
  * Return: memory address where arguments are stored
  */
char **get_command(char **buf)
{
	char **array;
	size_t n = 1, k, i, l = 0, count;

	*buf = malloc(n), k = getline(buf, &n, stdin);
	if (k == (size_t)(-1))
	{
		if (errno == 0)
			return (NULL);
		perror("Failure to read line");
		return (NULL);
	}
	count = arg_counter(*buf, k);
	if (!count)
	{
		array = malloc(sizeof(char *));
		array[0] = strdup(" ");
		return (array);
	}
	array = malloc(sizeof(char *) * (count + 1));
	if (array == NULL)
	{
		free(*buf), free(array);
		return (NULL);
	}
	for (i = 1; i < k; i++)
	{
		if ((*buf)[i - 1] == ' ' || (*buf)[i - 1] == '\t' || (*buf)[i - 1] == '\n')
			(*buf)[i - 1] = '\0';
		else if ((*buf)[i - 1] == '\0')
			continue;
		else
		{
			array[l] = *buf + i - 1;
			while ((*buf)[i] != ' ' && (*buf)[i] != '\t' && (*buf)[i] != '\n')
				i++;
			(*buf)[i] = '\0', l++;
		}
	}
	array[l] = NULL;
	return (array);
}
