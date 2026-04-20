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
	int i = 0;

	token = strtok(str, " ");
	while (token != NULL)
	{
		av = realloc(av, (i + 1) * sizeof(char *));
		av[i] = token;
		i++;
		token = strtok(NULL, " ");
	}
	av = realloc(av, (i + 1) * sizeof(char *));
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
	pid_t pid = fork();
	int status = 0;

	if (pid == -1)
	{
		perror("fork");
		return (1);
	}
	if (pid == 0)
	{
		execve(args[0], args, env);
		fprintf(stderr, "%s: %d: %s: not found\n",
			shell_name, cmd_num, args[0]);
		exit(127);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
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
