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
	pid_t pid;

	(void)ac;
	(void)av;

	if (isatty(STDIN_FILENO))
		printf("$ ");

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
		if (strcmp(args[0], "exit") == 0)
        {
            free(args);
            free(line);
            line = NULL;
			exit(0);
        }
		if (strcmp(args[0], "env") == 0)
		{
			builtin_env(env);
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
			execute_cmd(args, env);
		else
			wait(NULL);
		free(args);
		if (isatty(STDIN_FILENO))
			printf("$ ");
	}
	free(line);
	return (0);
}
