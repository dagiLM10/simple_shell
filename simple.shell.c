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
/**
 * read_line: reads line
 * Description:reads input to parse it
 * @prompt: prompt asks
 * Return: pointer to line
 */
char *read_line()
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
/**
  * custom_write: writes into stdout
  * Description: writes to prompt the user
  * @str: input
  * Return: void
  */
void custom_write(const char *str)
{
int length;
length = strlen(str);
write(STDOUT_FILENO, str, length);
}
/**
* free_tokens: is frees memory
* Description:frees to have enough space
* @tokens: input
* Return: void
*/
void free_tokens(char **tokens)
{
int i;
for (i = 0; tokens[i] != NULL; i++)
{
free(tokens[i]);
}
free(tokens);
}
/**
  * execute_fork: executes fork
  * Description: calls system call fork
  * @command: it is a command inpt
  * @tokens: token inpt
  * @statbuf: structure
  * @environ: environment varaiable
  * Return: void
  */
void execute_fork(const char *command, char **tokens, struct stat *statbuf, char **environ)
{
pid_t pid = fork();
if (pid == -1)
perror("fork error");
else if (pid == 0)
execute_command(command, tokens, statbuf, environ);
else
wait(NULL);
}

/**
  * perror_handling: handles error situation
  * Return: void
*/

void perror_handling()
{
char *line = NULL;
perror("Error");
free(line);
exit(EXIT_FAILURE);
}

/**
* main - Entry point of the Simple Shell program *
* Description: Reads and executes user commands in a loop.
* Supports built-in commands 'exit' and 'env'.
* Continues to read and execute commands until 'exit' is entered .
*
* Return: 0 on success, or appropriate error code on failure
*/

int main(void)
{
struct stat statbuf;
const char *prompt = "$";
bool fpipe = false;
char *line = NULL;
int argc = 0;
char **tokens;
while (1 && !fpipe)
{
if (isatty(STDIN_FILENO) == 0)
fpipe = true;
custom_write(prompt);
line = read_line();
if (line == NULL)
{
void perror_handling();
}
tokens = split_string(line, " ", &argc);
if (_strcmp(tokens[0], "exit") == 0)
{
handle_exit(line, tokens);
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
}
free_tokens(tokens);
free(line);
}
return (0);
}
