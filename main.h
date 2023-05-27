#ifndef MAIN_H
#define MAIN_H
#include <stdbool.h>
#include <stddef.h>
#include <sys/types.h>
#include <sys/stat.h>
struct stat;

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
int my_atoi(const char *str);
void execute_command(const char *command, char *argv[], struct stat *statbuf, char **environ);
void handle_exit(char *line, char **tokens);
bool command_exists(const char *command);
bool check_file_status(const char *filename, struct stat *statbuf);
char **split_string(const char *str, const char *delimiter, int *argc);
void print_environment(char **env);
void free_tokens(char **tokens);
void custom_write(const char *str);
#endif /* MAIN_H */
