<<<<<<< HEAD
#include "main.h"

/**
 * main - Entry point of the simple shell
 *        Displays a prompt, reads a command, executes it, and loops
 * @ac: argument count (unused)
 * @av: argument vector (unused)
 * @env: environment variables passed to execve
 *
 * Return: 0 on success (when EOF is reached with Ctrl+D)
 */
int main(int ac, char **av, char **env)
{
	char *line = NULL;
	size_t n = 0;
	char **args;
	pid_t pid;
	char *cmd;

	(void)ac;
	(void)av;

	if (isatty(STDIN_FILENO))
		printf("$ ");

	while (getline(&line, &n, stdin) != -1)
	{
		line[strlen(line) - 1] = '\0';
		args = split_string(line);

		if (args[0] == NULL)
		{
			free(args);
			if (isatty(STDIN_FILENO))
				printf("$ ");
			continue;
		}

		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			free(args);
			continue;
		}

		if (pid == 0)
		{
			cmd = find_path(args[0], env);
			if (cmd == NULL)
			{
				fprintf(stderr, "%s: command not found\n", args[0]);
				free(args);
				exit(127);
			}
			execve(cmd, args, env);
			perror(cmd);
			free(cmd);
			free(args);
			exit(1);
		}
		else
		{
			wait(NULL);
		}
		free(args);
		if (isatty(STDIN_FILENO))
			printf("$ ");
	}
	free(line);
	return (0);
=======
#include <stdio.h>

void print_env(char **env);

/**
 * main - entry point
 * @ac: arguments count
 * @av: arguments array
 * @env: user environment variables
 *
 * Return: Always 0.
 */
int main(int ac, char **av, char **env)
{
(void)ac;
(void)av;
print_env(env);
return (0);
>>>>>>> 7266a28ec6f614fa34eb0a3887b836c2e1ba2342
}
