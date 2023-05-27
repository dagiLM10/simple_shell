#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
/**
 * my_strtok_dyn - Tokenizes a string based on specified delimiters
 * @str: The input string to be tokenized
 * @delim: input delimiter
 *
 * Return: Pointer to the next token, or NULL if no more tokens are available
*/
char *my_strtok_dyn(char *str, const char *delim)
{
static char *nextToken;
char *token = NULL;
size_t tokenLength;
char *delimiter;
if (str != NULL)
{
nextToken = str;
}
if (nextToken == NULL || *nextToken == '\0')
{
return (NULL);
}
delimiter = my_strchr(nextToken, *delim);
if (delimiter != NULL)
{
size_t tokenLength = delimiter - nextToken;
token = (char *)malloc((tokenLength + 1) * sizeof(char));
_strncpy(token, nextToken, tokenLength);
token[tokenLength] = '\0';
nextToken = delimiter + 1;
}
else
{
tokenLength = strlen(nextToken);
token = (char *)malloc((tokenLength + 1) * sizeof(char));
_strcpy(token, nextToken);
nextToken = NULL;
}
return (token);
}
