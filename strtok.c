#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

char **split_string(char *str)
{
	char *token = NULL;     /* pointer to store each word returned by strtok */      
	char **av = NULL;       /* array of strings to store all words */
	int i = 0;              /* counter to track number of words */

    token = strtok(str, " ");           /* first call: pass the string to split */
	while (token != NULL)               /* loop until no more words */
	{
		av = realloc(av, (i + 1) * sizeof(char *)); /* resize av to add one more slot */
		av[i] = token ;                 /* store current word in av */
		i++;                            /* move to next slot */
        token = strtok(NULL, " ");      /* next calls: pass NULL to continue splitting */
	}
	av = realloc(av, (i + 1) * sizeof(char *)); /* add one slot for NULL terminator */
	av[i] = NULL;                       /* NULL-terminate the array like argv */
	return (av);                        /* return the array of words */
}

int main(void)
{
    char str[] = "ls -la /home";         /* test string to split */
    char **av = split_string(str);       /* call our function */
    int i = 0;

    while (av[i] != NULL)                 /* print each word */
    {
        printf("%s\n", av[i]);
        i++;
    }
    return (0);
}
