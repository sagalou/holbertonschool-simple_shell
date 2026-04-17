#include <stdio.h>

extern char **environ;  /* declare the global variable */

int main(void)
{
    int i = 0;

    while (environ[i] != NULL)
    {
       printf("%s\n", environ[i]); /* afficher environ[i] */
        i++;
    }
    return (0);
}
