#include <stdio.h>

/**
 * print_env - display the environment via env variable
 * @env: user environment variables
 */

void print_env(char **env)

{
unsigned int i;

i = 0;
while (env[i] != NULL)
{
printf("%s\n", env[i]);
i++;
}
}
