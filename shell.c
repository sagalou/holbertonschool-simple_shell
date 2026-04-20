#include "main.h"

/**
 * split_string - Splits a string into an array of words
 * @str: the input string to split
 *
 * Return: a NULL-terminated array of strings (each word)
 */
char **split_string(char *str)
{
	char *token = NULL;
	char **av = NULL;
	char **tmp = NULL;
	int i = 0;

	if (str == NULL || str[0] == '\0')
		return (NULL);
	token = strtok(str, " ");
	while (token != NULL)
	{
		tmp = malloc((i + 2) * sizeof(char *)); /* resize av to add one slot */
		if (tmp == NULL)
			return (NULL);
		if (av != NULL)
		{
			int j = 0;

			while (j < i)
			{
				tmp[j] = av[j];
				j++;
			}
			free(av);
		}
		av = tmp;
		av[i] = token;
		i++;
		token = strtok(NULL, " ");
	}
	if (av != NULL)
		av[i] = NULL;
	return (av);
}

/**
 * execute_cmd - executes a command in the child process
 * @args: array of arguments (args[0] is the command name)
 * @env: environment variables passed to execve
 * @shell_name: name of the shell binary (argv[0])
 * @cmd_num: command line count for error messages
 *
 * Return: nothing
 */
int execute_cmd(char **args, char **env, char *shell_name, int cmd_num)
{
	pid_t pid;
	char *cmd;

	cmd = find_path(args[0], env);
	if (cmd == NULL)
	{
		fprintf(stderr, "%s: %d: %s: not found\n",
			shell_name, cmd_num, args[0]);
		free(args);
		return (127);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		free(cmd);
		return (1);
	}
	if (pid == 0)
	{
		execve(cmd, args, env);
		perror(cmd);
		free(cmd);
		free(args);
		exit(1);
	}
	wait(NULL);
	free(cmd);
	return (0);
}

/**
 * handle_builtins - checks and executes built-in commands
 * @args: array of arguments
 * @env: environment variables
 * @line: input line buffer
 *
 * Return: 1 if built-in was executed, 0 otherwise
 */
int handle_builtins(char **args, char **env, char *line)
{
	if (strcmp(args[0], "exit") == 0)
	{
		free(args);
		free(line);
		exit(0);
	}
	if (strcmp(args[0], "env") == 0)
	{
		builtin_env(env);
		free(args);
		return (1);
	}
	return (0);
}
