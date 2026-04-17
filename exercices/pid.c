#include <stdio.h>
#include <unistd.h>

/**
 * main - PID
 *
 * Return: Always 0.
 */
int main(void)
{
    pid_t pid_parent;

    pid_parent = getppid();
    printf("%u\n", pid_parent);
    return (0);
}
