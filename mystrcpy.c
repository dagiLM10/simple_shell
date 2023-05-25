#include <stdio.h>
/**
 * _strcpy - Copies a string from source to destination.
 * @dest: Pointer to the destination string.
 * @str: Pointer to the source string.
 *
 * Return: Pointer to the destination string.
 */
char *_strcpy(char *dest, char *str)
{
char *origDest = dest;
while (*str != '\0')
{
*dest = *str;
str++;
dest++;
}
*dest = '\0';
return (origDest);
}
