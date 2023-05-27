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
* exit_command - Handles the 'exit' command in the Simple Shell program *
@tokens: Array of command tokens
*
* Description: Frees allocated memory and exits the shell program.
*
* Return: No return value
*/
void handle_exit(char *line, char **tokens)
{
int exit_status = 0;
if (tokens[1] != NULL)
{
exit_status = my_atoi(tokens[1]);
}
free_tokens(tokens);
free(line);
exit(exit_status);
}
