#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <stdbool.h>
#include <sys/stat.h>
#include "main.h"
/**
 * execute_command - Executes a command with given arguments
 * @command: The command to be executed
 * @argv: The arguments for the command * @statbuf: Pointer to a struct stat variable to check file status
 * @statbuf : structure for stat
 * @environ: The environment variables
*/
void execute_command(const char *command, char *argv[], struct stat *statbuf, char **environ)
{
char commandPath[1024];
char *pathToken;
char *pathEnv;
char pathCopy[1024];
bool commandFound = false;
if (check_file_status(command, statbuf))
{
if (execve(command, argv, environ) == -1)
{
perror("Execution error");
exit(EXIT_FAILURE);
}
}
else
{
if (command[0] == '/')
{
_strcpy(commandPath, command);
}
else
{
pathEnv = getenv("PATH");
_strcpy(pathCopy, pathEnv);
pathToken = my_strtok_dyn(pathCopy, ":");
while (pathToken != NULL)
{
_strcpy(commandPath, pathToken);
my_strcat(commandPath, "/");
my_strcat(commandPath, command);
if (check_file_status(commandPath, statbuf))
{
commandFound = true;
break;
}
pathToken = my_strtok_dyn(NULL, ":");
}
if (!commandFound)
{
custom_write("Command not found in PATH\n");
exit(EXIT_FAILURE);
}
if (!check_file_status(commandPath, statbuf))
{
custom_write("Command not found in PATH\n");
exit(EXIT_FAILURE);
}
if (execve(commandPath, argv, environ) == -1)
{
perror("Execution error");
exit(EXIT_FAILURE);
}
}
}
}
