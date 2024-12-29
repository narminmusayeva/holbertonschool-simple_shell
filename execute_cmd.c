#include "main.h"
/**
  * exec_c - execute user input
  * @fcommand: user input
  * Return: executed commands return code
  */
int exec_c(char **fcommand)
{
	pid_t pid;
	int r_code;

	pid = fork();
	if (pid == 0)
		r_code = execve(fcommand[0], fcommand, environ);
	else
	{
		wait(&r_code);
		return (WEXITSTATUS(r_code));
	}
	return (r_code);
}
