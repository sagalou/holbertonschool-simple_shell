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
	char *line = NULL;      /* Buffer dynamically allocated by getline */
	size_t n = 0;           /* Buffer size, automatically managed by getline */
	char **args;            /* Array of tokens produced by splitting the line */

	(void)ac;               /* Unused parameters, silences compiler warnings */
	(void)av;

	/* Main loop: print prompt, read a line, process it */
	while (1)
	{
		if (isatty(STDIN_FILENO))
			printf("$ ");

		if (getline(&line, &n, stdin) == -1)
			break;

		/* Replace the trailing '\n' with '\0' to get a clean string */
		line[strlen(line) - 1] = '\0';

		/* Empty line or whitespace-only: loop back to prompt */
		if (line[0] == '\0')
			continue;

		/* Split the line into tokens separated by whitespace */
		args = split_string(line);

		if (args[0] == NULL)
		{
			free(args);
			continue;
		}

		/* Check if the command is a builtin (exit, env, cd) and run it */
		if (handle_builtins(args, env, line))
			continue;

		/* External command: fork + execve, then free the token array */
		execute_cmd(args, env);
		free(args);
	}
	free(line); /* Release the buffer allocated by getline before exiting */
	return (0);
}
