#include <stdio.h>
#include <stddef.h>
/**
 *_strncpy - Copies a specified number of characters one string to another.
 * @destn: The destination string where characters will be copied to.
 * @src: The source string from which characters will be copied.
 * @n: The maximum number of characters to be copied.
 *
 * Return: A pointer to the destination string.
 */
char *_strncpy(char *destn, const char *src, size_t n)
{
size_t i;
for (i = 0; i < n && src[i] != '\0'; i++)
destn[i] = src[i];
for (; i < n; i++)
destn[i] = '\0';
return (destn);
}
