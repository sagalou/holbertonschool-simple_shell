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
	int last_status = 0;

	if (line[0] == '\0')
		return (0);

	args = split_string(line);
	if (args == NULL || args[0] == NULL)
	{
		if (args != NULL)
			free(args);
		return (0);
	}
	if (handle_builtins(args, env, line))
		return (0);
	last_status = execute_cmd(args, env, shell_name, cmd_num);
	free(args);
	return (last_status);
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
	int last_status = 0;

	(void)ac;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "($) ", 4);
		if (getline(&line, &n, stdin) == -1)
			break;
		line[strlen(line) - 1] = '\0';
		cmd_num++;
		last_status = process_line(line, env, av[0], cmd_num);
	}
	free(line);
	return (last_status);
}
