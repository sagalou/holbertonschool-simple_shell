#include "main.h"

/**
 * resolve_command - resolves a command to its full path
 * @cmd: command to resolve
 * @env: environment variables
 *
 * Return: full path of the command or NULL if not found
 */

char *resolve_command(char *cmd, char **env)
{
	char *path, *path_copy, *dir;
	char full_path[1024]; /* buffer pour construire "répertoire/commande" */
	struct stat st;       /* structure remplie par stat() pour vérifier l'existence */
	int i = 0;

	/* si la commande contient '/', c'est déjà un chemin (relatif ou absolu) */
	if (strchr(cmd, '/'))
	{
		if (stat(cmd, &st) == 0) /* vérifie que le fichier existe bien */
			return (strdup(cmd)); /* retourne une copie du chemin tel quel */
		return (NULL);           /* chemin fourni mais fichier inexistant */
	}

	/* parcourt les variables d'environnement pour trouver PATH */
	while (env[i])
	{
		if (strncmp(env[i], "PATH=", 5) == 0) /* entrée PATH trouvée */
		{
			path = env[i] + 5;         /* pointe après "PATH=" pour avoir la valeur */
			path_copy = strdup(path);  /* copie nécessaire car strtok modifie la chaîne */
			dir = strtok(path_copy, ":"); /* découpe PATH en répertoires séparés par ':' */

			while (dir)
			{
				sprintf(full_path, "%s/%s", dir, cmd); /* construit le chemin complet */

				if (stat(full_path, &st) == 0) /* le fichier existe dans ce répertoire */
				{
					free(path_copy);
					return (strdup(full_path)); /* retourne une copie du chemin trouvé */
				}
				dir = strtok(NULL, ":"); /* répertoire suivant dans PATH */
			}
			free(path_copy);
			return (NULL); /* commande non trouvée dans aucun répertoire de PATH */
		}
		i++;
	}
	return (NULL); /* variable PATH absente de l'environnement */
}
