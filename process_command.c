#include "main.h"

void process_command(char **args, char **env, char *line)
{
	pid_t pid;
	char *cmd_path;
	int i = 0;

	(void)line;

	/* exit */
	if (strcmp(args[0], "exit") == 0)
	{
		exit(0);
	}

	/* env */
	if (strcmp(args[0], "env") == 0)
	{
		while (env[i])
		{
			printf("%s\n", env[i]);
			i++;
		}
		return;
	}

	cmd_path = find_path(args[0], env);

	if (cmd_path == NULL)
	{
		fprintf(stderr, "%s: command not found\n", args[0]);
		return;
	}

	pid = fork();

	if (pid == 0)
	{
		execve(cmd_path, args, env);
		perror("execve");
		exit(1);
	}
	else
	{
		wait(NULL);
	}

	free(cmd_path);
}