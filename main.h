#ifndef MAIN_H
#define MAIN_H
#include <stdbool.h>
#include <stddef.h>
int _strcmp(const char *str1, const char *str2);
char *_strcpy(char *dest, const char *src);
char *my_strchr(const char *str, int character);
char *my_strcat(char *dest, const char *src);
size_t my_strlen(const char *str);
char *mynew_strtok(char *str, const char *delim);
bool yes_delimiter(char c, const char *delim);
char *my_strtok_dyn(char *str, const char *delim);
char *_strncpy(char *destn, const char *src, size_t n);
 char *mi_strdup(const char *str);
#endif /* MAIN_H */
