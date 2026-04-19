#include "main.h"

/**
 * find_path - searches for the full path of a command in the PATH variable
 * @cmd: the command name to look for (e.g. "ls", "cat")
 * @env: the environment variables array (NULL-terminated)
 *
 * Return: full patch string or NULL if not found
 */
char *find_path(char *cmd, char **env)
{
	int i = 0;

	while (env[i] != NULL)                             /* iterate over all environment variables */
	{
		if (strncmp(env[i], "PATH=", 5) == 0)         /* find the variable that starts with "PATH=" */
		{
			char *path = strdup(env[i] + 5);          /* copy the PATH value, skipping the "PATH=" prefix */
			char *dir = strtok(path, ":");             /* split PATH into directories separated by ":" */

			while (dir != NULL)                        /* iterate over each directory in PATH */
			{
				char full_path[1024];                  /* buffer to build the full command path */
				struct stat st;                        /* struct to hold file metadata */

				snprintf(full_path, sizeof(full_path), "%s/%s", dir, cmd); /* build e.g. "/usr/bin/ls" */
				if (stat(full_path, &st) == 0          /* check the file exists */
					&& S_ISREG(st.st_mode)             /* check it is a regular file, not a directory */
					&& access(full_path, X_OK) == 0)   /* check it is executable */
				{
					free(path);                        /* free the PATH copy before returning */
					return (strdup(full_path));        /* return the found full path */
				}
				dir = strtok(NULL, ":");               /* move to the next directory */
			}
			free(path);                                /* free the PATH copy if command was not found */
		}
		i++;                                           /* move to the next environment variable */
	}
	return (NULL);                                     /* command not found in any PATH directory */
}
