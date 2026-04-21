#include "main.h"

/**
 * process_line - Parses and executes a single input line
 * @line: The input line
 * @env: Environment variables
 * @shell_name: Name of the shell (argv[0])
 * @cmd_num: Command count
 * Return: Last command status
 */
static int process_line(char *line, char **env, char *shell_name, int cmd_num)
{
	char **args;
	int status = 0;

	if (!line || line[0] == '\0')
		return (0);

	args = split_string(line);
	if (!args || !args[0])
	{
		free(args);
		return (0);
	}

	if (handle_builtins(args, env, line))
	{
		free(args);
		return (0);
	}

	status = execute_cmd(args, env, shell_name, cmd_num);
	free(args);
	return (status);
}

/**
 * main - Simple Shell main loop
 * @ac: Arg count
 * @av: Arg vector
 * @env: Environment
 * Return: 0 on success
 */
int main(int ac, char **av, char **env)
{
	char *line = NULL;
	size_t n = 0;
	int cmd_num = 0, status = 0;
	(void)ac;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "($) ", 4);

		if (getline(&line, &n, stdin) == -1)
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			break;
		}

		if (line[strlen(line) - 1] == '\n')
			line[strlen(line) - 1] = '\0';

		cmd_num++;
		status = process_line(line, env, av[0], cmd_num);
	}
	free(line);
	return (status);
}
