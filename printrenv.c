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
 * print_environment - Prints the environment variables to stdout
 * @env: The array of environment variables
* Return: void
*/
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

