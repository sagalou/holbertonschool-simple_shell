#include "main.h"

/**
 * split_string - Splits a string into an array of words
 * @str: the input string to split
 *
 * Return: a NULL-terminated array of strings (each word)
 */
char **split_string(char *str)
{
	char *token = NULL;   /* pointeur vers le mot courant extrait */
	char **av = NULL;     /* tableau de mots (résultat final) */
	char **tmp = NULL;    /* tableau temporaire pour le realloc manuel */
	int i = 0;            /* nombre de mots ajoutés jusqu'ici */
	int j;

	if (str == NULL || str[0] == '\0') /* chaîne vide ou NULL : rien à faire */
		return (NULL);

	token = strtok(str, " ");          /* premier mot (délimiteur : espace) */
	while (token != NULL)
	{
		tmp = malloc((i + 2) * sizeof(char *)); /* i mots + nouveau + NULL final */
		if (tmp == NULL)
		{
			free(av);      /* libère le tableau existant en cas d'échec */
			return (NULL);
		}

		j = 0;
		while (j < i)          /* copie les anciens pointeurs dans tmp */
		{
			tmp[j] = av[j];
			j++;
		}

		free(av);              /* libère l'ancien tableau devenu inutile */
		av = tmp;              /* av pointe maintenant sur le nouveau tableau */
		av[i] = token;         /* ajoute le mot courant */
		i++;

		token = strtok(NULL, " "); /* prochain mot (NULL = reprend là où on s'est arrêté) */
	}

	if (av != NULL)
		av[i] = NULL; /* termine le tableau par un pointeur NULL (convention execve) */

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
	pid_t pid;    /* PID du processus fils créé par fork */
	char *cmd;    /* chemin absolu de la commande trouvé dans PATH */
	int status;   /* code de retour brut récupéré par wait */

	cmd = find_path(args[0], env); /* résout le chemin complet de la commande */
	if (cmd == NULL)
	{
		fprintf(stderr, "%s: %d: %s: not found\n",
			shell_name, cmd_num, args[0]); /* message d'erreur style sh */
		return (127); /* 127 = commande introuvable (convention POSIX) */
	}

	pid = fork(); /* crée un processus fils */
	if (pid == -1)
	{
		perror("fork"); /* fork a échoué (ressources insuffisantes, etc.) */
		free(cmd);
		return (1);
	}

	if (pid == 0) /* bloc exécuté uniquement par le fils */
	{
		if (execve(cmd, args, env) == -1) /* remplace l'image du fils par la commande */
		{
			perror(args[0]); /* execve n'a pas pu lancer la commande */
			free(cmd);
			exit(127);       /* le fils quitte avec 127 en cas d'erreur */
		}
	}
	else /* bloc exécuté par le père */
	{
		wait(&status);         /* attend la fin du fils */
		free(cmd);
		if (WIFEXITED(status)) /* vérifie que le fils a terminé normalement */
			return (WEXITSTATUS(status)); /* extrait le code de sortie réel */
	}
	return (0);
}

/**
 * handle_builtins - checks and executes built-in commands
 * @args: array of arguments
 * @env: environment variables
 * @line: input line buffer
 * @status: exit code of the last command
 *
 * Return: 1 if built-in was executed, 0 otherwise
 */
int handle_builtins(char **args, char **env, char *line, int status)
{
	if (args == NULL || args[0] == NULL) /* pas de commande à traiter */
		return (0);

	if (strcmp(args[0], "exit") == 0) /* commande "exit" : quitter le shell */
	{
		free(line);   /* libère le buffer de la ligne saisie */
		free(args);   /* libère le tableau d'arguments */
		exit(status); /* quitte avec le code du dernier retour */
	}

	if (strcmp(args[0], "env") == 0) /* commande "env" : afficher l'environnement */
	{
		builtin_env(env); /* délègue l'affichage à la fonction dédiée */
		return (1);       /* 1 = un builtin a été exécuté */
	}

	return (0); /* 0 = ce n'est pas un builtin, continuer le traitement normal */
}
