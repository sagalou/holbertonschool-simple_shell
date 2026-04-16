#include <stdio.h>

void print_env(char **env);

/**
 * main - entry point
 * @ac: arguments count
 * @av: arguments array
 * @env: user environment variables
 *
 * Return: Always 0.
 */
int main(int ac, char **av, char **env)
{
(void)ac;
(void)av;
print_env(env);
return (0);
}
