#include <stdlib.h>
#include <string.h>
#include "main.h"
#include <stdio.h>
/**
 * mi_strdup - Duplicates a string.
 * @str: The string to be duplicated.
 *
 * Return: On success, a pointer to the duplicated string. On failure, NULL.
 */
char *mi_strdup(const char *str)
{
size_t len = my_strlen(str) + 1;

char *new_str = (char *)malloc(len);
if (new_str == NULL)
{
return (NULL);
}
_strncpy(new_str, str, len);
return (new_str);
}

