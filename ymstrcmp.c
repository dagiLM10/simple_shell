#include <stdio.h>
/**
* _strcmp - Compares two strings.
* @str: Pointer to the first string.
* @str1: Pointer to the second string.
*
* Return: Integer value indicating the comparison result.
*/
int _strcmp(const char *str, const char *str1)
{
while (*str != '\0' && *str == *str1)
{
str++;
str1++;
}
return (*(unsigned char *)str - *(unsigned char *)str1);
}
