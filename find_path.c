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
	char *path = strdup(path_val);
	char *dir = strtok(path, ":");
	char full_path[1024];
	struct stat st;

	while (dir != NULL)
	{
		snprintf(full_path, sizeof(full_path), "%s/%s", dir, cmd);
		/* check file exists, is regular, and is executable */
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
	return (NULL);
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

	if (strchr(cmd, '/'))
	{
		if (stat(cmd, &st) == 0)
			return (strdup(cmd));
		return (NULL);
	}

	while (env[i] != NULL)
	{
		if (strncmp(env[i], "PATH=", 5) == 0)
			return (search_dirs(env[i] + 5, cmd));
		i++;
	}
	return (NULL);
}
