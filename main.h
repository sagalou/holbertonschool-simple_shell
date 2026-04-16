#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>

char *find_path(char *cmd, char**env);
char **split_string(char *str);
int main(int ac, char **av, char **env);
char *_getenv(const char *name);
void builtin_exit(void);
void builtin_env(char **env);
void execute_cmd(char **argds, char **env);

#endif
