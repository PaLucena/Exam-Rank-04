#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <sys/wait.h>

int	ft_error(char *str)
{
	while (*str)
		write(2, str++, 1);
	return (1);
}

int	ft_cd(char **av, int i)
{
	if (i != 2)
		return (ft_error("error: cd: bad arguments\n"));
	else if (chdir(av[1]) == -1)
		return (ft_error("error: cd: cannot change directory to "), ft_error(av[1]), ft_error("\n"));
	return (0);
}

int	ft_exec(char **av, char **envp, int i)
{
	int		fd[2];
	int 	status;
	int		pid;
	bool	pipe_check = 0;

	if (av[i] && !strcmp(av[i], "|"))
		pipe_check = 1;
	if (pipe_check && pipe(fd) == -1)
		return (ft_error("error: fatal\n"));
	pid = fork();
	if (!pid)
	{
		av[i] = 0;
		if (pipe_check && (dup2(fd[1], 1) == -1 || close(fd[0]) == -1 || close(fd[1]) == -1))
			return (ft_error("error: fatal\n"));
		execve(*av, av, envp);
		return (ft_error("error: cannot execute "), ft_error(*av), ft_error("\n"));
	}
	waitpid(pid, &status, 0);
	if (pipe_check && (dup2(fd[0], 0) == -1 || close(fd[0]) == -1 || close(fd[1]) == -1))
		return (ft_error("error: fatal\n"));
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	return (status);
}

int	main(int ac, char **av, char **envp)
{
	int	i = 0;
	int	status = 0;

	if (ac > 1)
	{
		while (av[i] && av[++i])
		{
			av += i;
			i = 0;
			while (av[i] && strcmp(av[i], "|") && strcmp(av[i], ";"))
				i++;
			if (!strcmp(*av, "cd"))
				status = ft_cd(av, i);
			else if (i)
				status = ft_exec(av, envp, i);
		}
	}
	return (status);
}
