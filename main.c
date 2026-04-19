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

	/* Main loop: reads a full line from stdin (EOF exits the shell) */
	while (getline(&line, &n, stdin) != -1)
	{
		/* Replace the trailing '\n' with '\0' to get a clean string */
		line[strlen(line) - 1] = '\0';

		/* Empty line after stripping '\n': reprint prompt and read again */
		if (line[0] == '\0')
		{
			if (isatty(STDIN_FILENO)) /* Only print prompt in interactive mode */
				printf("$ ");
			continue;
		}

		/* Split the line into tokens separated by whitespace */
		args = split_string(line);

		/* split_string returned an empty array (whitespace-only input) */
		if (args[0] == NULL)
		{
			free(args);
			if (isatty(STDIN_FILENO))
				printf("$ ");
			continue;
		}

		/* Check if the command is a builtin (exit, env, cd) and run it */
		/* Returns 1 if handled internally, 0 otherwise */
		if (handle_builtins(args, env, line))
		{
			if (isatty(STDIN_FILENO))
				printf("$ ");
			continue;
		}

		/* External command: fork + execve, then free the token array */
		handle_process(args, env);
		free(args);
		if (isatty(STDIN_FILENO))
			printf("$ ");
	}
	free(line); /* Release the buffer allocated by getline before exiting */
	return (0);
}
