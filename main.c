#include "main.h"

/**
 * process_line - parses and executes a single input line
 * @line: the input line (already stripped of newline)
 * @env: environment variables passed to execve
 *
 * Return: 1 to continue the loop, 0 otherwise
 */
static int process_line(char *line, char **env)
{
	char **args;

	if (line[0] == '\0')
		return (1);

	args = split_string(line);
	if (args[0] == NULL)
	{
		free(args);
		return (1);
	}
	if (handle_builtins(args, env, line))
		return (1);
	execute_cmd(args, env);
	free(args);
	return (1);
}

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

	(void)ac;
	(void)av;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			printf("$ ");
		if (getline(&line, &n, stdin) == -1)
			break;
		line[strlen(line) - 1] = '\0';
		process_line(line, env);
	}
	free(line);
	return (0);
}
