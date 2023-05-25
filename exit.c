#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include "main.h"
void custom_write(const char* str)
{
int length = 0;
while (str[length] != '\0')
{
length++;
}
write(STDOUT_FILENO, str, length);
}
int main(void)
{
char *line = NULL;
size_t bufsize =0;
ssize_t inpt;
const char* prompt;
char str[1024];
char* token;
pid_t pid;
int i = 0;
extern char **environ;
int fpipe = 0;
char* argv[18];
prompt = "$";
while (1 && !fpipe)
{
if (isatty(STDIN_FILENO) != 0)
fpipe = 1;
custom_write(prompt);
inpt = getline(&line, &bufsize, stdin);
if (inpt == -1)
{
perror("error");
free(line);
exit(EXIT_FAILURE);
}
if (line[inpt - 1] == '\n')
line[inpt - 1] ='\0';
token = strtok(line, " ");
while (token != NULL)
{
argv[i] = token;
i++;
token = strtok(NULL, " ");
}
argv[i] = NULL;
if (_strcmp(argv[0], "exit") == 0)
{
free(line);
exit(EXIT_SUCCESS);
}
pid = fork();
if (pid == -1)
{
perror ("error");
}
else if (pid == 0)
{
execve(argv[0], argv, environ);
perror("execve");
exit(EXIT_FAILURE);
}
else
{
wait(NULL);
}
}
free(line);
line =  NULL;
bufsize = 0;
i = 0;
return (0);
}
