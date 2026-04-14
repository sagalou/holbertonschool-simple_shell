#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
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
		token = strtok(NULL, " ");		/* next calls: pass NULL to continue splitting */
	}
	av = realloc(av, (i + 1) * sizeof(char *)); /* add one slot for NULL terminator */
	av[i] = NULL;                       /* NULL-terminate the array like argv */
	return (av);                        /* return the array of words */
}

int main(void)
{
	char *line = NULL;				/* buffer to store the command typed by the user */
	size_t n = 0;					/* size of the buffer for getline */

	printf("$ ");					/* display the prompt for the first time */

	while (getline(&line, &n, stdin) != -1)	/* read a line until EOF (Ctrl+D) */
	{
		line[strlen(line) - 1] = '\0';		/* remove trailing newline '\n' */
		char **av = split_string(line);		/* split the command into an array of words */
		pid_t pid = fork();					/* create a child process */

		if (pid == 0)						/* child process: fork() returns 0 */
		{
			execve(av[0], av, NULL);		/* replace child with the command to execute */
		}
		else								/* parent process: fork() returns child's PID */
		{
			wait(NULL);						/* wait for the child to finish */
		}
		printf("$ ");
	}
	return (0);
}
