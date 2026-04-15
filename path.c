#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>

char *find_path(char *cmd, char**env)
{
    int i = 0;
    while (env[i] != NULL)
    {
        if (strncmp(env[i], "PATH=", 5) == 0)
        {
            char *path = env[i] + 5;
            char *dir = strtok(path, ":");
            while (dir != NULL)
            {
                char full_path[1024];
                struct stat st;

                sprintf(full_path, "%s/%s", dir, cmd);
                if (stat(full_path, &st) == 0)
                {
                    return (strdup(full_path));
                }
                dir = strtok(NULL, ":");
            }
        }
        i++;
    }
    return (NULL);
}