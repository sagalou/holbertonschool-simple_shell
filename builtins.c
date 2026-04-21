#include "main.h"

/**
 * builtin_env - prints all environment variables
 * @env: environment variables array
 *
 * Return: nothing
 */
void builtin_env(char **env)
{
	int i = 0; /* index pour parcourir le tableau d'environnement */

	while (env[i] != NULL) /* chaque entrée est du type "CLE=valeur" */
	{
		write(STDOUT_FILENO, env[i], strlen(env[i])); /* affiche la variable */
		write(STDOUT_FILENO, "\n", 1);                /* saut de ligne après chaque entrée */
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
	exit(0); /* quitte le shell avec le code 0 (succès) */
}
