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
* split_string - Splits a string into an array of tokens
* @str: The string to be split
* @delimiter: The delimiter used to split the string
* @argc: Pointer to an integer to store the number of tokens
* Return: a pointer to the string.
*/
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
