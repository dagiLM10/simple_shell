#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/**
 * myn_getenv - Retrieves the value of an environment variable.
 * @name: The name of the environment variable.
 *
 * Return: The value of the environment variable if found, or NULL otherwise.
 */
char *myn_getenv(const char *name)
{
extern char **environ;
char *variable, *delimiter, *variable_name, *value;
size_t name_length;
int i;
for (i = 0; environ[i] != NULL; i++)
{
variable = environ[i];
delimiter = strchr(variable, '=');
if (delimiter != NULL)
{
name_length = delimiter - variable;
variable_name = malloc(name_length + 1);
if (variable_name != NULL)
{
strncpy(variable_name, variable, name_length);
variable_name[name_length] = '\0';
if (strcmp(variable_name, name) == 0)
{
value = delimiter + 1;
free(variable_name);
return (value);
}
free(variable_name);
}
}
}
return (NULL);
}

