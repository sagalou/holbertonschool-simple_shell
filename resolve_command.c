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
	char full_path[1024];
	struct stat st;
	int i = 0;

	/* si commande avec / */
	if (strchr(cmd, '/'))
	{
		if (stat(cmd, &st) == 0)
			return (strdup(cmd));
		return (NULL);
	}

	while (env[i])
	{
		if (strncmp(env[i], "PATH=", 5) == 0)
		{
			path = env[i] + 5;
			path_copy = strdup(path);
			dir = strtok(path_copy, ":");

			while (dir)
			{
				sprintf(full_path, "%s/%s", dir, cmd);

				if (stat(full_path, &st) == 0)
				{
					free(path_copy);
					return (strdup(full_path));
				}
				dir = strtok(NULL, ":");
			}
			free(path_copy);
			return (NULL);
		}
		i++;
	}
	return (NULL);
}
