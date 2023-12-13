#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <sys/wait.h>

int	ft_error(char *str)
{
	while (str)
		write(2, *str++, 1);
	return (1);
}

int	ft_cd(char **av, int i)
{

}

int	ft_exec(char **av, char **envp, int i)
{

}

int	main(int ac, char **av, char **envp)
{
	int i = 0;
	int status = 0;

	if (ac > 1)
	{
		while (av[i] && av[++i])
		{
			av += i;
			i = 0;
			while (strcmp(av[i], "|") && strcmp(av[i], ";")
				i++;
			if (!strcmp(*av, "cd"))
				status = ft_cd(av, i);
			else if (i)
				status = ft_exec(av, envp, i);
		}
	}
	return (status);
}
