#include "main.h"

char **path_var;

/**
 * find_file - Finds file location in path variables.
 *
 * @command: User input specifying the file.
 * @lk: Flag indicating whether this command uses path or not.
 *
 * Return: Modified user input.
 */
char *find_file(char *command, int *lk)
{
	int i = 0, max_len = 0, j;
	char *temp, *result = NULL;
	struct stat st;

	if (command[0] == '/' || command[0] == '.')
	{
		if (!stat(command, &st))
		{
			result = strdup(command);
			if (result != NULL)
				(*lk)++;
		}
		return (result);
	}
	if (!path_var)
		return (NULL);
	for (j = 0; path_var[j] != NULL; j++)
		max_len += strlen(path_var[j]) + strlen(command) + 2;
	temp = malloc(max_len);
	if (temp == NULL)
		return (NULL);
	while (path_var[i])
	{
		strcpy(temp, path_var[i]);
		strcat(temp, "/");
		strcat(temp, command);
		if (!stat(temp, &st))
		{
			(*lk)++;
			errno = 0;
			result = strdup(temp);
			break;
		}
		i++;
	}
	free(temp);
	return (result);
}
