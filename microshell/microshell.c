#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <sys/wait.h>

int	main(int ac, char **av, char **envp)
{
	int i = 0;
	int status = 0;

	if (ac > 1)
	{
		while (av[i] && av[++i])
		{
			//cosas
		}
	}
}
