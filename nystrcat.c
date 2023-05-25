#include <stdio.h>
/**
 * my_strcat - Concatenates two strings
 * @dest: The destination string
 * @src: The source string
 *
 * Return: Pointer to the destination string
 */
char *my_strcat(char *dest, const char *src)
{
char *origlDest = dest;
while (*dest != '\0')
{
dest++;
}
while (*src != '\0')
{
*dest = *src;
dest++;
src++;
}
*dest = '\0';
return (origlDest);
}
