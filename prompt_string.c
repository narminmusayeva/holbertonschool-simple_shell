#include "main.h"

/**
 * print_prompt - prints prompt string
 * @status: 1 if fd is an open file descriptor referring to a terminal
 */
void print_prompt(int status)
{
	if (status)
		printf("#cisfun$ ");
	else
		errno = 0;
}
