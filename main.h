#ifndef MAIN_H /* garde d'inclusion : évite les inclusions multiples du header */
#define MAIN_H

#include <stdio.h>    /* fprintf, printf, perror */
#include <stdlib.h>   /* malloc, free, exit */
#include <unistd.h>   /* write, access, fork, execve, isatty, STDIN_FILENO */
#include <string.h>   /* strlen, strcmp, strncmp, strchr, strdup, strtok */
#include <sys/stat.h> /* stat(), struct stat, S_ISREG */
#include <sys/wait.h> /* wait(), WIFEXITED, WEXITSTATUS */

/* --- find_path.c --- */
char *find_path(char *cmd, char **env); /* cherche le chemin complet de cmd dans PATH */

/* --- main.c ---*/
int main(int ac, char **av, char **env);                    /* point d'entrée du shell */
void shell_loop(char **env);                                /* boucle principale (non utilisée) */
void process_command(char **args, char **env, char *line);  /* traitement d'une commande */

/* --- shell.c ---*/
int execute_cmd(char **args, char **env, char *shell_name, int cmd_num); /* fork + execve */
char **split_string(char *str);                                          /* découpe une ligne en mots */
int handle_builtins(char **args, char **env, char *line, int status);    /* gère les builtins */

/* --- builtins.c --- */
void builtin_exit(void);       /* quitte le shell */
void builtin_env(char **env);  /* affiche les variables d'environnement */

#endif /* MAIN_H */
