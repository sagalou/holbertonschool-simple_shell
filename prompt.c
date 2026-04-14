#include <stdio.h>
#include <unistd.h>

int main(void)
{
	char *line = NULL;
	size_t n = 0;

	printf("$ ");

	while (getline(&line, &n, stdin) != -1)
	{
		printf("%s", line);
		printf("$ ");
	}
	return (0);
}
