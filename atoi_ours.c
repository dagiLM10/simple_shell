#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include "main.h"

/**
* my_atoi - Converts a string to an integer
* @str: The string to be converted
*
* Description: Converts the string representation of an integer  eq value.
*
* Return: The converted integer value, or 0 if conversion fails
*/
int my_atoi(const char *str)
{
int result = 0;
int sign = 1;
int i = 0;
while (str[i] == ' ' ||  str[i] == '\t' || str[i] == '\n')
i++;
if (str[i] == '-' || str[i] == '+')
{
sign = (str[i] == '-') ? -1 : 1;
i++;
}
while (str[i] >= '0' && str[i] <= '9')
{
result = result * 10 + (str[i] - '0');
i++;
}
return (result *sign);
}
