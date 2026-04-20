#include "main.h"

/**
 * process_line - parses and executes a single input line
 * @line: the input line (already stripped of newline)
 * @env: environment variables passed to execve
 * @shell_name: name of the shell (argv[0])
 * @cmd_num: command line count for error messages
 *
 * Return: 1 to continue the loop, 0 otherwise
 */
static int process_line(char *line, char **env, char *shell_name, int cmd_num)
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
	execute_cmd(args, env, shell_name, cmd_num);
	free(args);
	return (1);
}

/**
 * main - Entry point of the simple shell
 * @ac: argument count (unused)
 * @av: argument vector
 * @env: environment variables passed to execve
 *
 * Return: 0 on success
 */
int main(int ac, char **av, char **env)
{
	char *line = NULL;
	size_t n = 0;
	int cmd_num = 0;

	(void)ac;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "$ ", 2);
		if (getline(&line, &n, stdin) == -1)
			break;
		line[strlen(line) - 1] = '\0';
		cmd_num++;
		process_line(line, env, av[0], cmd_num);
	}
	free(line);
	return (0);
}
