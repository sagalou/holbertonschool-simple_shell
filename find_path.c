#include "main.h"

/**
 * find_path - searches for the full path of a command in the PATH variable
 * @cmd: the command name to look for (e.g. "ls", "cat")
 * @env: the environment variables array (NULL-terminated)
 *
 * Return: full patch string or NULL if not found
 */
char *find_path(char *cmd, char**env)
{
	int i = 0;

	while (env[i] != NULL)
	{
		if (strncmp(env[i], "PATH=", 5) == 0)
		{
			char *path = strdup(env[i] + 5);
			char *dir = strtok(path, ":");

			while (dir != NULL)
			{
				char full_path[1024];
				struct stat st;

				snprintf(full_path, sizeof(full_path), "%s/%s", dir, cmd);
				if (stat(full_path, &st) == 0
					&& S_ISREG(st.st_mode)
					&& access(full_path, X_OK) == 0)
				{
					free(path);
					return (strdup(full_path));
				}
				dir = strtok(NULL, ":");
			}
			free(path);
		}
		i++;
	}
	return (NULL);
}
