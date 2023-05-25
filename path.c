#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
extern char **environ;
void custom_write(const char* str)
{
	int length = strlen(str);
	write(STDOUT_FILENO, str, length);
}
int command_exists(char *command)
{
	int exists = 0;
	char *pathEnv = getenv("PATH");
	char pathCopy[1024];
	strcpy(pathCopy, pathEnv);
	char* pathToken = strtok(pathCopy, ":");
	while (pathToken != NULL)
	{
		printf("%s\n", pathToken);
		char commandPath[1024];
		strcpy(commandPath, pathToken);
		strcat(commandPath, "/");
		strcat(commandPath, command);
		printf("%s\n", commandPath);
		if (access(commandPath, F_OK) == 0)
		{
			printf("exists");
			exists = 1;
			break;
		}
		pathToken = strtok(NULL, ":");
	}
	return (exists);
}
int main(void)
{
	char *line = NULL;
	size_t bufsize = 0;
	ssize_t inpt;
	const char *prompt = "$";
	char *argv[18];
 char **env = environ;
	while (1)
	{
		if (isatty(STDIN_FILENO) != 0)
		{
			custom_write(prompt); }

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
			free(line);
			exit(EXIT_SUCCESS);
		}
		else if (strcmp(argv[0], "env") == 0)
		{
			while (*env)
			{
				int length = strlen(*env);
				write(STDOUT_FILENO, *env, length);
				write(STDOUT_FILENO, "\n", 1);
				env++;
			}
		}
		else
		{
			int commandExists = command_exists(argv[0]);
			printf("trhis is argv0: %s\n", argv[0]);
			if (commandExists)
			{
				pid_t pid = fork();
				if (pid == -1)
				{
					perror("fork error");
				}
				else if (pid == 0)
				{
					execve(argv[0], argv, environ);
					perror("execve error");
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
