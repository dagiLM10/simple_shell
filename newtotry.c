#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/stat.h>
#include <stdbool.h>
extern char **environ;
void custom_write(const char* str)
{
	int length = strlen(str);
	write(STDOUT_FILENO, str, length);
}
int command_exists(char* command)
{
	int exists = 0;
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
		if (access(commandPath, F_OK) == 0)
		{
			printf("%s\n", commandPath);
			exists = 1;
			break;
		}
		pathToken = strtok(NULL, ":");
	}
	return (exists);
}
bool check_file_status (char *filename, struct stat *statbuf)
{
if (stat(filename, statbuf) == -1)
{ return false; // File does not exist } // Check if it is a regular file and has execute permissions
if (S_ISREG(statbuf->st_mode) && (statbuf->st_mode & S_IXUSR))
{
return true; // File exists and has execute permissions
}
return false;
}
}
void exit_shell(char *line)
{
	free(line);
	exit(EXIT_SUCCESS);
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
void execute_command(char *command, struct stat *statbuf, char **environ)
{
	if (!check_file_status(command, statbuf))
	{
		perror("Error (file status)");
		exit(EXIT_FAILURE);
	}
	char *argv[] = {command, NULL};
	execve(command, argv, environ);
	/* Free the dynamically allocated argv array */ /*_free_vector(argv, 20) */ /* If execve failed */
	perror("Error (execve)");
	exit(EXIT_FAILURE);
}
int main(void)
{
	char *line = NULL;
	size_t bufsize = 0;
	ssize_t inpt;
	const char* prompt = "$";
	char* argv[18];
	struct stat statbuf;
	while (1)
	{
		if (isatty(STDIN_FILENO) != 0)
		{
			custom_write(prompt);
		}
		inpt = getline(&line, &bufsize, stdin);
		if (inpt == -1)
		{
			perror("error");
			free(line);
			exit(EXIT_FAILURE);
		}
		if (line[inpt - 1] == '\n')
		{
			line[inpt - 1] = '\0';
		}
		int i = 0;
		char* token = strtok(line, " ");
		while (token != NULL)
		{
			argv[i] = token;
			i++;
			token = strtok(NULL, " ");
		}
		argv[i] = NULL;
		if (strcmp(argv[0], "exit") == 0)
		{
			exit_shell(line);
		}
		else if (strcmp(argv[0], "env") == 0)
		{
			print_environment(environ);
		}
		else
		{
			int commandExists = command_exists(argv[0]);
			if (commandExists)
			{
				pid_t pid = fork();
				if (pid == -1)
				{
					perror("fork error");
				}
				else if (pid == 0)
				{ printf("argv0 : %s\n", argv[0]);
					execute_command(argv[0], &statbuf, environ);
					exit(EXIT_FAILURE);
				}
				else
				{
					wait(NULL);
				}
			}
			else
			{
				custom_write("Command not found\n");
			}
		}
	}
	free(line);
	return (0);
}
