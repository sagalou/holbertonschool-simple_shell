#include "main.h"

/**
 * process_line - Parses and executes a single input line
 * @line: The input line
 * @env: Environment variables
 * @shell_name: Name of the shell (argv[0])
 * @cmd_num: Command count
 * Return: Last command status
 */
static int process_line(char *line, char **env, char *shell_name, int cmd_num)
{
	char **args;
	static int status; /* static : conserve le dernier code de retour entre les appels */

	if (!line || line[0] == '\0') /* ligne vide : rien à exécuter */
		return (0);

	args = split_string(line); /* découpe la ligne en tableau de mots */
	if (!args || !args[0])     /* split n'a rien produit (ex: espaces seuls) */
	{
		free(args);
		return (0);
	}

	if (handle_builtins(args, env, line, status)) /* teste et exécute les builtins */
	{
		free(args); /* si builtin traité, on libère et on sort */
		return (0);
	}

	status = execute_cmd(args, env, shell_name, cmd_num); /* exécute via fork/execve */
	free(args);    /* libère le tableau de mots après usage */
	return (status);
}

/**
 * main - Simple Shell main loop
 * @ac: Arg count
 * @av: Arg vector
 * @env: Environment
 * Return: 0 on success
 */
int main(int ac, char **av, char **env)
{
	char *line = NULL; /* buffer alloué dynamiquement par getline */
	size_t n = 0;      /* taille du buffer (gérée automatiquement par getline) */
	int cmd_num = 0, status = 0;
	(void)ac; /* ac non utilisé : supprime l'avertissement du compilateur */

	while (1)
	{
		if (isatty(STDIN_FILENO))          /* mode interactif : affiche le prompt */
			write(STDOUT_FILENO, "($) ", 4);

		if (getline(&line, &n, stdin) == -1) /* lit une ligne ; -1 = EOF ou erreur */
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1); /* retour à la ligne propre sur Ctrl+D */
			break; /* fin de la boucle principale */
		}

		if (line[strlen(line) - 1] == '\n')
			line[strlen(line) - 1] = '\0'; /* retire le '\n' final laissé par getline */

		cmd_num++;                                      /* incrémente le compteur de commandes */
		status = process_line(line, env, av[0], cmd_num); /* traite la ligne saisie */
	}
	free(line);     /* libère le buffer alloué par getline */
	return (status); /* retourne le code de la dernière commande exécutée */
}
