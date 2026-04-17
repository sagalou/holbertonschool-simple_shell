#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
    char *av[] = {"/bin/ls", "-l", "/tmp", NULL};
    int i;

    for (i = 0; i < 5; i++)
    {
		pid_t pid = fork();					/* create a child process */

		if (pid == 0)						/* child process: fork() returns 0 */
		{
			execve(av[0], av, NULL);		/* replace child with the command to execute */
		}
		else								/* parent process: fork() returns child's PID */
		{
			wait(NULL);						/* wait for the child to finish */
		}
    }
	return (0);
}
