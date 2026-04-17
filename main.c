#include "main.h"

/**
 * main - Entry point of the simple shell
 * @ac: argument count (unused)
 * @av: argument vector (unused)
 * @env: environment variables passed to execve
 *
 * Return: 0 on success
 */
int main(int ac, char **av, char **env)
{
	char *line = NULL;
	size_t n = 0;
	char **args;

	(void)ac;
	(void)av;

	while (getline(&line, &n, stdin) != -1)
	{
		line[strlen(line) - 1] = '\0';
		if (line[0] == '\0')
		{
			if (isatty(STDIN_FILENO))
				printf("$ ");
			continue;
		}
		args = split_string(line);
		if (args[0] == NULL)
		{
			free(args);
			if (isatty(STDIN_FILENO))
				printf("$ ");
			continue;
		}
		if (handle_builtins(args, env, line))
		{
			if (isatty(STDIN_FILENO))
				printf("$ ");
			continue;
		}
		handle_process(args, env);
		free(args);
		if (isatty(STDIN_FILENO))
			printf("$ ");
	}
	free(line);
	return (0);
}
