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
	int j;

	if (str == NULL || str[0] == '\0')
		return (NULL);

	token = strtok(str, " ");
	while (token != NULL)
	{
		tmp = malloc((i + 2) * sizeof(char *));
		if (tmp == NULL)
		{
			free(av);
			return (NULL);
		}

		j = 0;
		while (j < i)
		{
			tmp[j] = av[j];
			j++;
		}

		free(av);
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
 * @args: array of arguments
 * @env: environment variables
 * @shell_name: name of the shell
 * @cmd_num: command number
 *
 * Return: status code
 */
int execute_cmd(char **args, char **env, char *shell_name, int cmd_num)
{
	pid_t pid;
	char *cmd;
	int status;

	cmd = find_path(args[0], env);
	if (cmd == NULL)
	{
		fprintf(stderr, "%s: %d: %s: not found\n",
			shell_name, cmd_num, args[0]);
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
		if (execve(cmd, args, env) == -1)
		{
			perror(args[0]);
			free(cmd);
			exit(127);
		}
	}
	else
	{
		wait(&status);
		free(cmd);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
	}
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
	if (args == NULL || args[0] == NULL)
		return (0);

	if (strcmp(args[0], "exit") == 0)
	{
		free(line);
		free(args);
		exit(0);
	}

	if (strcmp(args[0], "env") == 0)
	{
		builtin_env(env);
		return (1);
	}

	return (0);
}
