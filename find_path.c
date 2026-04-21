#include "main.h"

/**
 * search_dirs - searches cmd in each directory of path_val
 * @path_val: colon-separated list of directories
 * @cmd: command name to find
 *
 * Return: full path string or NULL if not found
 */
static char *search_dirs(char *path_val, char *cmd)
{
	char *path = strdup(path_val); /* copie de PATH car strtok modifie la chaîne */
	char *dir = strtok(path, ":"); /* premier répertoire de la liste */
	char full_path[1024];          /* buffer pour "répertoire/commande" */
	struct stat st;                /* structure pour récupérer les infos du fichier */

	while (dir != NULL)
	{
		snprintf(full_path, sizeof(full_path), "%s/%s", dir, cmd); /* chemin complet à tester */

		/* trois conditions cumulées : fichier existe + fichier ordinaire + exécutable */
		if (stat(full_path, &st) == 0
			&& S_ISREG(st.st_mode)       /* exclut les répertoires et fichiers spéciaux */
			&& access(full_path, X_OK) == 0) /* vérifie le bit d'exécution */
		{
			free(path);
			return (strdup(full_path)); /* retourne une copie du chemin valide trouvé */
		}
		dir = strtok(NULL, ":"); /* répertoire suivant dans PATH */
	}
	free(path);
	return (NULL); /* commande introuvable dans tous les répertoires de PATH */
}

/**
 * find_path - searches for the full path of a command in PATH
 * @cmd: the command name to look for (e.g. "ls", "cat")
 * @env: the environment variables array (NULL-terminated)
 *
 * Return: full path string or NULL if not found
 */

char *find_path(char *cmd, char **env)
{
	int i = 0;
	struct stat st;

	if (strchr(cmd, '/')) /* la commande contient '/' : c'est déjà un chemin */
	{
		if (stat(cmd, &st) == 0) /* vérifie que le fichier existe */
			return (strdup(cmd)); /* retourne une copie du chemin fourni */
		return (NULL);           /* chemin fourni mais fichier inexistant */
	}

	/* parcourt l'environnement pour trouver la variable PATH */
	while (env[i] != NULL)
	{
		if (strncmp(env[i], "PATH=", 5) == 0)     /* entrée PATH trouvée */
			return (search_dirs(env[i] + 5, cmd)); /* délègue la recherche dans les dossiers */
		i++;
	}
	return (NULL); /* PATH absent de l'environnement */
}
