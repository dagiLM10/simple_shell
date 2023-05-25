#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <stdbool.h>
#include <sys/stat.h>
 extern char **environ;

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

void custom_write(const char* str)
{
int length = strlen(str);
write(STDOUT_FILENO, str, length);
}
bool command_exists(const char* command)
{
bool exists = false;
char* pathEnv = getenv("PATH");
char pathCopy[1024];
strcpy(pathCopy, pathEnv);
char* pathToken = strtok(pathCopy, ":");
while (pathToken != NULL)
{
char commandPath[1024];
strcpy(commandPath, pathToken);
strcat(commandPath, "/");
strcat(commandPath, command);
if (access(commandPath, X_OK) == 0)
{
exists = true;
break;
}
pathToken = strtok(NULL, ":");
}
return exists;
}
bool check_file_status (const char *filename, struct stat *statbuf)
{
if (stat(filename, statbuf) == -1)
{
return (false);
if (S_ISREG(statbuf->st_mode) && (statbuf->st_mode & S_IXUSR))
{
return (true);
}
return (false);
}
}
char *search_executable_in_paths(const char *command, struct stat *statbuf)
{
char *pathEnv = getenv("PATH");
char pathCopy[1024];
strcpy(pathCopy, pathEnv);
char *pathToken = strtok(pathCopy, ":");
while (pathToken != NULL)
{
char commandPath[1024];
strcpy(commandPath, pathToken);
strcat(commandPath, "/");
strcat(commandPath, command);
if (check_file_status(commandPath, statbuf))
{
return strdup(commandPath);
}
pathToken = strtok(NULL, ":");
}
return NULL;
}

char** split_string(const char* str, const char* delimiter, int* argc)
{
char* strCopy = strdup(str);
char* token = strtok(strCopy, delimiter);
char **tokens = malloc(sizeof(char*) * 18);
int i = 0;
while (token != NULL && i < 17)
{
tokens[i] = strdup(token);
i++;
token = strtok(NULL, delimiter);
}
tokens[i] = NULL;
*argc = i;
free(strCopy);
return tokens; }
void free_tokens(char** tokens)
{
for (int i = 0; tokens[i] != NULL; i++)
{
free(tokens[i]);
}
free(tokens);
}
void execute_command(char* command, char* argv[], struct stat* statbuf, char** environ)
{
if (!command_exists(command))
{
custom_write("Command not found\n");
exit(EXIT_FAILURE);
}
if (!check_file_status(command, statbuf))
{
perror("Error (file status)");
exit(EXIT_FAILURE);
}
execve(command, argv, environ);
// If execve failed perror("Error (execve)");
exit(EXIT_FAILURE);
}

int main(void)
{
char *line = NULL;
size_t bufsize = 0;
ssize_t inpt;
const char *prompt = "$";
char *argv[18];
struct stat statbuf;
bool fpipe = false;
while (1 && !fpipe)
{
if (isatty(STDIN_FILENO) == 0)
{
fpipe = true;
}
custom_write(prompt);
inpt = getline(&line, &bufsize, stdin);
if (inpt == -1)
{
perror("Error");
free(line);
exit(EXIT_FAILURE);
}
if (line[inpt - 1] == '\n')
{
line[inpt - 1] = '\0';
}
int argc = 0;
char **tokens = split_string(line, " ", &argc);
if (strcmp(tokens[0], "exit") == 0)
{
free_tokens(tokens);
free(line);
exit(EXIT_SUCCESS);
}
else if (strcmp(tokens[0], "env") == 0)
{
print_environment(environ);
}
else
{
if (command_exists(tokens[0]))
{
pid_t pid = fork();
if (pid == -1)
{
perror("fork error");
}
else if (pid == 0)
{
struct stat execStat;
if (!check_file_status(tokens[0], &execStat))
{
char *fullpath = search_executable_in_paths(tokens[0], &execStat);
if (fullpath)
{
free(tokens[0]);
tokens[0] = fullpath;
}
else
{
perror("Error (file status)");
free_tokens(tokens);
continue;
}
}
execute_command(tokens[0], tokens, &statbuf, environ);
}
else
{
wait(NULL);
}
}
else
{
custom_write("command not found\n");
}
}
free_tokens(tokens);
}
free(line);
return 0;
}
