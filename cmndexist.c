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
* command_exists - Checks if a command exists in the system's PATH
* @command: The command to check for existence
* Return: the true or false
*/
bool command_exists(const char *command)
{
bool exists = false;
char *pathEnv = getenv("PATH");
char pathCopy[1024];
_strcpy(pathCopy, pathEnv);
char *pathToken = strtok(pathCopy, ":");
while (pathToken != NULL)
{
char commandPath[1024];
_strcpy(commandPath, pathToken);
my_strcat(commandPath, "/");
my_strcat(commandPath, command);
struct stat statbuf;
if (stat(commandPath, &statbuf) == 0)
{
if (S_ISREG(statbuf.st_mode) && (statbuf.st_mode & S_IXUSR))
{
exists = true;
break;
}
}
pathToken = strtok(NULL, ":");
}
return (exists);
}
