#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <stdbool.h>
#include <sys/stat.h>
#include "main.h"

extern char **environ;
char *read_line(const char *prompt)
{
char *line = NULL;
size_t bufsize = 0;
ssize_t inpt;
inpt = getline(&line, &bufsize, stdin);

if (line[inpt - 1] == '\n')
{
line[inpt - 1] = '\0';
}
return (line);
}

void print_environment(char **env)
{
while (*env)
{
int length = strlen(*env);
write(STDOUT_FILENO, *env, length);
write(STDOUT_FILENO, "\n", 1);
env++;
}
}
void custom_write(const char *str)
{
int length = strlen(str);
write(STDOUT_FILENO, str, length);
}
bool command_exists(const char *command)
{
bool exists = false;
char *pathEnv = getenv("PATH");
char pathCopy[1024];
strcpy(pathCopy, pathEnv);
char *pathToken = my_strtok_dyn(pathCopy, ":");
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
pathToken = my_strtok_dyn(NULL, ":");
}
return (exists);
}
char **split_string(const char *str, const char *delimiter, int *argc)
{
char *strCopy = mi_strdup(str);
char *token = my_strtok_dyn(strCopy, delimiter);
char **tokens = malloc(sizeof(char *) * 18);
int i = 0;
while (token != NULL && i < 17)
{
tokens[i] = mi_strdup(token);
i++;
token = my_strtok_dyn(NULL, delimiter);
}
tokens[i] = NULL;
*argc = i;
free(strCopy);
return (tokens);
}
bool check_file_status (const char *filename, struct stat *statbuf)
{
if (stat(filename, statbuf) == -1)
{
return (false);
}
if (S_ISREG(statbuf->st_mode) && (statbuf->st_mode & S_IXUSR))
{
return (true);
}
return (false);
}
void free_tokens(char **tokens)
{
for (int i = 0; tokens[i] != NULL; i++)
{
free(tokens[i]);
}
free(tokens);
}
void execute_command(const char *command, char *argv[], struct stat *statbuf, char **environ)
{
        if (check_file_status(command, statbuf))
        { // Execute the command directly
                if (execve(command, argv, environ) == -1)
                {
                        perror("Execution error");
        exit(EXIT_FAILURE);
}
}
else
{
        char commandPath[1024];
        if (command[0] == '/')
        {
		_strcpy(commandPath, command);
        } else {
char *pathEnv = getenv("PATH");
char pathCopy[1024]; _strcpy(pathCopy, pathEnv);char *pathToken = my_strtok_dyn(pathCopy, ":");char commandPath[1024];bool commandFound = false;
while (pathToken != NULL)
{
_strcpy(commandPath, pathToken); my_strcat(commandPath, "/"); my_strcat(commandPath, command);
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
} // Execute the command using execve
if (!check_file_status(commandPath, statbuf)){
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

void execute_fork(const char *command, char **tokens, struct stat *statbuf, char **environ)
{
pid_t pid = fork();
if (pid == -1)
perror("fork error");
else if (pid == 0)
execute_command(tokens[0], tokens, statbuf, environ);
else
wait(NULL);
}




int main(void)
{
const char *prompt = "$";
struct stat statbuf;
bool fpipe = false;
char *line = NULL;
while (1 && !fpipe)
{
if (isatty(STDIN_FILENO) == 0)
fpipe = true;
custom_write(prompt);
line = read_line(prompt);
if (line == NULL)
{
perror("Error");
free(line);
exit(EXIT_FAILURE);
}

int argc = 0;
char **tokens = split_string(line, " ", &argc);
if (strcmp(tokens[0], "exit") == 0)
{
free_tokens(tokens);
free(line);
exit(EXIT_SUCCESS);
}
else if (_strcmp(tokens[0], "env") == 0)
{
print_environment(environ);
}
else
{
if (command_exists(tokens[0]))
{
execute_fork(tokens[0], tokens, &statbuf, environ);
}
else
{
custom_write("command not found\n");
}
}free_tokens(tokens);free(line);}return (0);
}
