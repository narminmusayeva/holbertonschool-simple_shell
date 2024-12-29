#ifndef MAINH
#define MAINH
#define PATH "PATH="
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

extern char **path_var;
extern char **environ;
char **_strtok(char *str, char delim);
int exec_c(char **fcommand);
char **get_command(char **);
char **get_path(char **);
char *find_file(char *command, int *);
void print_prompt(int status);
void free_path(void);
void print_env(void);
#endif
