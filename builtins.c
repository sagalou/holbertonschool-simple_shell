#include "main.h"

/**
 * builtin_env - prints all environment variables
 * @env: environment variables array
 *
 * Return: nothing
 */
void builtin_env(char **env)
{
	int i = 0; /* counter to go through each environment variable */

	while (env[i] != NULL) /* loop until we reach the end of the array */
	{
		write(STDOUT_FILENO, env[i], strlen(env[i]));
        write(STDOUT_FILENO, "\n", 1);
		i++;
	}
}

/**
 * builtin_exit - exits the shell
 *
 * Return: nothing
 */
void builtin_exit(void)
{
	exit(0); /* terminate the shell with status 0 (success) */
}
