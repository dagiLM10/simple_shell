#include <stdio.h>
/**
 * my_strchr - Locates the first occurrence of a character in a string.
 * @str: Pointer to the string to be searched.
 * @character: The character to be located.
 *
 * Return: Pointer to the first occurrence of the character in the string.
 * NULL if the character is not found.
 */
char *my_strchr(const char *str, int character)
{
while (*str != '\0')
{
if (*str != character)
str++;
else
return ((char *) str);
}
return (NULL);
}
