#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
/**
 * yes_delimiter - checks if the char is delimiter
 * @c: char
 * @delim: delimiter
 *
 * Return: bool true or false
 */
bool yes_delimiter(char c, const char *delim)
{
int i = 0;
while (delim[i] != '\0')
{
if (c == delim[i])
{
return (true);
}
i++;
}
return (false);
}

/**
 * mynew_strtok - Tokenizes a string based on specified delimiters
 * @str: The input string to be tokenized
 * @delim: The delimiter string used for tokenization
 *
 * Return: Pointer to the next token, or NULL if no more tokens are available
*/
char *mynew_strtok(char *str, const char *delim)
{
static char *saved_token;
char *token = NULL;
if (str != NULL)
{
saved_token = str;
}
if (saved_token == NULL || *saved_token == '\0')
{
return (NULL);
}
token = saved_token;
while (*token != '\0')
{
if (yes_delimiter(*token, delim))
{
*token = '\0';
saved_token = token + 1;
return (token);
}
token++;
}
saved_token = NULL;
return (token);
}

