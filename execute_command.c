#include "shell.h"
#include <errno.h>

int execute_command(char **args)
{
    pid_t child_pid;
    struct stat st;
    int status = 0, flag = 0, i = 0;
    char *fullPath = NULL, **pathArr = NULL, *path = NULL;

    if (stat(args[0], &st) == 0 && strcmp(args[0], "hbtn_ls") != 0)
    {
        fullPath = strdup(args[0]);
        flag = 1;
        child_pid = fork();
    }
    else
    {
        extern char **environ;
        char *env_path = NULL;
        int path_len = 0;

        for (i = 0; environ[i]; i++)
        {
            if (strncmp(environ[i], "PATH=", 5) == 0)
            {
                env_path = environ[i] + 5;
                break;
            }
        }

        if (env_path)
        {
            pathArr = parse_line(env_path, ":");
            if (!pathArr)
                perror("malloc");

            while (pathArr[i])
            {
                fullPath = malloc(strlen(pathArr[i]) + strlen(args[0]) + 2);
                if (!fullPath)
                {
                    perror("malloc");
                    return (1);
                }

                strcpy(fullPath, pathArr[i]);
                strcat(fullPath, "/");
                strcat(fullPath, args[0]);

                if (stat(fullPath, &st) == 0)
                {
                    child_pid = fork();
                    flag = 1;
                    break;
                }
                free(fullPath);
                i++;
            }

            for (i = 0; pathArr[i]; i++)
                free(pathArr[i]);
            free(pathArr);
        }
    }

    if (!flag)
    {
        fprintf(stderr, "./hsh: 1: %s: not found\n", args[0]);
        return (127);
    }
    else
    {
        if (child_pid == -1)
        {
            free(fullPath);
            perror("fork");
            return (1);
        }
        else if (child_pid == 0)
        {
            if (execve(fullPath, args, environ) == -1)
            {
                free(fullPath);
                perror("execve");
                return (2);
            }
        }
        else
        {
            waitpid(child_pid, &status, 0);
            free(fullPath);
            if (WIFEXITED(status))
                return (WEXITSTATUS(status));
        }
    }
    return (0);
}

