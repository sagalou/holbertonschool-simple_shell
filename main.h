#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>

/* --- find_path.c --- */
char *find_path(char *cmd, char **env);

/* --- main.c ---*/
int main(int ac, char **av, char **env);
void shell_loop(char **env);
void process_command(char **args, char **env, char *line);

/* --- shell.c ---*/
int execute_cmd(char **args, char **env, char *shell_name, int cmd_num);
char **split_string(char *str);
int handle_builtins(char **args, char **env, char *line, int status);

/* --- builtins.c --- */
void builtin_exit(void);
void builtin_env(char **env);

/* --- process.c --- */
void process_command(char **args, char **env, char *line);

#endif
