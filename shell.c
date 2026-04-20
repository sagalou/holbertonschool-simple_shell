#include "main.h"

/**
 * split_string - Splits a string into an array of words
 * @str: the input string to split
 *
 * Return: a NULL-terminated array of strings (each word)
 */
char **split_string(char *str)
{
	char *token = NULL; /* stores each word returned by strtok */
	char **av = NULL;   /* array of strings to store all words */
	int i = 0;          /* counter to track number of words */

	token = strtok(str, " "); /* first call: pass the string to split on spaces */
	while (token != NULL)     /* loop until no more words */
	{
		av = realloc(av, (i + 1) * sizeof(char *)); /* resize av to add one slot */
		av[i] = token; /* store current word in av */
		i++;           /* move to next slot */
		token = strtok(NULL, " "); /* next calls: pass NULL to continue splitting */
	}
	av = realloc(av, (i + 1) * sizeof(char *)); /* add NULL terminator slot */
	av[i] = NULL;  /* NULL-terminate the array like argv */
	return (av);   /* return the array of words */
}

/**
 * execute_cmd - executes a command in the child process
 * @args: array of arguments (args[0] is the command name)
 * @env: environment variables passed to execve
 * @shell_name: name of the shell binary (argv[0])
 *
 * Return: nothing
 */
void execute_cmd(char **args, char **env, char *shell_name)
{
	pid_t pid = fork();

	if (pid == -1)
	{
		perror("fork");
		return;
	}
	if (pid == 0)
	{
		execve(args[0], args, env);
		fprintf(stderr, "%s: %s: No such file or directory\n",
			shell_name, args[0]);
		exit(1);
	}
	wait(NULL);
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
	if (strcmp(args[0], "exit") == 0) /* check if command is "exit" */
	{
		free(args); /* free the arguments array before exiting */
		free(line); /* free the input line buffer before exiting */
		exit(0);    /* terminate the shell with success status */
	}
	if (strcmp(args[0], "env") == 0) /* check if command is "env" */
	{
		builtin_env(env); /* print all environment variables */
		free(args);       /* free args after execution */
		return (1);       /* signal that a built-in was handled */
	}
	return (0); /* no built-in matched, caller should fork and execute */
}
