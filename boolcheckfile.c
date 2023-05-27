#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <stdbool.h>
#include <sys/stat.h>
#include "main.h"
/**
  * check_file_status: checks file status
  * @filename: file name
  * @statbuf: structure for stat
  * @tokens: input outpit
  * Return: bool statement
  */
bool check_file_status(const char *filename, struct stat *statbuf)
{
if (stat(filename, statbuf) == -1)
{
return (false);
}
if (S_ISREG(statbuf->st_mode) && (statbuf->st_mode & S_IXUSR))
{
return (true);
}
return (false);
}

